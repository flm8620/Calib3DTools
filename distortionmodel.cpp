#include "distortionmodel.h"
#include <QDebug>
#include <limits>

using event::_1_;
using event::_2_;

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

    this->subscriptions<<
            this->coreData->dataChangedEvent.subscribe(
                this, &DistortionModel::onCoreDataChanged, _1_, _2_ );

    this->subscriptions<<
            this->coreData->dataSizeChangedEvent.subscribe(
                this, &DistortionModel::onCoreSizeChanged, _1_ );
}

DistortionModel::~DistortionModel()
{
    //close all event subscribings.
    foreach(event::EventConnection* conn, this->subscriptions)
        if(conn!=NULL)
            conn->close();
    this->subscriptions.clear();

    // dispose the coreData if needed.
    if(this->coreDisposingRequired && this->coreData!=NULL) {
        delete this->coreData;
        this->coreData = NULL;
    }
}


void DistortionModel::onCoreDataChanged(int fromIndex, int toIndex)
{
    emit this->dataChanged(this->index(fromIndex), this->index(toIndex));
}

void DistortionModel::onCoreSizeChanged(int newSize )
{
    this->beginResetModel();
    this->endResetModel();
}

int DistortionModel::rowCount(const QModelIndex &index) const
{
    return this->coreData->size();
}

const static QVariant INVALID_QVARIANT;
const static double INVALID_DOUBLE = std::numeric_limits<double>::min();

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
    return false;
}

bool DistortionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

QVariant DistortionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)return QVariant();
    if(orientation==Qt::Vertical){
        return tr("x^%1").arg(section*2+2);
    }
    return QVariant();
}
