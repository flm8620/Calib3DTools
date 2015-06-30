#ifndef DISTORTIONMODEL_H
#define DISTORTIONMODEL_H

#include <QtCore>
#include <QAbstractItemModel>
#include "distortion.h"

class DistortionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    DistortionModel(QObject *parent = 0);
    ~DistortionModel();
    Distortion &core();
    void clear();
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

private:
    Distortion coreData;


//    void onCoreDataChanged(int fromIndex, int toIndex);
//    void onCoreSizeChanged(int newSize);
//    QVarLengthArray<event::EventConnection*> subscriptions;
    void onCoreDataChanged();
    event::EventConnection* subscriptions;

};

#endif // DISTORTIONMODEL_H
