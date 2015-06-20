#ifndef EVENTTHREADPOOL_H
#define EVENTTHREADPOOL_H

#include "abstractthreadpool.h"
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class Runnable;

class EventThreadPool : AbstractThreadPool
{
public:
    EventThreadPool(int initSize=2, int maxSize=5);
    ~EventThreadPool();
    void start( Runnable* task );

private:
    std::vector<std::thread*> pool;
    int initsize, maxsize;

    class TaskQueue
    {
    public:
        void Push(Runnable*  t);
        Runnable* Pop();
        void close();
    private:
        std::queue<Runnable*> q;
        std::mutex mtx;
        std::condition_variable notEmpty;
        bool closed = false;
    } tasks;
    static void threadMain(TaskQueue* tasks);
};

#endif // EVENTTHREADPOOL_H
