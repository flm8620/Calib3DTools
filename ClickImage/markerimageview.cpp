#include "markerimageview.h"
#include "marker.h"
#include "myscene.h"
#include <QDebug>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QSignalMapper>
#include <QPixmap>
#include <QWheelEvent>
MarkerImageView::MarkerImageView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new myScene(this);
    setScene(scene);
    connect(this->scene, SIGNAL(requireScrollTo(QPointF)), this, SLOT(scrollTo(QPointF)));
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void MarkerImageView::loadImage(const QImage &image)
{
    scene->addPixmap(QPixmap::fromImage(image));
}

void MarkerImageView::wheelEvent(QWheelEvent *event)
{
    int a = event->angleDelta().y();
    if (a > 0)
        zoomIn();
    else
        zoomOut();
}

void MarkerImageView::scrollTo(QPointF pos)
{
    this->centerOn(pos);
}

void MarkerImageView::zoomIn()
{
    if (this->transform().m11() < 100 && this->transform().m22() < 100) {
        scale(1.25, 1.25);
        this->scene->setZoomScale(this->transform().m11());
    }
}

void MarkerImageView::zoomOut()
{
    if (this->transform().m11() > 0.01 && this->transform().m22() > 0.01) {
        scale(0.8, 0.8);
        this->scene->setZoomScale(this->transform().m11());
    }
}

void MarkerImageView::zoomRestore()
{
    resetTransform();
    this->scene->setZoomScale(this->transform().m11());
}

void MarkerImageView::setCoreData(ImageListWithPoint2D *core)
{
    this->scene->setCoreData(core);
}

void MarkerImageView::setPoint2DView(Point2DView *point2DView)
{
    this->scene->setPoint2DView(point2DView);
}
