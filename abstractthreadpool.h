#ifndef ABSTRACTTHREADPOOL_H
#define ABSTRACTTHREADPOOL_H

class Runnable
{
public:
    virtual void run() =0;
    virtual ~Runnable() =0;
};

class AbstractThreadPool {
public:
    virtual void start( Runnable* task ) =0;
};

#endif // ABSTRACTTHREADPOOL_H

