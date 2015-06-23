#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QtCore>
#include <QtGui>
#include "imagelist.h"

class ImageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ImageListModel(QObject *parent = 0);
    bool isEmpty();

    ImageList getImageList_threadSafe();
    void saveImageList_threadSafe(const ImageList &list);
    int rowCount(const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void storeImage(const QString &name, const QImage &image);
    ImageList *core();
public slots:
    void onCoreDataChanged();

private:
    ImageList *coreData;
    QMutex mutex;
};

#endif // IMAGELISTMODEL_H
