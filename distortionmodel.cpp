#include "distortionmodel.h"
#include <QDebug>
DistortionModel::DistortionModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    connect(this, SIGNAL(requestGet()), this, SLOT(prepareDistortion()));
    connect(this, SIGNAL(requestSave(Distortion)), this, SLOT(saveDistortion(Distortion)));
}

bool DistortionModel::isEmpty()
{
    return rowCount() == 0;
}

void DistortionModel::makeEmpty()
{
    beginResetModel();
    modelData.clear();
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
    // auto-unlock by locker
}

void DistortionModel::saveDistortion_threadSafe(const Distortion &dist)
{
    QMutexLocker locker(&mutex);
    qDebug()<<"Dist: emit requestSave();";
    emit requestSave(dist);
    qDebug()<<"conditionSave.wait(&mutex);";
    conditionSave.wait(&mutex);
    qDebug()<<"waked up by conditionSave";
    // auto-unlock by locker
}

int DistortionModel::rowCount(const QModelIndex &) const
{
    return modelData.size();
}

int DistortionModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant DistortionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0)
            return modelData.xParam(row);
        if (col == 1)
            return modelData.yParam(row);
    }
    return QVariant();
}

Qt::ItemFlags DistortionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return 0;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

bool DistortionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;
    int row = index.row();
    int col = index.column();
    if (row < 0 || row >= modelData.size()) return false;
    if (col < 0 || col > 1) return false;
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0)
            modelData.setXParam(value.toDouble(), row);
        if (col == 1)
            modelData.setYParam(value.toDouble(), row);
        return true;
    }
    return false;
}

bool DistortionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    // if(row<0||row>para.size())return false;
    // beginInsertRows(parent,row,row+count-1);
    // for(int i=0;i<count;i++){
    // para.insert(row,0);
    // }
    // endInsertRows();
    // return true;
    return false;
}

bool DistortionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    // if(row<0||row+count-1>=para.size())return false;
    // beginRemoveRows(parent,row,row+count-1);
    // for(int i=0;i<row;++i){
    // para.removeAt(row);
    // }
    // return true;
    return false;
}

QVariant DistortionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Vertical) {
        int x, y;
        modelData.XYfromIdx(section, x, y);
        return tr("x^%1*y^%2").arg(x).arg(y);
    }
    if (orientation == Qt::Horizontal) {
        if (section == 0)
            return tr("xParam");
        if (section == 1)
            return tr("yParam");
    }
    return QVariant();
}

QModelIndex DistortionModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex DistortionModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

void DistortionModel::prepareDistortion()
{
    QMutexLocker locker(&mutex);
    preparedDistortion = modelData;
    conditionGet.wakeAll();
}

void DistortionModel::saveDistortion(const Distortion &value)
{
    QMutexLocker locker(&mutex);
    makeEmpty();
    int rows = value.size();
    beginInsertRows(QModelIndex(), 0, rows-1);
    modelData = value;
    endInsertRows();
    conditionSave.wakeAll();
}
