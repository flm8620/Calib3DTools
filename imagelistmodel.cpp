#include "imagelistmodel.h"
#include <QImage>
ImageListModel::ImageListModel(QObject *parent)
    :QAbstractListModel(parent)
{

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



