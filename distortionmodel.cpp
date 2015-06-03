#include "distortionmodel.h"
#include "solver.h"
#include <QDebug>

DistortionModel::DistortionModel(QObject *parent)
    :QAbstractListModel(parent)
{
    connect(this,SIGNAL(requestGet()),this,SLOT(prepareDistortion()));
    connect(this,SIGNAL(requestSave(Distortion)),this,SLOT(saveDistortion(Distortion)));
}

bool DistortionModel::isEmpty()
{
    return rowCount()==0;
}

void DistortionModel::makeEmpty()
{
    beginResetModel();
    para.clear();
    endResetModel();
}

Distortion DistortionModel::getDistortion_threadSafe()
{
    QMutexLocker locker(&mutex);
    qDebug()<<"Dist: emit requestGet();";
    emit requestGet();
    qDebug()<<"conditionGet.wait(&mutex);";
    conditionGet.wait(&mutex);
    qDebug()<<"waked up by conditionGet";
    return preparedDistortion;
    //auto-unlock by locker
}

void DistortionModel::saveDistortion_threadSafe(const Distortion &dist)
{
    QMutexLocker locker(&mutex);
    qDebug()<<"Dist: emit requestSave();";
    emit requestSave(dist);
    qDebug()<<"conditionSave.wait(&mutex);";
    conditionSave.wait(&mutex);
    qDebug()<<"waked up by conditionSave";
    //auto-unlock by locker
}

int DistortionModel::rowCount(const QModelIndex &index) const
{
    return para.size();
}

QVariant DistortionModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    int row=index.row();
    if(role==Qt::DisplayRole||role==Qt::EditRole){
    return para.value(row);
    }
    return QVariant();
}

Qt::ItemFlags DistortionModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())return 0;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

bool DistortionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())return false;
    int row=index.row();
    if(row<0||row>=para.size())return false;
    if(role==Qt::DisplayRole){
        para[row]=value.toDouble();
        return true;
    }
    return false;
}

bool DistortionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(row<0||row>para.size())return false;
    beginInsertRows(parent,row,row+count-1);
    for(int i=0;i<count;i++){
        para.insert(row,0);
    }
    endInsertRows();
    return true;
}

bool DistortionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row<0||row+count-1>=para.size())return false;
    beginRemoveRows(parent,row,row+count-1);
    for(int i=0;i<row;++i){
        para.removeAt(row);
    }
    return true;
}

QVariant DistortionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)return QVariant();
    if(orientation==Qt::Vertical){
        return tr("x^%1").arg(section*2+2);
    }
    return QVariant();
}

void DistortionModel::prepareDistortion()
{
    QMutexLocker locker(&mutex);
    preparedDistortion.data.clear();
    int rows=rowCount();
    for(int i=0;i<rows;++i){
        QModelIndex id=index(i);
        preparedDistortion.data.append( data(id).toDouble());
    }
    conditionGet.wakeAll();
}

void DistortionModel::saveDistortion(const Distortion &dist)
{
    QMutexLocker locker(&mutex);
    makeEmpty();
    int rows=dist.data.size();
    for(int i=0;i<rows;++i){
        insertRow(i);
        setData(index(i),dist.data.value(i));
    }
    conditionSave.wakeAll();

}
