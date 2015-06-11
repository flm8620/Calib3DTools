#ifndef TARGET2D_H
#define TARGET2D_H

#include <QtCore>
#include <QPointF>

class Target2D : public  QList<QList<QPointF> >
{
public:
    inline int pointCount(){ return this->isEmpty() ? 0 : this->first().size(); }
};
Q_DECLARE_METATYPE(Target2D)


class Target2DContainer
{
public:
    virtual Target2D getTarget2D_threadSafe() =0;
    virtual void saveTarget2D_threadSafe(const Target2D& target2D) =0;
    virtual bool isEmpty() =0;
};

#endif // TARGET2D_H

