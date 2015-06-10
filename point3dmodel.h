#ifndef POINT3DMODEL_H
#define POINT3DMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QMutex>
#include <QWaitCondition>
#include "target3d.h"

class Point3DModel : public QStandardItemModel, public Target3DContainer
{
    Q_OBJECT
public:
    Point3DModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();
    int pointCount();
    Target3D getTarget3D_threadSafe();
    void saveTarget3D_threadSafe(const Target3D& target3D);
signals:
    void requestGet();
    void requestSave(const Target3D& target3D);
private slots:
    void prepareTarget3D();
    void saveTarget3D(const Target3D& target3D);
private:
    QMutex mutex;
    QWaitCondition conditionGet;
    QWaitCondition conditionSave;
    Target3D preparedTarget3D;//locked by mutex
};

#endif // POINT3DMODEL_H
