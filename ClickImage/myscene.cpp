#include "myscene.h"
#include "marker.h"
#include <QGraphicsSceneWheelEvent>
#include <QDebug>
#include <QAbstractItemModel>
myScene::myScene(QObject *parent)
    :QGraphicsScene(parent)
{
    myMode=MoveItem;
}

void myScene::setMode(myScene::Mode mode)
{
    myMode=mode;
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(myMode==InsertItem){
        emit requestItemInsert(event->scenePos().x(),event->scenePos().y());
        event->accept();
    }else{
        QGraphicsScene::mousePressEvent(event);
    }
}





