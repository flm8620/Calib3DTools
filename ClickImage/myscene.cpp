#include "myscene.h"

#include <QGraphicsSceneWheelEvent>
#include <QDebug>
#include <QAbstractItemModel>

myScene::myScene(QObject *parent) :
    QGraphicsScene(parent),
    pointView(0)
{
    myMode = MoveItem;
    this->mapper=new QSignalMapper(this);
    this->coreData = 0;
    this->currentZoomScale = 1;
    connect(this->mapper, SIGNAL(mapped(int)), this, SLOT(onMarkerMoved(int)));
}

void myScene::setCoreData(ImageListWithPoint2D *core)
{
    if (this->coreData) {
        disconnect(this->coreData, SIGNAL(pointChanged(int, int)), this,
                   SLOT(onPointChanged(int, int)));
        disconnect(this->coreData, SIGNAL(pointRemoved(int)), this, SLOT(onPointRemoved(int)));
        disconnect(this->coreData, SIGNAL(pointAppended()), this, SLOT(onPointAppended()));
        disconnect(this->coreData, SIGNAL(pointSwaped(int, int)), this, SLOT(onPointSwaped(int,
                                                                                           int)));
        disconnect(this->coreData, SIGNAL(imageChanged(int)), this, SLOT(onImageChanged(int)));
        disconnect(this->coreData, SIGNAL(imageAppended()), this, SLOT(onImageAppended()));
        disconnect(this->coreData, SIGNAL(dataReset()), this, SLOT(onDataReset()));
        if (this->coreData->parent() == this || this->coreData->parent() == 0)
            delete this->coreData;
    }

    this->coreData = core;
    connect(this->coreData, SIGNAL(pointChanged(int, int)), this, SLOT(onPointChanged(int, int)));
    connect(this->coreData, SIGNAL(pointRemoved(int)), this, SLOT(onPointRemoved(int)));
    connect(this->coreData, SIGNAL(pointAppended()), this, SLOT(onPointAppended()));
    connect(this->coreData, SIGNAL(pointSwaped(int, int)), this, SLOT(onPointSwaped(int, int)));
    connect(this->coreData, SIGNAL(imageChanged(int)), this, SLOT(onImageChanged(int)));
    connect(this->coreData, SIGNAL(imageAppended()), this, SLOT(onImageAppended()));
    connect(this->coreData, SIGNAL(dataReset()), this, SLOT(onDataReset()));
    // (*this) doesn't own the new core
}

void myScene::setPoint2DView(Point2DView *pointView)
{
    if (this->pointView) {
        disconnect(this->pointView, SIGNAL(currentPointChanged(int, int)), this,
                   SLOT(onCurrentPointChanged(int, int)));
    }
    this->pointView = pointView;
    connect(this->pointView, SIGNAL(currentPointChanged(int, int)), this,
            SLOT(onCurrentPointChanged(int, int)));
    Point2DModel* model=this->pointView->getPoint2DModel();
    ImageListWithPoint2D* coredata=model->core();
    this->setCoreData(coredata);
}

void myScene::setMode(myScene::Mode mode)
{
    myMode = mode;
}

void myScene::setZoomScale(double scale)
{
    this->currentZoomScale = scale;
    this->resizeMarkers();
}

void myScene::onPointChanged(int indexImg, int indexPoint)
{
    if (this->currentImageId == indexImg) {
        if (indexPoint >= 0 && indexPoint < this->markerList.size()) {
            QPointF p = this->coreData->getPoint(indexImg, indexPoint);
            markerList[indexPoint]->setPos(p);
        }
    }
}

void myScene::onPointRemoved(int indexPoint)
{
    if (indexPoint < this->markerList.size())
        this->removeMarker(indexPoint);
}

void myScene::onPointAppended()
{
    int indexPoint = this->coreData->pointCount()-1;
    this->appendMarker();
    this->onPointChanged(this->currentImageId, indexPoint);
}

void myScene::onPointSwaped(int indexPoint1, int indexPoint2)
{
    this->onPointChanged(this->currentImageId, indexPoint1);
    this->onPointChanged(this->currentImageId, indexPoint2);
}

void myScene::onImageChanged(int indexImg)
{
    if (indexImg == this->currentImageId)
        this->onDataReset();
}

void myScene::onImageAppended()
{
    // nothing to do
}

void myScene::onDataReset()
{
    this->clear();
    this->markerList.clear();
    if (this->currentImageId < this->coreData->size()) {
        this->loadImage(this->coreData->getImage(this->currentImageId));
        QList<QPointF> list;
        this->coreData->getPointsInImage(this->currentImageId, list);
        for (int i = 0; i < list.size(); ++i) {
            Marker *marker = this->appendMarker();
            marker->setPos(list[i]);
        }
    }
    this->setSceneRect(this->itemsBoundingRect());
}

void myScene::onMarkerMoved(int id)
{
    QGraphicsObject *marker = markerList[id];
    double x = marker->pos().x();
    double y = marker->pos().y();
    QPointF p = marker->pos();
    this->coreData->setPoint(this->currentImageId, id, p);
}

void myScene::onCurrentPointChanged(int indexImg, int indexPoint)
{
    if (this->currentImageId != indexImg) {
        this->currentImageId = indexImg;
        this->onDataReset();
        this->selectMarker(indexPoint);
        this->needScrollToMarker(indexPoint);
    } else {
        this->selectMarker(indexPoint);
        this->needScrollToMarker(indexPoint);
    }
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
// if (myMode == InsertItem) {

// event->accept();
// } else {
    QGraphicsScene::mousePressEvent(event);
    // }
}

void myScene::loadImage(const QImage &image)
{
    this->addPixmap(QPixmap::fromImage(image));
}

void myScene::needScrollToMarker(int id)
{
    if (id >= 0 && id < this->markerList.size()) {
        QPointF pos = this->markerList[id]->pos();
        emit requireScrollTo(pos);
    }
}

void myScene::removeMarker(int id)
{
    Marker *marker = markerList[id];
    this->removeItem(marker);
    disconnect(marker, SIGNAL(xChanged()), mapper, SLOT(map()));
    disconnect(marker, SIGNAL(yChanged()), mapper, SLOT(map()));
    this->mapper->removeMappings(marker);
    markerList.removeAt(id);
    delete marker;
}

void myScene::resizeMarkers()
{
    for (int i = 0; i < markerList.size(); i++)
        resizeMarker(i);
}

void myScene::resizeMarker(int id)
{
    Marker *marker = markerList[id];
    if (marker)
        marker->setScale(1/this->currentZoomScale);
}

Marker *myScene::appendMarker()
{
    int id = this->markerList.size();
    Marker *marker = new Marker(id);
    markerList.append(marker);
    resizeMarker(id);
    this->addItem(marker);
    connect(marker, SIGNAL(xChanged()), mapper, SLOT(map()));
    connect(marker, SIGNAL(yChanged()), mapper, SLOT(map()));
    mapper->setMapping(marker, id);
    return marker;
}

void myScene::selectMarker(int id)
{
    this->clearSelection();
    if (id >= 0 && id < this->markerList.size())
        this->markerList[id]->setSelected(true);
}
