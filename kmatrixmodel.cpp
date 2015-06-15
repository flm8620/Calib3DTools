#include "kmatrixmodel.h"

#include <QDebug>

typedef double (KMatrix::*KMemberGetter)() const;
typedef void (KMatrix::*KMemberSetter)(double);

const static char * const ITEM_NAMES[] = { "fx", "fy", "x0", "y0", "s" };
const static int ITEM_COUNT = sizeof(ITEM_NAMES) / sizeof(ITEM_NAMES[0]);
const static KMemberGetter ITEM_GETTERS[] = { &KMatrix::fx, &KMatrix::fy, &KMatrix::x0, &KMatrix::y0, &KMatrix::s };
const static KMemberSetter ITEM_SETTERS[] = { &KMatrix::setFx, &KMatrix::setFy, &KMatrix::setX0, &KMatrix::setY0, &KMatrix::setS };
const static Qt::ItemFlags ITEM_FLAGS = Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
const static QVariant INVALID_VARIANT;

static inline bool inDataRange(int index)  { return index>=0 && index<ITEM_COUNT; }

KMatrixModel::KMatrixModel(QObject *parent, KMatrix* core)
    :QAbstractListModel(parent)
{
    if(core!=NULL) {
        this->coreData = core;
        this->coreDisposingRequired = false;
    } else {
        this->coreData = new KMatrix();
        this->coreDisposingRequired = true;
    }
    connect( this->coreData, SIGNAL(dataChanged()), this, SLOT(onCoreDataChanged()) );
}

KMatrixModel::~KMatrixModel() {
    if( this->coreDisposingRequired && this->coreData!=NULL ) {
        delete this->coreData;
        this->coreData = NULL;
    }
}

void KMatrixModel::onCoreDataChanged()
{
    emit this->dataChanged(this->index(0), this->index(ITEM_COUNT-1));
}

KMatrix *KMatrixModel::core() {
    return this->coreData;
}

int KMatrixModel::rowCount(const QModelIndex &) const
{
    return ITEM_COUNT;
}

QVariant KMatrixModel::data(const QModelIndex &index, int role) const
{
    return
            index.isValid() && inDataRange(index.row()) &&
                    (role==Qt::DisplayRole || role==Qt::EditRole) ?
            (this->coreData->*(ITEM_GETTERS[index.row()]))() :
            // effect as: row==0 ? this->coreData->fx() : ==1 ? this->coreData->fy() : ==2 ....
            INVALID_VARIANT ;
}

Qt::ItemFlags KMatrixModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? ITEM_FLAGS : Qt::ItemFlags(0);
}

bool KMatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
    if(role!=Qt::EditRole)
        return false;

    bool valueOk;
    double dValue = value.toDouble(&valueOk);
    if(!valueOk)
        return false;

    int row=index.row();
    if(!inDataRange(row))
        return false;

    (this->coreData->*(ITEM_SETTERS[row]))(dValue);
    //effect as: row==0 ? coreData->setFx(dValue) : ==1 ? coreData->setFy(dValue) : ==2? ......

    return true;
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
    return
            role==Qt::DisplayRole && orientation==Qt::Vertical ?
                tr( ITEM_NAMES[section] ) :
                INVALID_VARIANT;
}
