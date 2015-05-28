#include "kmatrixmodel.h"

KMatrixModel::KMatrixModel(QObject *parent)
    :QAbstractListModel(parent)
{
    fx=fy=s=x0=y0=0;
}

int KMatrixModel::rowCount(const QModelIndex &) const
{
    return 5;
}

QVariant KMatrixModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    int row=index.row();
    if(role==Qt::DisplayRole){
        switch (row) {
        case 0:
            return fx;
            break;
        case 1:
            return fy;
            break;
        case 2:
            return x0;
            break;
        case 3:
            return y0;
            break;
        case 4:
            return s;
            break;
        default:
            break;
        }
    }
    return QVariant();
}

Qt::ItemFlags KMatrixModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())return 0;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

bool KMatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())return false;
    int row=index.row();
    if(row<0||row>=5)return false;
    if(role==Qt::EditRole){
        switch (row) {
        case 0:
            fx=value.toInt();
            break;
        case 1:
            fy=value.toInt();
            break;
        case 2:
            x0=value.toInt();
            break;
        case 3:
            y0=value.toInt();
            break;
        case 4:
            s=value.toInt();
            break;
        default:
            return false;
            break;
        }
        return true;
    }
}

bool KMatrixModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

bool KMatrixModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

QVariant KMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)return QVariant();
    if(orientation==Qt::Vertical){
        switch (section) {
        case 0:
            return tr("fx");
            break;
        case 1:
            return tr("fy");
            break;
        case 2:
            return tr("x0");
            break;
        case 3:
            return tr("y0");
            break;
        case 4:
            return tr("s");
            break;
        default:
            return QVariant();
            break;
        }
    }
    return QVariant();
}

