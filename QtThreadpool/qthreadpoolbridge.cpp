#include "qthreadpoolbridge.h"


class QThreadpoolBridge::QRunnableTask : public QRunnable
{
private:
    concurrent::AbstractThreadPool::Task core;
public:
    QRunnableTask(concurrent::AbstractThreadPool::Task task)
        :core(task)
    {
        this->setAutoDelete(true);
    }

    void run() {
        this->core.main(this->core.hint);
        if(this->core.done!=nullptr)
            this->core.done(this->core.hint);
    }
};

QThreadpoolBridge::QThreadpoolBridge(QThreadPool *core) : core(core)
{

}

void QThreadpoolBridge::start(concurrent::AbstractThreadPool::Task task) const {
    if(this->core==nullptr)
        this->core = QThreadPool::globalInstance();

    this->core->start(new QRunnableTask(task));
}

QThreadpoolBridge QThreadpoolBridge::DEFAULT;
