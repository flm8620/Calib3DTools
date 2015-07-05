#ifndef EVENTTHREADPOOL_H
#define EVENTTHREADPOOL_H

#include "abstractthreadpool.h"
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace concurrent {


class SimpleThreadPool : public AbstractThreadPool
{
private:
    template<typename R, typename ... ARGS>
    class RunnableFunction : public Runnable {
    private:
        std::function<R()> func;
        std::promise<R> result;
        template<typename T>
        void run(std::promise<T>& result) { result.set_value(func()); }
        void run(std::promise<void>& result) { func(), result.set_value(); }
    public:
        RunnableFunction(R(*f)(ARGS...), ARGS... args) : func(std::bind(f, args...)) {}
        std::future<R> getFuture() { return this->result.get_future();}
        void run() { run(result); }
        void done() { delete this; }
    };

public:
    SimpleThreadPool(int threads=5);
    ~SimpleThreadPool();
    void start( Runnable* task ) const;
    template<typename R, typename ... ARGS >
    std::future<R> start( R(*f)(ARGS...), ARGS... args) {
        auto fn = new RunnableFunction<R,ARGS...>(f, args...);
        this->start(fn);
        return fn->getFuture();
    }

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
