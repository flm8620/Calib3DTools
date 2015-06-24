#ifndef ABSTRACTTHREADPOOL_H
#define ABSTRACTTHREADPOOL_H

namespace concurrent {

class Runnable
{
public:
    virtual void run() =0;
    virtual void done() { }
    virtual ~Runnable() {}
};

class AbstractThreadPool {
public:
    virtual void start( Runnable* task ) const =0;
};



} //namespace concurrent
#endif // ABSTRACTTHREADPOOL_H

