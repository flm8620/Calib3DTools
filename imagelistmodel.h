#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QImage>
template<typename T> class QList;

class QString;
class ImageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ImageListModel(QObject* parent=0);
    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
public slots:

private:
    QList<QImage> imageList;
    QList<QString> imageName;
};

#endif // IMAGELISTMODEL_H
