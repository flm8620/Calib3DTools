#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QGraphicsView>
class QLabel;
class ImageViewer : public QGraphicsView
{
    Q_OBJECT
public:
    ImageViewer(const QImage &image, QWidget *parent = 0);
    ImageViewer(QWidget *parent = 0);
signals:

public slots:
    void setImage(QImage image);
protected:
    void wheelEvent(QWheelEvent *event);
private:
    void zoomIn();
    void zoomOut();
    QImage myImage;
    QGraphicsScene *scene;
};

#endif // IMAGEVIEWER_H
