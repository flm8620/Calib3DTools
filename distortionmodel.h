#ifndef DISTORTIONMODEL_H
#define DISTORTIONMODEL_H

#include <QObject>
#include <QAbstractListModel>
template<typename T> class QList;
class DistortionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DistortionModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();


    int rowCount(const QModelIndex & index=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::DisplayRole);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QList<double> para;
};

#endif // DISTORTIONMODEL_H
