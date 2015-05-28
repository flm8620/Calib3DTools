#include "imageviewer.h"
#include <QWheelEvent>
#include <QDebug>
ImageViewer::ImageViewer(const QImage &image, QWidget *parent)
    :QGraphicsView(parent)
{
    myImage=image;
    scene=new QGraphicsScene(this);
    QPixmap pix=QPixmap::fromImage(myImage);
    scene->addPixmap(pix);
    setScene(scene);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    int a=event->angleDelta().y();
    if(a>0)
        zoomIn();
    else
        zoomOut();
}

void ImageViewer::zoomIn()
{
    scale(1.25,1.25);
}

void ImageViewer::zoomOut()
{
    scale(0.8,0.8);
}
