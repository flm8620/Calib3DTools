#include "point2dmodel.h"
#include "imagelistmodel.h"

#include <QDebug>
/**
 * Tree structure of this model:
 *    root
 *      |
 *      |-Image 0
 *      |   |--Point 0: x, y
 *      |   |--Point 1: x, y
 *      |-Image 1
 *          |--Point 0: x, y
 *          |--Point 1: x, y
 */
static const quintptr rootId = 0;
Point2DModel::Point2DModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    this->coreData = new ImageListWithPoint2D(this);
    connect(this->coreData, SIGNAL(pointChanged(int, int)), this, SLOT(onPointChanged(int, int)));
    connect(this->coreData, SIGNAL(pointRemoved(int)), this, SLOT(onPointRemoved(int)));
    connect(this->coreData, SIGNAL(pointAppended()), this, SLOT(onPointAppended()));
    connect(this->coreData, SIGNAL(pointSwaped(int, int)), this, SLOT(onPointSwaped(int, int)));
    connect(this->coreData, SIGNAL(imageChanged(int)), this, SLOT(onImageChanged(int)));
    connect(this->coreData, SIGNAL(imageAppended()), this, SLOT(onImageAppended()));
    connect(this->coreData, SIGNAL(dataReset()), this, SLOT(onDataReset()));
}

void Point2DModel::clear()
{
    this->coreData->clearPoint();
}

void Point2DModel::setCoreData(ImageListWithPoint2D *core)
{
    if (this->coreData) {
        disconnect(this->coreData, SIGNAL(pointChanged(int, int)), this,
                   SLOT(onPointChanged(int, int)));
        disconnect(this->coreData, SIGNAL(pointRemoved(int)), this, SLOT(onPointRemoved(int)));
        disconnect(this->coreData, SIGNAL(pointAppended()), this, SLOT(onPointAppended()));
        disconnect(this->coreData, SIGNAL(pointSwaped(int, int)), this, SLOT(onPointSwaped(int,
                                                                                           int)));
        disconnect(this->coreData, SIGNAL(imageChanged(int)), this, SLOT(onImageChanged(int)));
        disconnect(this->coreData, SIGNAL(imageAppended()), this, SLOT(onImageAppended()));
        disconnect(this->coreData, SIGNAL(dataReset()), this, SLOT(onDataReset()));
        if (this->coreData->parent() == this || this->coreData->parent() == 0)
            delete this->coreData;
    }

    this->coreData = core;
    connect(this->coreData, SIGNAL(pointChanged(int, int)), this, SLOT(onPointChanged(int, int)));
    connect(this->coreData, SIGNAL(pointRemoved(int)), this, SLOT(onPointRemoved(int)));
    connect(this->coreData, SIGNAL(pointAppended()), this, SLOT(onPointAppended()));
    connect(this->coreData, SIGNAL(pointSwaped(int, int)), this, SLOT(onPointSwaped(int, int)));
    connect(this->coreData, SIGNAL(imageChanged(int)), this, SLOT(onImageChanged(int)));
    connect(this->coreData, SIGNAL(imageAppended()), this, SLOT(onImageAppended()));
    connect(this->coreData, SIGNAL(dataReset()), this, SLOT(onDataReset()));
    // (*this) doesn't own the new core
}

int Point2DModel::pointCount() const
{
    return this->coreData->pointCount();
}

QImage Point2DModel::getImage(int row) const
{
    return this->coreData->getImage(row);
}

void Point2DModel::removePoint(QModelIndex &index)
{
    if (this->indexMeansPoint(index))
        this->coreData->removePoint(index.row());
}

void Point2DModel::movePointUp(QModelIndex &index)
{
    if (this->indexMeansPoint(index))
        this->coreData->movePointUp(index.row());
}

void Point2DModel::movePointDown(QModelIndex &index)
{
    if (this->indexMeansPoint(index))
        this->coreData->movePointDown(index.row());
}

void Point2DModel::appendPoint()
{
    this->coreData->appendPoint();
}

int Point2DModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return this->coreData->size();
    else if (this->indexMeansImage(parent))
        return this->coreData->pointCount();
    else
        return 0;
}

int Point2DModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 3;
    else if (this->indexMeansImage(parent))
        return 3;
    else
        return 0;
}

