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
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numPixels.isNull()) {
        qDebug()<<"pixel "<<numPixels;
        scrollWithPixels(numPixels);
    } else if (!numDegrees.isNull()) {
        qDebug()<<"deg: "<<numDegrees;
        QPoint numSteps = numDegrees / 15;
        scrollWithDegrees(numSteps);
    }
    event->accept();
}

void ImageViewer::scrollWithPixels(const QPoint &pixel)
{
    int s = pixel.y();
    double z = std::pow(1.01, s);
    this->zoom(z);
}

void ImageViewer::scrollWithDegrees(const QPoint &step)
{
    int s = step.y();
    double z = std::pow(1.1, s);
    this->zoom(z);
}

void ImageViewer::zoom(double z)
{
    if (z > 1)
        if (this->transform().m11() < 100 && this->transform().m22() < 100)
            scale(z, z);
    if (z < 1 && z > 0)
        if (this->transform().m11() > 0.01 && this->transform().m22() > 0.01)
            scale(z, z);
}
