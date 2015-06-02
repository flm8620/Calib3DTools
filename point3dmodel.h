#ifndef POINT3DMODEL_H
#define POINT3DMODEL_H

#include <QObject>
#include <QStandardItemModel>
class Point3DModel : public QStandardItemModel
{
    Q_OBJECT
public:
    Point3DModel(QObject* parent=0);
    bool isEmpty();
    void makeEmpty();
    int pointCount();
};

#endif // POINT3DMODEL_H
