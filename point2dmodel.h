#ifndef POINT2DMODEL_H
#define POINT2DMODEL_H

#include <QtCore>
#include <QAbstractItemModel>
#include "imagelistwithpoint2d.h"
class ImageListModel;
class Point2DModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    Point2DModel(QObject* parent=0);
    void clear();
    void setCoreData(ImageListWithPoint2D* core);
    ImageListWithPoint2D *core();
    int pointCount()const;

    QImage getImage(int row)const;
    void removePoint(QModelIndex &index);
    void movePointUp(QModelIndex &index);
    void movePointDown(QModelIndex &index);
    void appendPoint();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool indexMeansImage(const QModelIndex &index)const;
    bool indexMeansPoint(const QModelIndex &index)const;
private slots:
    void onPointChanged(int indexImg,int indexPoint);
    void onPointRemoved(int indexPoint);
    void onPointAppended();
    void onPointSwaped(int indexPoint1,int indexPoint2);

    void onImageChanged(int indexImg);
    void onImageAppended();

    void onDataReset();
private:

    ImageListWithPoint2D *coreData;
};

#endif // POINT2DMODEL_H
