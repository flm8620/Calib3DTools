#include "distortionmodel.h"
#include <QDebug>

DistortionModel::DistortionModel(QObject *parent, Distortion *core)
    :QAbstractListModel(parent)
{
    if(core!=NULL) {
        this->coreData = core;
        this->coreDisposingRequired = false;
    } else {
        this->coreData = new Distortion();
        this->coreDisposingRequired = true;
    }
    connect( this->coreData, SIGNAL(dataChanged(int,int)), this, SLOT(onCoreDataChanged(int,int)) );
    connect( this->coreData, SIGNAL(dataSizeChanged(int)), this, SLOT(onCoreSizeChanged()) );
}

void DistortionModel::onCoreDataChanged(int fromIndex, int toIndex)
{
    emit this->dataChanged(this->index(fromIndex), this->index(toIndex));
}

void DistortionModel::onCoreSizeChanged()
{
    this->beginResetModel();
    this->endResetModel();
}

int DistortionModel::rowCount(const QModelIndex &index) const
{
    return this->coreData->size();
}

const static QVariant INVALID_QVARIANT;
const static double INVALID_DOUBLE = -100000000000;

QVariant DistortionModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || (role!=Qt::DisplayRole && role!=Qt::EditRole))
        return INVALID_QVARIANT;

    double result = this->coreData->value(index.row(), INVALID_DOUBLE);
    return result!=INVALID_DOUBLE ? QVariant(result) : INVALID_QVARIANT;
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
    if(row<0||row>=coreData->size())return false;
    if(role==Qt::DisplayRole){
        (*coreData)[row]=value.toDouble();
        return true;
    }
    return false;
}

bool DistortionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(row<0||row>coreData->size())return false;
    beginInsertRows(parent,row,row+count-1);
    for(int i=0;i<count;i++){
        coreData->insert(row,0);
    }
    endInsertRows();
    return true;
}

bool DistortionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row<0||row+count-1>=coreData->size())return false;
    beginRemoveRows(parent,row,row+count-1);
    for(int i=0;i<row;++i){
        coreData->remove(row);
    }
    endRemoveRows();
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
