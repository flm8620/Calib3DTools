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
    static SimpleThreadPool DEFAULT;
    SimpleThreadPool(int threads = 5);
    ~SimpleThreadPool();
protected:
    void start(AbstractThreadPool::Task task) const
    {
        this->tasks.Push(task);
    }


private:
    std::vector<std::thread> pool;

    class TaskQueue
    {
    public:
        void Push(AbstractThreadPool::Task task);
        AbstractThreadPool::Task Pop();
        void close();
    private:
        mutable std::queue<AbstractThreadPool::Task> q;
        std::mutex mtx;
        std::condition_variable notEmpty;
        bool closed = false;
    };
    mutable TaskQueue tasks;
};

} // namespace concurrent
#endif // EVENTTHREADPOOL_H
