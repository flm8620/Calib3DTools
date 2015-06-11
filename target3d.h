#ifndef TARGET3D_H
#define TARGET3D_H

#include <QtCore>
#include<QVector3D>

typedef  QList<QVector3D> Target3D;

class Target3DContainer
{
public:
    virtual Target3D getTarget3D_threadSafe() =0;
    virtual void saveTarget3D_threadSafe(const Target3D& target3D) =0;
    virtual bool isEmpty() =0;
};


#endif // TARGET3D_H

