#include "distortionmodel.h"
#include <QDebug>

//using event::_1_;
//using event::_2_;

const static Qt::ItemFlags ITEM_FLAGS = Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
const static Qt::ItemFlags INVALID_ITEM_FLAGS = Qt::ItemFlags(0);
const static QVariant INVALID_VARIANT;

DistortionModel::DistortionModel(QObject *parent) :
    QAbstractItemModel(parent)
{
//    this->subscriptions<<
//            this->coreData.dataChangedEvent.subscribe(
//                this, &DistortionModel::onCoreDataChanged, _1_, _2_ );

//    this->subscriptions<<
//            this->coreData.dataSizeChangedEvent.subscribe(
//                this, &DistortionModel::onCoreSizeChanged, _1_ );
    this->subscriptions =
            this->coreData.dataChangedEvent.subscribe(
                this, &DistortionModel::onCoreDataChanged );

}

DistortionModel::~DistortionModel()
{
    //close event subscribing.
    if(this->subscriptions!=NULL) {
        this->subscriptions->close();
        this->subscriptions=NULL;
    }
}

Distortion & DistortionModel::core()
{
    return this->coreData;
}

void DistortionModel::clear()
{
    this->coreData.clear();
}

int DistortionModel::rowCount(const QModelIndex &) const
{
    return coreData.size();
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
                return coreData.xParam(row);
            if (col == 1)
                return coreData.yParam(row);
        }
    }
    return INVALID_VARIANT;
}

Qt::ItemFlags DistortionModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? ITEM_FLAGS : INVALID_ITEM_FLAGS;
}

bool DistortionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid()) {
        int row = index.row();
        int col = index.column();
        if (row < 0 || row >= coreData.size()) return false;
        if (col < 0 || col > 1) return false;
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (col == 0)
                coreData.setXParam(value.toDouble(), row);
            if (col == 1)
                coreData.setYParam(value.toDouble(), row);
            return true;
        }
    }
    return false;
}

QVariant DistortionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Vertical) {
        int x, y;
        coreData.XYfromIdx(section, x, y);
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
    if (!parent.isValid())
        return createIndex(row, column);
    else
        return QModelIndex();
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
