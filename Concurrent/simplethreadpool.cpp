#include "simplethreadpool.h"
#include <thread>
#include <functional>
using std::thread;
namespace concurrent {
SimpleThreadPool SimpleThreadPool::DEFAULT;

SimpleThreadPool::SimpleThreadPool(int threads) : pool(threads)
{
    for (int i = 0; i < threads; i++)
        this->pool[i] = new thread(&threadMain, &this->tasks);
}

void SimpleThreadPool::threadMain(TaskQueue *tasks)
{
    Runnable *task;
    while (NULL != (task = tasks->Pop())) {
        task->run();
        task->done();
    }
}

void SimpleThreadPool::start(Runnable *task) const
{
    this->tasks.Push(task);
}

SimpleThreadPool::~SimpleThreadPool()
{
    this->tasks.close();
    for (unsigned i = 0; i < this->pool.size(); i++) {
        thread * &th = this->pool[i];
        if (th != NULL) {
            th->join();
            delete th;
            th = NULL;
        }
    }
}

typedef std::unique_lock<std::mutex> UniqueLock;

void SimpleThreadPool::TaskQueue::Push(Runnable *t)
{
    UniqueLock lock(this->mtx);
    if (!this->closed) {
        this->q.push(t);
        this->notEmpty.notify_all();
    }
}

Runnable *SimpleThreadPool::TaskQueue::Pop()
{
    UniqueLock lock(this->mtx);
    while (!closed && this->q.size() <= 0)
        this->notEmpty.wait(lock);

    if (this->q.size() > 0) {
        Runnable *result = this->q.front();
        this->q.pop();
        return result;
    } else {
        return NULL;
    }
}

void SimpleThreadPool::TaskQueue::close()
{
    UniqueLock lock(this->mtx);
    this->closed = true;
    this->notEmpty.notify_all();
}

void getVoidFtr_CheckExcpt(bool &allOk, std::vector<std::future<void> > &ftrs)
{
    allOk = true;
    for (int i = 0; i < ftrs.size(); ++i) {
        try{
            ftrs[i].get();
        }catch (MyException &e) {
            allOk = false;
            libMsg::cout<<"Exception caught in task "<<i<<": "<<libMsg::endl;
            libMsg::cout<<e.what()<<libMsg::endl;
        }
        catch (...) {
            allOk = false;
            libMsg::cout<<"Unexcepted exception caught in task "<<i<<libMsg::endl;
        }
    }
}

void getBoolFtr_CheckExcpt(bool &allOk, std::vector<std::future<bool> > &ftrs)
{
    allOk = true;
    for (int i = 0; i < ftrs.size(); ++i) {
        try{
            if (!ftrs[i].get())
                allOk = false;
        }catch (MyException &e) {
            allOk = false;
            libMsg::cout<<"Exception caught in task "<<i<<": "<<libMsg::endl;
            libMsg::cout<<e.what()<<libMsg::endl;
        }
        catch (...) {
            allOk = false;
            libMsg::cout<<"Unexcepted exception caught in task "<<i<<libMsg::endl;
        }
    }
}
}
