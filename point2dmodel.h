#ifndef POINT2DMODEL_H
#define POINT2DMODEL_H

#include <QtCore>
#include <QStandardItemModel>
#include "target2d.h"


class ImageListModel;
class Point2DModel : public QStandardItemModel, public Target2DContainer
{
    Q_OBJECT
public:
    Point2DModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();
    int pointCount();
    void setImageModel(ImageListModel* model);
    QImage getImage(int row);
    Target2D getTarget2D_threadSafe();
    void saveTarget2D_threadSafe(const Target2D& target2D);

    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
public slots:
    void imagesInserted(const QModelIndex &, int first, int last);
    void imagesRemoved(const QModelIndex &, int first, int last);
    void imagesChanged(const QModelIndex & topLeft);
signals:
    void requestGet();
    void requestSave(const Target2D& target2D);
private slots:
    void prepareTarget2D();
    void saveTarget2D(const Target2D& target2D);
private:
    ImageListModel* imageModel;
    QMutex mutex;
    QWaitCondition conditionGet;
    QWaitCondition conditionSave;
    Target2D preparedTarget2D;//locked by mutex
};

#endif // POINT2DMODEL_H
