#ifndef POINT3DMODEL_H
#define POINT3DMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QMutex>
#include <QWaitCondition>
#include "point3d.h"

class Point3DModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    Point3DModel(QObject* parent=0);
    Point3D *core();
    bool isEmpty();
    void clear();
    int pointCount();
    void append();
    void remove(int index);
    void moveUp(const QModelIndex &index);
    void moveDown(const QModelIndex &index);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
private slots:
    void onCoreDataChanged();
private:
    Point3D *coreData;
};

#endif // POINT3DMODEL_H
