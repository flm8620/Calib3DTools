#ifndef CAMPOSMODEL_H
#define CAMPOSMODEL_H
#include <QtCore>
#include <QAbstractItemModel>
#include "camerapos.h"
class CamPosModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    CamPosModel(QObject *parent = 0);
    void setCoreData(CameraPos *core);
    CameraPos *core();
    void clear();
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
private slots:
    void onCoreDataChanged();
private:
    CameraPos *coreData;
};

#endif // CAMPOSMODEL_H