QVariant Point2DModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        if (this->indexMeansImage(index)) {
            if (index.column() == 0)
                return this->coreData->getName(index.row());
        } else {
            int idximg = (int)index.internalId()-1;
            QPointF p = this->coreData->getPoint(idximg, index.row());
            switch (index.column()) {
            case 0:
                return QString("Point %1").arg(index.row()+1);
            case 1:
                return p.x();
            case 2:
                return p.y();
            }
        }
    }
    return QVariant();
}

bool Point2DModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        if (this->indexMeansPoint(index)) {
            int idximg = (int)index.internalId()-1;
            QPointF p = this->coreData->getPoint(idximg, index.row());
            if (index.column() == 1) p.setX(qvariant_cast<double>(value));
            if (index.column() == 2) p.setY(qvariant_cast<double>(value));
            this->coreData->setPoint(idximg, index.row(), p);
            return true;
        }
    }
    return false;
}

QVariant Point2DModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Image");
            break;
        case 1:
            return tr("X");
            break;
        case 2:
            return tr("Y");
            break;
        default:
            break;
        }
    }
    return QVariant();
}

ImageListWithPoint2D *Point2DModel::core()
{
    return this->coreData;
}

QModelIndex Point2DModel::index(int row, int column, const QModelIndex &parent) const
{
    // here we use the internalId as a parent Identifier
    if (!parent.isValid()) {
        return this->createIndex(row, column, rootId);
    } else if (this->indexMeansImage(parent)) {
        quintptr rowImagePlusOne = parent.row()+1;
        return this->createIndex(row, column, rowImagePlusOne);
    }
}

QModelIndex Point2DModel::parent(const QModelIndex &child) const
{
    if (this->indexMeansImage(child)) {
        return QModelIndex();
    } else if (this->indexMeansPoint(child)) {
        int imageRow = child.internalId()-1;
        return this->createIndex(imageRow, 0, rootId);
    }
    return QModelIndex();
}

Qt::ItemFlags Point2DModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (this->indexMeansPoint(index))
            if (index.column() >= 1 && index.column() <= 2)
                return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    }
    return 0;
}

void Point2DModel::onPointChanged(int indexImg, int indexPoint)
{
    QModelIndex imgId = this->index(indexImg, 0);
    QModelIndex ptId1 = this->index(indexPoint, 1, imgId);
    QModelIndex ptId2 = this->index(indexPoint, 2, imgId);
    emit dataChanged(ptId1, ptId2);
}

void Point2DModel::onPointRemoved(int indexPoint)
{
    for (int i = 0; i < this->coreData->size(); ++i) {
        QModelIndex imgId = this->index(i, 0);
        beginRemoveRows(imgId, indexPoint, indexPoint);
        endRemoveRows();
    }
}

void Point2DModel::onPointAppended()
{
    int first = this->coreData->pointCount();
    for (int i = 0; i < this->coreData->size(); ++i) {
        QModelIndex imgId = this->index(i, 0);
        beginInsertRows(imgId, first, first);
        endInsertRows();
    }
}

void Point2DModel::onPointSwaped(int indexPoint1, int indexPoint2)
{
    for (int i = 0; i < this->coreData->size(); ++i) {
        QModelIndex imgId = this->index(i, 0);
        QModelIndex ptId1 = this->index(indexPoint1, 1, imgId);
        QModelIndex ptId2 = this->index(indexPoint2, 2, imgId);
        emit dataChanged(ptId1, ptId2);
    }
}

void Point2DModel::onImageChanged(int indexImg)
{
    QModelIndex imgId = this->index(indexImg, 0);
    emit dataChanged(imgId, imgId);
}

void Point2DModel::onImageAppended()
{
    int size = this->coreData->size();
    beginInsertRows(QModelIndex(), size, size);
    endInsertRows();
}

void Point2DModel::onDataReset()
{
    beginResetModel();
    endResetModel();
}

bool Point2DModel::indexMeansImage(const QModelIndex &index) const
{
    return index.isValid() && index.internalId() == rootId;
}

bool Point2DModel::indexMeansPoint(const QModelIndex &index) const
{
    return index.isValid() && index.internalId() > rootId;
}
