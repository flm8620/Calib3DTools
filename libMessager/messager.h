#ifndef MESSAGER_H
#define MESSAGER_H
#include <sstream>
#include <stdexcept>
#include <mutex>
namespace libMsg {
enum MessageType {
    M_TEXT, M_INFO, M_WARN, M_ERROR
};

class AbortFlag
{
public:
    AbortFlag();
    void requestAbort();
    void resetFlag();
    bool abortRequested();
private:
    std::mutex lock;
    bool needToAbort;
};
extern AbortFlag abortFlag;
class Messager
{
public:

    virtual void message(std::string s, MessageType type) = 0;
};

extern Messager *globalMessager;

class ostream
{
public:
    ostream(Messager * &msg);
    template<typename T>
    ostream& operator<<(const T& value) { ss<<value; return *this; }
    ostream &operator<<(ostream & (*manipFunc)(ostream &));
    ostream &flush();
    ostream &endl();
    ostream &setprecision(int precision);
private:
    Messager * &receiverMsg;
    std::stringstream ss;
    int doublePrecision;
};

ostream &flush(ostream &os);
ostream &endl(ostream &os);
extern ostream cout;
void abortIfAsked();
void error(const char *msg);
}

class MyException : public std::runtime_error
{
public:
    MyException(const std::string &msg);
};

#endif
