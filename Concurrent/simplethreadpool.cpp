#include "simplethreadpool.h"
#include <thread>
#include <functional>
#include <algorithm>

namespace concurrent {

using std::thread;
using std::for_each;
using std::mem_fn;

SimpleThreadPool SimpleThreadPool::DEFAULT;

SimpleThreadPool::SimpleThreadPool(int threads) : pool(threads)
{
    for_each(this->pool.begin(), this->pool.end(),
                [this](thread& th)
                {
                    th = thread(
                            [this]()
                            {
                                while(auto task=this->tasks.Pop())
                                {
                                    task.main(task.hint);
                                    if(task.done!=nullptr)
                                        task.done(task.hint);
                                }
                            });
                });
}

SimpleThreadPool::~SimpleThreadPool()
{
    this->tasks.close();
    for_each(this->pool.begin(), this->pool.end(), mem_fn(&thread::join));
}

typedef std::unique_lock<std::mutex> UniqueLock;

void SimpleThreadPool::TaskQueue::Push(AbstractThreadPool::Task task)
{
    UniqueLock lock(this->mtx);
    if (!this->closed) {
        this->q.push(task);
        this->notEmpty.notify_all();
    }
}

AbstractThreadPool::Task SimpleThreadPool::TaskQueue::Pop()
{
    UniqueLock lock(this->mtx);
    while (!closed && this->q.size() <= 0)
        this->notEmpty.wait(lock);

    if (!this->q.empty()) {
        AbstractThreadPool::Task result = this->q.front();
        this->q.pop();
        return result;
    } else {
        return NullTask;
    }
}

void SimpleThreadPool::TaskQueue::close()
{
    UniqueLock lock(this->mtx);
    this->closed = true;
    this->notEmpty.notify_all();
}

}
