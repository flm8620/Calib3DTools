#include "point3dmodel.h"
#include <QDebug>
Point3DModel::Point3DModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    this->coreData=new Point3D(this);
    connect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
}

Point3D *Point3DModel::core()
{
    return this->coreData;
}

bool Point3DModel::isEmpty()
{
    return this->coreData->isEmpty();
}

void Point3DModel::clear()
{
    this->coreData->clear();
}

int Point3DModel::pointCount()
{
    return this->coreData->pointCount();
}

void Point3DModel::append()
{
    this->coreData->append();
}

void Point3DModel::remove(int index)
{
    this->coreData->remove(index);
}

void Point3DModel::moveUp(const QModelIndex &index)
{
    this->coreData->moveUp(index.row());
}

void Point3DModel::moveDown(const QModelIndex &index)
{
    this->coreData->moveDown(index.row());
}

int Point3DModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()){
        return this->coreData->pointCount();
    }else{
        return 0;
    }
}

int Point3DModel::columnCount(const QModelIndex &parent) const
{
    if(!parent.isValid()){
        return 3;
    }else{
        return 0;
    }
}

QVariant Point3DModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        QVector3D v=this->coreData->getPoint(index.row());
        switch (index.column()) {
        case 0:
            return v.x();
            break;
        case 1:
            return v.y();
            break;
        case 2:
            return v.z();
            break;
        default:
            break;
        }
    }
    return QVariant();
}

bool Point3DModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {


            QVector3D v = this->coreData->getPoint(index.row());
            switch (index.column()) {
            case 0:
                v.setX(qvariant_cast<double>(value));
                break;
            case 1:
                v.setY(qvariant_cast<double>(value));
                break;
            case 2:
                v.setZ(qvariant_cast<double>(value));
                break;
            default:
                return false;
                break;
            }
            this->coreData->setPoint(index.row(), v);
            return true;

    }
    return false;
}
QVariant Point3DModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("X");
            break;
        case 1:
            return tr("Y");
            break;
        case 2:
            return tr("Z");
            break;
        default:
            break;
        }
    }
    return QVariant();
}

QModelIndex Point3DModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column);
    else
        return QModelIndex();
}

QModelIndex Point3DModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

Qt::ItemFlags Point3DModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
    return 0;
}

void Point3DModel::onCoreDataChanged()
{
    beginResetModel();
    endResetModel();
}
