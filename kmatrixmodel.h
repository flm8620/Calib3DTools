#ifndef KMATRIXMODEL_H
#define KMATRIXMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QMutex>
#include <QWaitCondition>
#include "kmatrix.h"

class KMatrixModel : public QAbstractListModel, public KMatrixContainer
{
    Q_OBJECT
public:
    KMatrixModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();
    KMatrix getKMatrix_threadSafe();
    void saveKMatrix_threadSafe(const KMatrix& value);

    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
signals:
    void requestGet();
    void requestSave(const KMatrix& K);
private slots:
    void prepareKMatrix();
    void saveKMatrix(const KMatrix& K);
private:
    double fx,fy,x0,y0,s;
    QMutex mutex;
    QWaitCondition conditionGet;
    QWaitCondition conditionSave;
    KMatrix preparedK;//locked by mutex

};

#endif // KMATRIXMODEL_H
