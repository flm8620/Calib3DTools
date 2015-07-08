#include "imageviewer.h"
#include <QWheelEvent>
#include <QDebug>
ImageViewer::ImageViewer(const QImage &image, QWidget *parent) :
    QGraphicsView(parent)
{
    myImage = image;
    scene = new QGraphicsScene(this);
    QPixmap pix = QPixmap::fromImage(myImage);
    scene->addPixmap(pix);
    setScene(scene);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

ImageViewer::ImageViewer(QWidget *parent) : myImage(0),
    QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void ImageViewer::setImage(QImage image)
{
    myImage = image;
    QPixmap pix = QPixmap::fromImage(myImage);
    scene->clear();
    scene->addPixmap(pix);
    scene->setSceneRect(scene->itemsBoundingRect());
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    int a = event->angleDelta().y();
    if (a > 0)
        zoomIn();
    else if (a < 0)
        zoomOut();
}

void ImageViewer::zoomIn()
{
    if (this->transform().m11() < 100 && this->transform().m22() < 100)
        scale(1.25, 1.25);
}

void ImageViewer::zoomOut()
{
    if (this->transform().m11() > 0.01 && this->transform().m22() > 0.01)
        scale(0.8, 0.8);
}
