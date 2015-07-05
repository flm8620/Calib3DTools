#include "messager.h"

namespace libMsg {
Messager *globalMessager = 0;
ostream cout(globalMessager);//Use globalMessage as standard output
AbortFlag abortFlag;

void error(const char *msg)
{
    if (globalMessager)
        globalMessager->message(msg, M_ERROR);
    throw MyException(msg);
}

ostream::ostream(Messager * &msg) : receiverMsg(msg),
    doublePrecision(6)
{
    ss.precision(doublePrecision);
}

ostream &ostream::operator<<(ostream & (*manipFunc)(ostream &))
{
    return (*manipFunc)(*this);
}

ostream &ostream::flush()
{
    if (this->receiverMsg) {
        this->receiverMsg->message(ss.str(), M_TEXT);
        ss.str(std::string());
        ss.clear();
    }
    return *this;
}

ostream &ostream::endl()
{
    ss.put('\n');
    return this->flush();
}

ostream &ostream::setprecision(int precision)
{
    this->doublePrecision = precision > 2 ? precision : 2;
    ss.precision(doublePrecision);
}

ostream &flush(ostream &os)
{
    return os.flush();
}

ostream &endl(ostream &os)
{
    return os.endl();
}

void abortIfAsked()
{
    if(abortFlag.abortRequested()){
        //abortFlag.resetFlag();
        error("Aborted by user.");
    }
}

AbortFlag::AbortFlag()
{
    this->needToAbort=false;
}

void AbortFlag::requestAbort()
{
    std::lock_guard<std::mutex> locker(this->lock);
    this->needToAbort=true;
}

void AbortFlag::resetFlag()
{
    std::lock_guard<std::mutex> locker(this->lock);
    this->needToAbort=false;
}

bool AbortFlag::abortRequested()
{
    std::lock_guard<std::mutex> locker(this->lock);
    return this->needToAbort;
}

}

MyException::MyException(const std::string &msg) : std::runtime_error(msg)
{
}
