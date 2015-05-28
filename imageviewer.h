#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QGraphicsView>
class QLabel;
class ImageViewer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ImageViewer(const QImage& image,QWidget *parent = 0);

signals:

public slots:
protected:
    void wheelEvent(QWheelEvent *event);
private:
    void zoomIn();
    void zoomOut();
    QImage myImage;
    QGraphicsScene* scene;
};

#endif // IMAGEVIEWER_H
