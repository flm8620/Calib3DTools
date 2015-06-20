#ifndef EVENTDELEGATE_H
#define EVENTDELEGATE_H

#include "readwritelock.h"
#include "abstractthreadpool.h"
#include <thread>
#include <vector>

template <class OBJECT>
class ObjectMethod :Runnable
{
private:
    mutable ReadWriteLock rwlock;
    OBJECT* obj;
    void (OBJECT::*method)();
public:
    ObjectMethod( OBJECT* obj, void (OBJECT::*method)() ) : obj(obj), method(method) {}
    bool isValid() { return obj!=NULL && method!=NULL; }
    void run() {
        ReadLock lock(rwlock);
        if(isValid())
            obj.*method();
    }
};

template <class OBJECT, class THREAD_POOL=AbstractThreadPool>
class EventDelegate
{
private:
    static THREAD_POOL tPool;
    ObjectMethod<OBJECT> target;

public:
    EventDelegate<OBJECT>(OBJECT* target, void (*OBJECT::targetMethod)() ):target(target, targetMethod) {}

    void call() {
        this->target.run();
    }

    inline void trigger() {
        if(tPool !=NULL) {
            if(this->target.isValid())
                tPool.start( this->target );
        }
        else
            this->target.run();
    }
}

#endif // EVENTDELEGATE_H

