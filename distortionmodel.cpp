#include "distortionmodel.h"




DistortionModel::DistortionModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

int DistortionModel::rowCount(const QModelIndex &) const
{
    return para.size();
}

QVariant DistortionModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    int row=index.row();
    if(role==Qt::DisplayRole){
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
        para[row]=value.toInt();
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
