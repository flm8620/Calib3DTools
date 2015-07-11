#include "abstractthreadpool.h"

namespace concurrent {


const AbstractThreadPool::Task AbstractThreadPool::NullTask = {nullptr, nullptr, nullptr};

static void runnableMain(Runnable * runnable) { runnable->run(); }
static void runnableDone(Runnable * runnable) { runnable->done(); }

AbstractThreadPool::Task AbstractThreadPool::task(Runnable &runnable)
{
    return
    {
        reinterpret_cast<void(*)(void*)>(&runnableMain),
        reinterpret_cast<void(*)(void*)>(&runnableDone),
        &runnable
    };
}


} //namespace concurrent

