#include "simplethreadpool.h"
#include <thread>
#include <functional>
#include <algorithm>


using namespace concurrent;
using std::thread;
using std::for_each;

SimpleThreadPool SimpleThreadPool::DEFAULT;

SimpleThreadPool::SimpleThreadPool(int threads) : pool(threads)
{
    for_each(this->pool.begin(), this->pool.end(), [this](thread*& th){
        th = new thread([this]{
                        for(auto task=this->tasks.Pop();
                            task!=nullptr;
                            task=this->tasks.Pop()) {
                            task->run();
                            task->done();
                        }
                    });
    });
}

SimpleThreadPool::~SimpleThreadPool() {
    this->tasks.close();
    for_each(this->pool.begin(), this->pool.end(),
             [this](thread*& th){
                if(th!=NULL) {
                    th->join();
                    delete th;
                    th = NULL;
                }
             });
}

typedef std::unique_lock<std::mutex> UniqueLock;

void SimpleThreadPool::TaskQueue::Push(Runnable*  t) {
    UniqueLock lock(this->mtx);
    if(!this->closed) {
        this->q.push(t);
        this->notEmpty.notify_all();
    }
}

Runnable* SimpleThreadPool::TaskQueue::Pop() {
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

void SimpleThreadPool::TaskQueue::close() {
    UniqueLock lock(this->mtx);
    this->closed = true;
    this->notEmpty.notify_all();
}
