#ifndef IMAGELISTWITHPOINT2D_H
#define IMAGELISTWITHPOINT2D_H
#include "imagelist.h"
#include <QtCore>

class ImageListWithPoint2D : public ImageList
{
    Q_OBJECT
public:
    ImageListWithPoint2D(QObject *parent = 0);
    bool clearPoint();
    void clear();
    int pointCount() const;
    void append(const QString &name, const QImage &image);
    void remove(int indexImg);
    void setContent(QList<QPair<QString, QImage> > &ImageListIn);
    void moveUp(int index);
    void moveDown(int index);
    void movePointUp(int indexPoint);
    void movePointDown(int indexPoint);
    void removePoint(int indexPoint);
    QPointF getPoint(int indexImg,int indexPoint)const;
    void setPoint(int indexImg,int indexPoint,QPointF p);
    void getPointsInImage(int indexImg,QList<QPointF>& list);
    void getAllPoints(QList<QList<QPointF> >& out);
    void setAllPoints(QList<QList<QPointF> >& in);
    void appendPoint();
signals:
    void pointChanged(int indexImg,int indexPoint);
    void pointRemoved(int indexPoint);
    void pointAppended();
    void pointSwaped(int indexPoint1,int indexPoint2);
    void imageChanged(int indexImg);
    void imageAppended();
    void dataReset();



private:
    QList<QList<QPointF> > _pointData;
};

#endif // IMAGELISTWITHPOINT2D_H
