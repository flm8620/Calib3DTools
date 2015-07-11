#ifndef ABSTRACTTHREADPOOL_H
#define ABSTRACTTHREADPOOL_H

namespace concurrent {


class Runnable
{
public:
    virtual ~Runnable() {}
    virtual void run() =0;
    virtual void done() {}
};

class FutureInterface
{
public:
    virtual ~FutureInterface() {}
    virtual bool isResultReady() =0;
    virtual void waitFor(int milliSeconds) =0;
};

/**
 * @brief The Callable is a Runnable with return value which wrapped by a Future object.
 */
class Callable : public Runnable
{
public:
    virtual ~Callable() {}
    virtual FutureInterface* future() =0;
};

/**
 * @brief A function without any parameter or return value called Procedure.
 */
typedef void (*Procedure)(void *);

/**
 * @brief The AbstractThreadPool class is an interface of an implementor object
 * which promises to run the task, you start()ed, in another thread already
 * prepared before. The done Procedure, if specified, would be called when the task done.
 */
class AbstractThreadPool {
protected:
    /**
     * @brief a Task, the struct, presents a main Procedure which perform the
     * major work of your task, and a done Procedure would be called after
     * the major work done. You can do some clean works in the done Procedure, or
     * simply leave it null;
     */
    struct Task
    {
        Procedure main;
        Procedure done;
        void * hint;
        inline bool isNull() { return this->main==nullptr; }
        inline operator bool() { return !this->isNull(); }
    };

    const static Task NullTask;

private:
    /**
     * @brief compose a Task struct to run the specified Runnable object.
     * @param runnable, the Runnable object specified to run.
     * @return the Task struct.
     */
    static Task task(Runnable& runnable);

protected:

    virtual void start(Task task) const =0;
public:
    inline void start( Runnable& runnable ) const
    {
        this->start( task(runnable) );
    }
    inline FutureInterface* start( Callable& callable ) const
    {
        FutureInterface* result = callable.future();
        this->start( task(callable) );
        return result;
    }
};

} //namespace concurrent
#endif // ABSTRACTTHREADPOOL_H

