#include "imagelistmodel.h"
#include <QImage>
#include <QDebug>
#include <QThread>
void function(){

}

ImageListModel::ImageListModel(QObject *parent)
    :QAbstractListModel(parent)
{
    connect(this,SIGNAL(requestGet()),this,SLOT(prepareImageList()),Qt::QueuedConnection);
    connect(this,SIGNAL(requestSave(ImageList)),this,SLOT(saveImageList(ImageList)),Qt::QueuedConnection);
}

bool ImageListModel::isEmpty()
{
    return rowCount()==0;
}

void ImageListModel::makeEmpty()
{
    beginResetModel();
    if(rowCount()>0)
        removeRows(0,rowCount());
    endResetModel();

}


ImageList ImageListModel::getImageList_threadSafe()
{
    QMutexLocker locker(&mutex);
    qDebug()<<"Image: emit requestGet();";
    emit requestGet();
    qDebug()<<"conditionGet.wait(&mutex);";
    conditionGet.wait(&mutex);
    qDebug()<<"waked up by conditionGet";
    return preparedList;
    //auto-unlock by locker
}

void ImageListModel::saveImageList_threadSafe(const ImageList &list)
{
    QMutexLocker locker(&mutex);
    qDebug()<<"Image: emit requestSave(list);";
    emit requestSave(list);
    qDebug()<<"conditionSave.wait(&mutex);";
    conditionSave.wait(&mutex);
    qDebug()<<"waked up by conditionSave";
    //auto-unlock by locker
}

int ImageListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return imageList.size();
}

QVariant ImageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row=index.row();

    if(role==Qt::UserRole){
        return imageList.value(row);
    }
    if(role==Qt::DisplayRole){
        return imageName.value(row);
    }
    return QVariant();
}

Qt::ItemFlags ImageListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())return 0;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

bool ImageListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())return false;
    int row=index.row();
    if(row<0||row>=imageList.size())return false;
    if(role==Qt::DisplayRole){
        imageName[row]=qvariant_cast<QString>(value);
        emit dataChanged(index,index);
        return true;
    }
    if(role==Qt::UserRole){
        imageList[row]=qvariant_cast<QImage>(value);
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

bool ImageListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(row<0||row>imageList.size())return false;
    beginInsertRows(parent,row,row+count-1);
    for(int i=0;i<count;i++){
        imageName.insert(row,"");
        imageList.insert(row,QImage());
    }
    endInsertRows();
    return true;
}

bool ImageListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row<0||row+count-1>=imageList.size())return false;
    beginRemoveRows(parent,row,row+count-1);
    for(int i=0;i<count;++i){
        imageList.removeAt(row);
        imageName.removeAt(row);
    }
    endRemoveRows();
    return true;
}

void ImageListModel::prepareImageList()
{
    QMutexLocker locker(&mutex);
    preparedList.clear();
    int rows=rowCount();
    for(int i=0;i<rows;++i){
        QModelIndex id=index(i);
        preparedList.append( qvariant_cast<QImage>(data(id,Qt::UserRole)));
    }
    conditionGet.wakeAll();
    //auto-unlock by locker
}

void ImageListModel::saveImageList(const ImageList &list)
{
    QMutexLocker locker(&mutex);
    makeEmpty();
    QImage image;
    int i=0;
    foreach (image,list) {
        insertRow(i);
        QModelIndex id=index(i);
        setData(id,tr("Image%1").arg(i),Qt::DisplayRole);
        setData(id,image,Qt::UserRole);
        i++;
    }
    conditionSave.wakeAll();
    //auto-unlock by locker
}



