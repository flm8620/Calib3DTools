#include "point3dmodel.h"
#include <QDebug>
Point3DModel::Point3DModel(QObject *parent)
    :QStandardItemModel(parent)
{
    QStringList list;
    list.append("x");
    list.append("y");
    list.append("z");
    setHorizontalHeaderLabels(list);
    connect(this,SIGNAL(requestGet()),this,SLOT(prepareTarget3D()));
    connect(this,SIGNAL(requestSave(Target3D)),this,SLOT(saveTarget3D(Target3D)));
}

bool Point3DModel::isEmpty()
{
    return rowCount()==0;
}

void Point3DModel::makeEmpty()
{
    beginResetModel();
    if(rowCount()>0)
        removeRows(0,rowCount());
    endResetModel();
}

int Point3DModel::pointCount()
{
    return rowCount();
}

Target3D Point3DModel::getTarget3D_threadSafe()
{
    QMutexLocker locker(&mutex);
    qDebug()<<"3D: emit requestGet();";
    emit requestGet();
    qDebug()<<"conditionGet.wait(&mutex);";
    conditionGet.wait(&mutex);
    qDebug()<<"waked up by conditionGet";
    return preparedTarget3D;
    //auto-unlock by locker
}

void Point3DModel::saveTarget3D_threadSafe(const Target3D &target3D)
{
    QMutexLocker locker(&mutex);
    qDebug()<<"3D: emit requestSave";
    emit requestSave(target3D);
    qDebug()<<"conditionSave.wait(&mutex);";
    conditionSave.wait(&mutex);
    qDebug()<<"waked up by conditionSave";
    //auto-unlock by locker
}

void Point3DModel::prepareTarget3D()
{
    QMutexLocker locker(&mutex);
    int points=rowCount();
    for(int j=0;j<points;j++){
        QVector3D p;
        p.setX(item(j,0)->text().toDouble());
        p.setY(item(j,1)->text().toDouble());
        p.setZ(item(j,2)->text().toDouble());
        preparedTarget3D.append(p);
    }
    conditionGet.wakeAll();
}

void Point3DModel::saveTarget3D(const Target3D &target3D)
{
    QMutexLocker locker(&mutex);
    makeEmpty();
    int points=target3D.size();
    for(int j=0;j<points;j++){
        const QVector3D& p=target3D[j];
        double x=p.x(),y=p.y(),z=p.z();
        QStandardItem *item1=new QStandardItem(QString::number(x));
        QStandardItem *item2=new QStandardItem(QString::number(y));
        QStandardItem *item3=new QStandardItem(QString::number(z));
        QList<QStandardItem*> list;
        list.append(item1);
        list.append(item2);
        list.append(item3);
        appendRow(list);
    }
    conditionSave.wakeAll();
}

