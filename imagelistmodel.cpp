#include "imagelistmodel.h"
#include <QImage>
#include <QDebug>
#include <QThread>

ImageListModel::ImageListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    coreData = new ImageList(this);
    connect(coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
}

bool ImageListModel::isEmpty()
{
    return rowCount() == 0;
}

int ImageListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return coreData->size();
}

QVariant ImageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();

    if (role == Qt::UserRole)
        return coreData->getImage(row);
    if (role == Qt::DisplayRole)
        return coreData->getName(row);
    return QVariant();
}

Qt::ItemFlags ImageListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return 0;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

bool ImageListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;
    int row = index.row();
    if (row < 0 || row >= coreData->size()) return false;
    if (role == Qt::DisplayRole) {
        coreData->setName(row, qvariant_cast<QString>(value));
        return true;
    }
    if (role == Qt::UserRole) {
        coreData->setImage(row, qvariant_cast<QImage>(value));
        return true;
    }
    return false;
}

bool ImageListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

bool ImageListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row+count-1 >= coreData->size()) return false;
    beginRemoveRows(parent, row, row+count-1);
    for (int i = 0; i < count; ++i)
        coreData->remove(row);
    endRemoveRows();
    return true;
}

void ImageListModel::storeImage(const QString& name, const QImage &image)
{
    coreData->append(name,image);
}

ImageList *ImageListModel::core()
{
    return this->coreData;
}

void ImageListModel::onCoreDataChanged()
{
    beginResetModel();
    endResetModel();
}
