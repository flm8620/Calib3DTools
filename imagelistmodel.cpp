#include "imagelistmodel.h"
#include <QImage>
#include <QDebug>
#include <QThread>

ImageListModel::ImageListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    this->coreData = new ImageList(this);
    connect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
}

void ImageListModel::setCoreData(ImageList *core)
{
    disconnect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
    delete this->coreData;
    this->coreData = core;
    connect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
    // (*this) doesn't own the new core
}

bool ImageListModel::isEmpty()
{
    return this->coreData->isEmpty();
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

void ImageListModel::storeImage(const QString &name, const QImage &image)
{
    coreData->append(name, image);
}

ImageList *ImageListModel::core()
{
    return this->coreData;
}

void ImageListModel::moveUp(const QModelIndex &index)
{
    this->coreData->moveUp(index.row());
}

void ImageListModel::moveDown(const QModelIndex &index)
{
    this->coreData->moveDown(index.row());
}

void ImageListModel::clear()
{
    this->coreData->clear();
}

void ImageListModel::deleteImage(int index)
{
    this->coreData->remove(index);
}

void ImageListModel::appendImage(const QString &name, const QImage &image)
{
    this->coreData->append(name, image);
}

void ImageListModel::onCoreDataChanged()
{
    beginResetModel();
    endResetModel();
}
