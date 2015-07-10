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
    if (!image.isNull())
        scene->addPixmap(QPixmap::fromImage(image));
}

void MarkerImageView::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numPixels.isNull()) {
        scrollWithPixels(numPixels);
    } else if (!numDegrees.isNull()) {
        QPoint numSteps = numDegrees / 15;
        scrollWithDegrees(numSteps);
    }
    event->accept();
}

void MarkerImageView::scrollTo(QPointF pos)
{
    this->centerOn(pos);
}

void MarkerImageView::scrollWithPixels(const QPoint &pixel)
{
    int s = pixel.y();
    double z = std::pow(1.01, s);
    this->zoom(z);
}

void MarkerImageView::scrollWithDegrees(const QPoint &step)
{
    int s = step.y();
    double z = std::pow(1.1, s);
    this->zoom(z);
}

void MarkerImageView::zoom(double z)
{
    if (z > 1) {
        if (this->transform().m11() < 100 && this->transform().m22() < 100) {
            scale(z, z);
            this->scene->setZoomScale(this->transform().m11());
        }
    }
    if (z < 1 && z > 0) {
        if (this->transform().m11() > 0.01 && this->transform().m22() > 0.01) {
            scale(z, z);
            this->scene->setZoomScale(this->transform().m11());
        }
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
