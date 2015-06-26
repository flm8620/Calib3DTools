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
    void setCoreData(ImageList *core);
    bool isEmpty();

    int rowCount(const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void storeImage(const QString &name, const QImage &image);
    ImageList *core();
    void moveUp(int index);
    void moveDown(int index);
    void clear();
    void deleteImage(int index);
    void appendImage(const QString& name,const QImage& image);
public slots:
    void onCoreDataChanged();

private:
    ImageList *coreData;
    QMutex mutex;
};

#endif // IMAGELISTMODEL_H
