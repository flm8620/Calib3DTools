#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QtCore>
#include <QtGui>
#include "imagelist.h"

class ImageListModel : public QAbstractListModel, public ImageListContainer
{
    Q_OBJECT
public:
    ImageListModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();

    ImageList getImageList_threadSafe();
    void saveImageList_threadSafe(const ImageList& list);
    int rowCount(const QModelIndex & index=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent=QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent=QModelIndex());
public slots:

signals:
    void requestSave(const ImageList& list);
    void requestGet();
private slots:
    void prepareImageList();
    void saveImageList(const ImageList& list);

private:
    ImageList imageList;
    QList<QString> imageName;
    QMutex mutex;
    QWaitCondition conditionGet;
    QWaitCondition conditionSave;
    ImageList preparedList;//locked by mutex
};

#endif // IMAGELISTMODEL_H
