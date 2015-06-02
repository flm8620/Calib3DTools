#ifndef POINT2DMODEL_H
#define POINT2DMODEL_H

#include <QObject>
#include <QStandardItemModel>
class ImageListModel;
class Point2DModel : public QStandardItemModel
{
    Q_OBJECT
public:
    Point2DModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();
    int pointCount();
    void setImageModel(ImageListModel* model);
    QImage getImage(int row);
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
public slots:
    void imagesInserted(const QModelIndex &, int first, int last);
    void imagesRemoved(const QModelIndex &, int first, int last);
    void imagesChanged(const QModelIndex & topLeft);
private:
    ImageListModel* imageModel;
};

#endif // POINT2DMODEL_H
