#ifndef SOLVERTHREAD_H
#define SOLVERTHREAD_H

#include <QObject>
#include <QThread>
class SolverThread : public QThread
{
public:
    SolverThread(QObject *parent = 0);
};

#endif // SOLVERTHREAD_H
