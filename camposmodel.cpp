#include "camposmodel.h"
const static Qt::ItemFlags ITEM_FLAGS = Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
const static QVariant INVALID_VARIANT;
CamPosModel::CamPosModel(QObject *parent) : QAbstractItemModel(parent)
{
    this->coreData = new CameraPos(this);
    connect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
}

void CamPosModel::setCoreData(CameraPos *core)
{
    if (this->coreData) {
        disconnect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
        if (this->coreData->parent() == this || this->coreData->parent() == 0)
            delete this->coreData;
    }
    this->coreData = core;
    connect(this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()));
    // (*this) doesn't own the new core
}

CameraPos *CamPosModel::core()
{
    return this->coreData;
}

void CamPosModel::clear()
{
    this->coreData->clear();
}

int CamPosModel::rowCount(const QModelIndex &) const
{
    return this->coreData->size()*4;
}

int CamPosModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant CamPosModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        int col = index.column();
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            int camNum=row/4;
            int rowInCam=row%4;
            if(rowInCam<3){
                return this->coreData->RMatrixElement(camNum,rowInCam,col);
            }else if(rowInCam==3){
                return this->coreData->centerVector(camNum,col);
            }
        }
    }
    return INVALID_VARIANT;
}

Qt::ItemFlags CamPosModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? ITEM_FLAGS : Qt::ItemFlags(0);
}

bool CamPosModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid()) {
        int row = index.row();
        int col = index.column();
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            int camNum=row/4;
            int rowInCam=row%4;
            if(rowInCam<3){
                this->coreData->setRMatrixElement(camNum,rowInCam,col,value.toDouble());
                return true;
            }else if(rowInCam==3){
                this->coreData->setCenterVector(camNum,col,value.toDouble());
                return true;
            }
        }
    }
    return false;
}

QVariant CamPosModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Vertical) {
        switch (section%4) {
        case 0:
        case 1:
        case 2:
            return tr("R%1").arg(section/4+1);
        case 3:
            return tr("C%1").arg(section/4+1);
        }
    }
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return "x";
        case 1:
            return "y";
        case 2:
            return "z";
        }
    }
    return INVALID_VARIANT;
}

QModelIndex CamPosModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column);
    else
        return QModelIndex();
}

QModelIndex CamPosModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

void CamPosModel::onCoreDataChanged()
{
    beginResetModel();
    endResetModel();
}
