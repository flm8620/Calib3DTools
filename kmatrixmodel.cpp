#include "kmatrixmodel.h"

#include <QDebug>
KMatrixModel::KMatrixModel(QObject *parent)
    :QAbstractListModel(parent)
{
    fx=fy=s=x0=y0=0;
    connect(this,SIGNAL(requestGet()),this,SLOT(prepareKMatrix()));
    connect(this,SIGNAL(requestSave(KMatrix)),this,SLOT(saveKMatrix(KMatrix)));
}

bool KMatrixModel::isEmpty()
{
    return fx==0&&fy==0&&s==0&&x0==0&&y0==0;
}

void KMatrixModel::makeEmpty()
{
    for(int i=0;i<5;i++){
        QModelIndex id=index(i,0);
        setData(id,0);
    }
}

KMatrix KMatrixModel::getKMatrix_threadSafe()
{
    QMutexLocker locker(&mutex);
    qDebug()<<"K: emit requestGet();";
    emit requestGet();
    qDebug()<<"conditionGet.wait(&mutex);";
    conditionGet.wait(&mutex);
    qDebug()<<"waked up by conditionGet";
    return preparedK;
    //auto-unlock by locker
}

void KMatrixModel::saveKMatrix_threadSafe(const KMatrix& value)
{
    QMutexLocker locker(&mutex);
    qDebug()<<"K: emit requestSave(K);";
    emit requestSave(value);
    qDebug()<<"conditionSave.wait(&mutex);";
    conditionSave.wait(&mutex);
    qDebug()<<"waked up by conditionSave";
    //auto-unlock by locker
}

int KMatrixModel::rowCount(const QModelIndex &) const
{
    return 5;
}

QVariant KMatrixModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    int row=index.row();
    if(role==Qt::DisplayRole||role==Qt::EditRole){
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
    if(!index.isValid())
        return false;

    int row=index.row();
    if(row<0||row>=5)
        return false;

    if(role!=Qt::EditRole)
        return false;

    switch (row) {
    case 0:
        fx=value.toDouble();
        return true;
    case 1:
        fy=value.toDouble();
        return true;
    case 2:
        x0=value.toDouble();
        return true;
    case 3:
        y0=value.toDouble();
        return true;
    case 4:
        s=value.toDouble();
        return true;
    default:
        return false;
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

void KMatrixModel::prepareKMatrix()
{
    QMutexLocker locker(&mutex);
    double k[5] = {
        data(index(0)).toDouble(),
        data(index(1)).toDouble(),
        data(index(2)).toDouble(),
        data(index(3)).toDouble(),
        data(index(4)).toDouble()};
    preparedK = k;
    conditionGet.wakeAll();
}

void KMatrixModel::saveKMatrix(const KMatrix& K)
{
    QMutexLocker locker(&mutex);
    setData( index(0), K.fx() );
    setData( index(1), K.fy() );
    setData( index(2), K.x0() );
    setData( index(3), K.y0() );
    setData( index(4), K.s() );
    conditionSave.wakeAll();
}

