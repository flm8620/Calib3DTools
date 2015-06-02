#ifndef KMATRIXMODEL_H
#define KMATRIXMODEL_H

#include <QObject>
#include <QAbstractListModel>

class KMatrixModel : public QAbstractListModel
{
    Q_OBJECT
public:
    KMatrixModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();

    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    double fx,fy,x0,y0,s;
};

#endif // KMATRIXMODEL_H
