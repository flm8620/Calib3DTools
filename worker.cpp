#include "worker.h"
#include "imagelistmodel.h"
#include <QDebug>
Worker::Worker(QObject *parent) : QObject(parent)
{

}

Worker::Worker(ImageListModel *model, QObject *parent): QObject(parent)
{
    this->model=model;
}

void Worker::solve()
{
    qDebug()<<"worker: solve()";
    QList<QImage> list= model->getImageList_threadSafe();
    qDebug()<<"got images";
    qDebug()<<list;
}

