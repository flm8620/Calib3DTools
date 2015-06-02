#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
template<typename T> class QList;

class QString;
class ImageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ImageListModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();

    QList<QImage> getImageList();
    QList<QImage> getImageList_threadSafe();
    int rowCount(const QModelIndex & index=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent=QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent=QModelIndex());
public slots:

signals:
    void requestImageList();
private slots:
    void prepareImageList();

private:
    QList<QImage> imageList;
    QList<QString> imageName;
    QMutex mutex;
    QWaitCondition condition;
    QList<QImage> preparedList;//locked by mutex


};

#endif // IMAGELISTMODEL_H
