#ifndef EVENTTHREADPOOL_H
#define EVENTTHREADPOOL_H

#include "abstractthreadpool.h"
#include "messager.h"
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <exception>
#include <list>
namespace concurrent {
class SimpleThreadPool : public AbstractThreadPool
{
private:
    template<typename R, typename ... ARGS>
    class RunnableFunction : public Runnable
    {
    private:
        std::function<R()> func;
        std::promise<R> result;
        template<typename T>
        void run(std::promise<T> &result)
        {
            try{
                result.set_value(func());
            }catch (...) {
                result.set_exception(std::current_exception());
            }
        }

        void run(std::promise<void> &result)
        {
            try{
                func();
                result.set_value();
            }catch (...) {
                result.set_exception(std::current_exception());
            }
        }

    public:
        RunnableFunction(R(*f)(ARGS ...), ARGS ... args) : func(std::bind(f, args ...))
        {
        }

        std::future<R> getFuture()
        {
            return this->result.get_future();
        }

        void run()
        {
            run(result);
        }

        void done()
        {
            delete this;
        }
    };

public:
    SimpleThreadPool(int threads = 5);
    ~SimpleThreadPool();
    void start(Runnable *task) const;
    template<typename R, typename ... ARGS >
    std::future<R> start(R (*f)(ARGS ...), ARGS ... args)
    {
        auto fn = new RunnableFunction<R, ARGS ...>(f, args ...);
        this->start(fn);
        return fn->getFuture();
    }

    static SimpleThreadPool DEFAULT;

private:
    std::vector<std::thread *> pool;

    class TaskQueue
    {
    public:
        void Push(Runnable *t);
        Runnable *Pop();
        void close();
    private:
        mutable std::queue<Runnable *> q;
        std::mutex mtx;
        std::condition_variable notEmpty;
        bool closed = false;
    };
    mutable TaskQueue tasks;
    static void threadMain(TaskQueue *tasks);
};

template<typename T>
void ReportProgrsAndWaitFtr(std::atomic_int &progress, int total,
                            std::vector<std::future<T> > &ftrs)
{
    libMsg::cout <<"[ "<< libMsg::flush;
    int lastPercentage = 0;
    int done, last = 0;
    std::list<std::future<T> * > unfinishedFtr;
    for (int i = 0; i < ftrs.size(); ++i) unfinishedFtr.push_back(&ftrs[i]);

    bool allFinished = false;
    while (!allFinished) {
        done = progress.load(std::memory_order_acquire);
        // libMsg::cout <<"done "<< done<<" last "<<last << libMsg::flush;
        if (last != done) {
            last = done;
            int percent = done *100 / total;
            int percentby4 = percent/4*4;
            if (percentby4 > lastPercentage) {
                lastPercentage = percentby4;
                if (percentby4%20 == 0)
                    libMsg::cout << percentby4 << "% " << libMsg::flush;
                else
                    libMsg::cout <<'.'<< libMsg::flush;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        allFinished = true;
        auto it = unfinishedFtr.begin();
        while (it != unfinishedFtr.end()) {
            if ((*it)->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                it = unfinishedFtr.erase(it);
            } else {
                it++;
                allFinished = false;
                break;
            }
        }
    }
    libMsg::cout <<"] "<< libMsg::flush;
}

void getVoidFtr_CheckExcpt(bool &allOk, std::vector<std::future<void> > &ftrs);
void getBoolFtr_CheckExcpt(bool &allOk, std::vector<std::future<bool> > &ftrs);
} // namespace concurrent
#endif // EVENTTHREADPOOL_H
