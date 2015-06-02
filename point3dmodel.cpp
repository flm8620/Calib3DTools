#include "point3dmodel.h"

Point3DModel::Point3DModel(QObject *parent)
    :QStandardItemModel(parent)
{
    QStringList list;
    list.append("x");
    list.append("y");
    list.append("z");
    setHorizontalHeaderLabels(list);
}

bool Point3DModel::isEmpty()
{
    return rowCount()==0;
}

void Point3DModel::makeEmpty()
{
    beginResetModel();
    if(rowCount()>0)
        removeRows(0,rowCount());
    endResetModel();
}

int Point3DModel::pointCount()
{
    return rowCount();
}

