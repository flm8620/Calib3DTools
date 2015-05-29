#include "markerimageview.h"
#include "marker.h"
#include "myscene.h"
#include <QDebug>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QSignalMapper>
#include <QPixmap>
MarkerImageView::MarkerImageView(QWidget *parent)
    :QGraphicsView(parent),model(0),selectionModel(0)
{
    scene=new myScene(this);
    setScene(scene);
    connect(scene,SIGNAL(requestItemInsert(double,double)),this,SLOT(insertMarkerOnScreen(double,double)));
    mapper=new QSignalMapper(this);
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(markerMoved(int)));
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(sceneSelectionChanged()));

    invertedMatrix=matrix().inverted();
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void MarkerImageView::setModel(QAbstractItemModel *m)
{
    if(m==model)return;
    if(model){
        disconnect(model,SIGNAL(destroyed()),this,SLOT(modelDestroyed()));
        disconnect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(dataChanged(QModelIndex,QModelIndex)));
        disconnect(model,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(reset()));
        disconnect(model,SIGNAL(columnsInserted(QModelIndex,int,int)),this,SLOT(reset()));
        disconnect(model,SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),this,SLOT(reset()));
        disconnect(model,SIGNAL(columnsMoved(QModelIndex,int,int,QModelIndex,int)),this,SLOT(reset()));
        disconnect(model,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(reset()));
        disconnect(model,SIGNAL(columnsRemoved(QModelIndex,int,int)),this,SLOT(reset()));
        disconnect(model,SIGNAL(modelReset()),this,SLOT(reset()));
    }
    model=m;
    if(model){
        connect(model,SIGNAL(destroyed()),this,SLOT(modelDestroyed()));
        connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(dataChanged(QModelIndex,QModelIndex)));
        connect(model,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(reset()));
        connect(model,SIGNAL(columnsInserted(QModelIndex,int,int)),this,SLOT(reset()));
        connect(model,SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),this,SLOT(reset()));
        connect(model,SIGNAL(columnsMoved(QModelIndex,int,int,QModelIndex,int)),this,SLOT(reset()));
        connect(model,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(reset()));
        connect(model,SIGNAL(columnsRemoved(QModelIndex,int,int)),this,SLOT(reset()));
        connect(model,SIGNAL(modelReset()),this,SLOT(reset()));
    }
}

void MarkerImageView::setMode(ViewMode mode)
{
    if(mode==InsertItem)scene->setMode(myScene::InsertItem);
    else scene->setMode(myScene::MoveItem);
}

void MarkerImageView::setSelectionModel(QItemSelectionModel *sModel)
{
    if(selectionModel){
        disconnect(selectionModel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(currentChanged()));
        disconnect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(selectionChanged(QItemSelection)));
    }
    selectionModel=sModel;
    if(sModel){
        connect(selectionModel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(currentChanged()));
        connect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(selectionChanged(QItemSelection)));
    }
}

void MarkerImageView::loadImage(const QImage &image)
{
    scene->addPixmap(QPixmap::fromImage(image));
}

void MarkerImageView::resizeMarkers()
{
    for(int i=0;i<markerList.size();i++){
        resizeMarker(i);
    }
}

void MarkerImageView::resizeMarker(int id)
{
    Marker* marker=markerList[id];
    if(marker)
        marker->setTransform(QTransform( matrix().inverted()));
}

void MarkerImageView::zoomIn()
{
    scale(1.25,1.25);
    invertedMatrix=matrix().inverted();
    resizeMarkers();
}

void MarkerImageView::zoomOut()
{
    scale(0.8,0.8);
    invertedMatrix=matrix().inverted();
    resizeMarkers();
}

void MarkerImageView::zoomRestore()
{
    resetTransform();
    invertedMatrix=matrix().inverted();
    resizeMarkers();
}

void MarkerImageView::insertMarkerOnScreen(double x, double y)
{
    QModelIndex current=selectionModel->currentIndex();
    if(!current.isValid()){
        int rowCount=model->rowCount();
        model->insertRow(rowCount);
        QModelIndex index1=model->index(rowCount,0);
        QModelIndex index2=model->index(rowCount,2);
        model->setData(index1,x);
        model->setData(index2,y);
    }else{
        int row=current.row();
        QModelIndex index1=model->index(row,0);
        QModelIndex index2=model->index(row,1);
        model->setData(index1,x);
        model->setData(index2,y);
    }
    emit markerInsertedOnScreen();
}

