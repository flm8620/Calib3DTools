#include "point2dmodel.h"
#include "imagelistmodel.h"
Point2DModel::Point2DModel(QObject *parent)
    :QStandardItemModel(parent)
{
    QStringList list;
    list.append("Image/Point");
    list.append("x");
    list.append("y");
    setHorizontalHeaderLabels(list);
}

bool Point2DModel::isEmpty()
{
    return rowCount()==0;
}

void Point2DModel::makeEmpty()
{
    beginResetModel();
    if(rowCount()>0)
        removeRows(0,rowCount());
    endResetModel();
}

int Point2DModel::pointCount()
{
    if(rowCount()==0)return 0;
    return item(0)->rowCount();
}

void Point2DModel::setImageModel(ImageListModel *model)
{
    imageModel=model;
    connect(imageModel,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(imagesInserted(QModelIndex,int,int)));
    connect(imageModel,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(imagesRemoved(QModelIndex,int,int)));
    connect(imageModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(imagesChanged(QModelIndex)));
}

QImage Point2DModel::getImage(int row)
{
    QModelIndex id = imageModel->index(row);
    QImage image=qvariant_cast<QImage>(imageModel->data(id,Qt::UserRole));
    Q_ASSERT(!image.isNull());
    return image;

}


QModelIndex Point2DModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex newParent=parent;
    if(!parent.isValid()){
        newParent=indexFromItem( invisibleRootItem());
    }
    return QStandardItemModel::index(row,column,newParent);
}

Qt::ItemFlags Point2DModel::flags(const QModelIndex &index) const
{
    if(index.isValid()){
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    }
    return 0;
}


void Point2DModel::imagesInserted(const QModelIndex &/*parent*/, int first, int last)
{
    int pointCount=0;
    if(rowCount()>0){
        pointCount=item(0)->rowCount();
    }
    for(int i=first;i<=last;++i){
        QModelIndex id=imageModel->index(i);
        QString s=qvariant_cast<QString>(imageModel->data(id,Qt::DisplayRole));
        QStandardItem* imageItem=new QStandardItem(s);
        QList<QStandardItem*> imageList;
        imageList.append(imageItem);
        imageList.append(new QStandardItem);
        imageList.append(new QStandardItem);
        insertRow(i,imageList);
        for(int j=0;j<pointCount;j++){
            QStandardItem *item1=new QStandardItem(tr("Point"));
            QStandardItem *item2=new QStandardItem("0");
            QStandardItem *item3=new QStandardItem("0");
            QList<QStandardItem*> list;
            list.append(item1);
            list.append(item2);
            list.append(item3);

            imageItem->appendRow(list);
        }
    }

}

void Point2DModel::imagesRemoved(const QModelIndex &/*parent*/, int first, int last)
{
    removeRows(first,last-first+1);
}

void Point2DModel::imagesChanged(const QModelIndex &topLeft)
{
    int row=topLeft.row();
    Q_ASSERT(row<rowCount());
    QString s=qvariant_cast<QString>(imageModel->data(topLeft,Qt::DisplayRole));
    item(row)->setText(s);
}

