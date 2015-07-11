#ifndef QTHREADPOOLBRIDGE_H
#define QTHREADPOOLBRIDGE_H

#include "abstractthreadpool.h"
#include <QtCore>


class QThreadpoolBridge : public concurrent::AbstractThreadPool
{
    class QRunnableTask;
    mutable QThreadPool *core;
protected:
    void start(concurrent::AbstractThreadPool::Task task) const;
public:
    QThreadpoolBridge(QThreadPool * core =nullptr);

    static QThreadpoolBridge DEFAULT;
};

#endif // QTHREADPOOLBRIDGE_H