void MarkerImageView::selectionChanged(const QItemSelection & selected)
{
    if(selected.isEmpty())return;
    int row=selected.first().top();
    scene->clearSelection();
    markerList.at(row)->setSelected(true);

}

void MarkerImageView::sceneSelectionChanged()
{
    qDebug()<<"changed"<<rand();
    if(scene->selectedItems().isEmpty())return;
    QGraphicsItem* item= scene->selectedItems().first();
    int i=markerList.indexOf(static_cast<Marker*>(item));
    if(i!=-1){
        QModelIndex index1= model->index(i,0);
        QModelIndex index2= model->index(i,1);
        QItemSelection itemSelection;
        itemSelection.append(QItemSelectionRange(index1,index2));
        selectionModel->select(itemSelection,QItemSelectionModel::ClearAndSelect);
    }
}

void MarkerImageView::currentChanged()
{
    QModelIndex index=selectionModel->currentIndex();
    if(index.isValid()){
        scrollToMarker(index.row());
    }
}



void MarkerImageView::reset()
{
    resetScene();
}

void MarkerImageView::modelDestroyed()
{
    model=0;
}

void MarkerImageView::dataChanged(const QModelIndex& topLeft,const QModelIndex& /*bottomRight*/)
{
    editMarker(topLeft);
}

void MarkerImageView::markerMoved(int id)
{
    Q_ASSERT(id>=0 && id<markerList.size());
    QGraphicsObject* marker=markerList[id];
    double x=marker->pos().x();
    double y=marker->pos().y();
    QModelIndex indexX=model->index(id,0);
    QModelIndex indexY=model->index(id,1);
    model->setData(indexX,x);
    model->setData(indexY,y);
}


Marker* MarkerImageView::addMarker(int id)
{
    Marker* marker=new Marker(id);
    markerList.reserve(id+1);
    for(int i=markerList.size();i<=id;i++)markerList.append(0);
    markerList[id]=marker;
    resizeMarker(id);
    scene->addItem(marker);
    connect(marker,SIGNAL(xChanged()),mapper,SLOT(map()));
    connect(marker,SIGNAL(yChanged()),mapper,SLOT(map()));
    mapper->setMapping(marker,id);
    return marker;
}

void MarkerImageView::removeMarker(int id)
{
    Marker* marker=markerList[id];
    scene->removeItem(marker);
    disconnect(marker,SIGNAL(xChanged()),mapper,SLOT(map()));
    disconnect(marker,SIGNAL(yChanged()),mapper,SLOT(map()));
    mapper->removeMappings(marker);
    markerList[id]=0;
    delete marker;

}

void MarkerImageView::resetScene()
{
    int n=model->rowCount();
    for(int i=0;i<markerList.size();i++)
        removeMarker(i);
    markerList.clear();

    Marker *newItem;
    for(int i=0;i<n;i++){
        QModelIndex index1=model->index(i,0);
        QModelIndex index2=model->index(i,1);
        bool ok1,ok2;
        double x=index1.data(Qt::DisplayRole).toDouble(&ok1);
        double y=index2.data(Qt::DisplayRole).toDouble(&ok2);
        if(!ok1 || !ok2){
            x=y=0;
        }
        newItem=addMarker(i);
        newItem->setPos(x,y);
    }
}

void MarkerImageView::editMarker(const QModelIndex &index)
{
    int i=index.row();
    Q_ASSERT(i>=0 && i<markerList.size());
    Marker *item=markerList[i];
    Q_ASSERT(item);
    bool ok1,ok2;
    double x=model->index(i,0,index.parent()).data(Qt::DisplayRole).toDouble(&ok1);
    double y=model->index(i,1,index.parent()).data(Qt::DisplayRole).toDouble(&ok2);
    if(!ok1 || !ok2){
        x=y=0;
    }
    item->setPos(x,y);
}

void MarkerImageView::scrollToMarker(int index)
{
    Q_ASSERT(index>=0 && index<markerList.size());
    ensureVisible(markerList[index]);
}


