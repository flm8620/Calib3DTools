#ifndef STLCALLABLE_H
#define STLCALLABLE_H

#include "abstractthreadpool.h"
#include "messager.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <future>
#include <typeinfo>

namespace concurrent {

template<typename T>
class Future : public FutureInterface
{
public:
    virtual T getResult() =0;
};

template<typename R, typename ... ARGS>
class StlCallable : public Callable
{
    class StlFutureWrapper : public Future<R>
    {
    private:
        std::future<R> core;

    public:
        explicit StlFutureWrapper(std::future<R>&& std)
            : core(std::move(std))
        {
        }

        StlFutureWrapper(StlFutureWrapper& origin) = delete;

        StlFutureWrapper(StlFutureWrapper&& origin)
        {
            std::swap(core, origin);
        }

        R getResult() {
            return this->core.get();
        }

        bool isResultReady()
        {
            return core.wait_for(std::chrono::milliseconds(0))==std::future_status::ready;
        }

        void waitFor(int milliSeconds)
        {
            core.wait_for(std::chrono::milliseconds(milliSeconds));
        }
    };

    std::packaged_task<R()> task;
    void run()
    {
        task();
    }
    void done()
    {
        //BE CAREFUL
        delete this;
    }

public:
    StlCallable(R(*fn)(ARGS...), ARGS... args)
        : task(std::bind(fn, args...)) {}

    StlFutureWrapper* future() {
        return new StlFutureWrapper(this->task.get_future());
    }
};

template<typename RETURN_TYPE, typename ... ARGS>
Future<RETURN_TYPE>* asyncInvoke(const AbstractThreadPool& pool,
                                RETURN_TYPE (*functionPointer)(ARGS...), ARGS... args)
{
    Callable * callable = new StlCallable<RETURN_TYPE, ARGS...>(functionPointer, args... );
    return reinterpret_cast<Future<RETURN_TYPE>*>(pool.start(*callable));
}

template<typename T>
void ReportProgrsAndWaitFtr(std::atomic_int &progress, int total,
                            std::vector<concurrent::Future<T>*> &ftrs)
{
    libMsg::cout <<"[ "<< libMsg::flush;
    int lastPercentage = 0;
    int done, last = 0;

    while (!std::all_of(ftrs.begin(), ftrs.end(),
                        std::mem_fn(&concurrent::Future<T>::isResultReady))) {
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
    }
    libMsg::cout <<"] "<< libMsg::flush;
}

template<typename T>
inline static bool getBoolResult(Future<T> * ftr) { return ftr->getResult(),true; }
inline static bool getBoolResult(Future<bool> * ftr) { return ftr->getResult(); }

template<typename T>
void getFtr_CheckExcpt(bool &allOk, std::vector<Future<T>*> &ftrs)
{
    allOk = true;
    for(int i=0; i<ftrs.size(); i++) {
        try{
            allOk = getBoolResult(ftrs[i]) && allOk;
        }catch (MyException &e) {
            allOk = false;
            libMsg::cout<<"Exception caught in task "<<i<<": "<<libMsg::endl;
            libMsg::cout<<e.what()<<libMsg::endl;
        }catch (...) {
            allOk = false;
            libMsg::cout<<"Unexcepted exception caught in task "<<i<<libMsg::endl;
        }
     }
}


}//namespace concurrent

#endif // STLCALLABLE_H
