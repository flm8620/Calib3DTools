#ifndef MESSAGER_H
#define MESSAGER_H
#include <sstream>
namespace libMsg {
enum MessageType {
    M_TEXT, M_INFO, M_WARN, M_ERROR
} ;

class Messager
{
public:

    virtual void message(std::string s, MessageType type) = 0;
};
class ostream
{
public:
    ostream(Messager * &msg);
    ostream &operator<<(const char *value);
    ostream &operator<<(double value);
    ostream &operator<<(int value);
    ostream &operator<<(unsigned int value);
    ostream &operator<<(char value);
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
extern Messager *globalMessager;
void error(const char *msg);
}
#endif
