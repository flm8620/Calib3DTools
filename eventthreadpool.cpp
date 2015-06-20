#include "eventthreadpool.h"
#include <thread>
#include <functional>

EventThreadPool::EventThreadPool(int initSize, int maxSize) : pool(initSize)
{
    this->initsize = initSize;
    this->maxsize = maxSize;
    for(int i=0; i<initSize; i++)
        this->pool[i] = new std::thread(&threadMain, &this->tasks);
}

void EventThreadPool::threadMain(TaskQueue* tasks)
{
    Runnable* task;
    while(NULL!= (task=tasks->Pop())) {
        task->run();
        delete task;
    }
}

void EventThreadPool::start(Runnable *task) {
    this->tasks.Push(task);
}

EventThreadPool::~EventThreadPool() {
    this->tasks.close();
    for(unsigned i=0; i<this->pool.size(); i++) {
        std::thread*& th = this->pool[i];
        if(th!=NULL) {
            th->join();
            delete th;
            th = NULL;
        }
    }
}

typedef std::unique_lock<std::mutex> UniqueLock;

void EventThreadPool::TaskQueue::Push(Runnable*  t) {
    UniqueLock lock(this->mtx);
    if(!this->closed) {
        this->q.push(t);
        this->notEmpty.notify_all();
    }
}

Runnable* EventThreadPool::TaskQueue::Pop() {
    UniqueLock lock(this->mtx);
    while(!closed && this->q.size()<=0)
        this->notEmpty.wait(lock);

    if(this->q.size()>0) {
        Runnable*  result = this->q.front();
        this->q.pop();
        return result;
    } else {
        return NULL;
    }
}

void EventThreadPool::TaskQueue::close() {
    UniqueLock lock(this->mtx);
    this->closed = true;
    this->notEmpty.notify_all();
}
