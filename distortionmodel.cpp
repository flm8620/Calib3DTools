#include "distortionmodel.h"
#include <QDebug>

const static Qt::ItemFlags ITEM_FLAGS = Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
const static QVariant INVALID_VARIANT;

DistortionModel::DistortionModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    this->coreData = new Distortion(this);
    this->coreData->setMaxOrder(11);
    connect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
}

Distortion *DistortionModel::core()
{
    return this->coreData;
}


int DistortionModel::rowCount(const QModelIndex &) const
{
    return coreData->size();
}

int DistortionModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant DistortionModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        int col = index.column();
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (col == 0)
                return coreData->xParam(row);
            if (col == 1)
                return coreData->yParam(row);
        }
    }
    return INVALID_VARIANT;
}

Qt::ItemFlags DistortionModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? ITEM_FLAGS : Qt::ItemFlags(0);
}

bool DistortionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid()) {
        int row = index.row();
        int col = index.column();
        if (row < 0 || row >= coreData->size()) return false;
        if (col < 0 || col > 1) return false;
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (col == 0)
                coreData->setXParam(value.toDouble(), row);
            if (col == 1)
                coreData->setYParam(value.toDouble(), row);
            return true;
        }
    }
    return false;
}

bool DistortionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

bool DistortionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

QVariant DistortionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Vertical) {
        int x, y;
        coreData->XYfromIdx(section, x, y);
        return tr("x^%1*y^%2").arg(x).arg(y);
    }
    if (orientation == Qt::Horizontal) {
        if (section == 0)
            return tr("xParam");
        if (section == 1)
            return tr("yParam");
    }
    return INVALID_VARIANT;
}

QModelIndex DistortionModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex DistortionModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

void DistortionModel::onCoreDataChanged()
{
    beginResetModel();
    endResetModel();
}
