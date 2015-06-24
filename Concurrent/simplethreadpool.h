#ifndef EVENTTHREADPOOL_H
#define EVENTTHREADPOOL_H

#include "abstractthreadpool.h"
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace concurrent {


class SimpleThreadPool : public AbstractThreadPool
{
public:
    SimpleThreadPool(int threads=5);
    ~SimpleThreadPool();
    void start( Runnable* task ) const;
    static SimpleThreadPool DEFAULT;

private:
    std::vector<std::thread*> pool;

    class TaskQueue
    {
    public:
        void Push(Runnable*  t);
        Runnable* Pop();
        void close();
    private:
        mutable std::queue<Runnable*> q;
        std::mutex mtx;
        std::condition_variable notEmpty;
        bool closed = false;
    };
    mutable TaskQueue tasks;
    static void threadMain(TaskQueue* tasks);
};

} //namespace concurrent
#endif // EVENTTHREADPOOL_H
