#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QList>
#include "marker.h"
#include "imagelistwithpoint2d.h"
#include "point2dview.h"
class QGraphicsSceneWheelEvent;
class myScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {
        InsertItem, MoveItem
    };
    myScene(QObject *parent = 0);
    void setCoreData(ImageListWithPoint2D *core);
    void setPoint2DView(Point2DView *pointView);
    void setMode(Mode mode);
    void setZoomScale(double scale);
private slots:
    void onPointChanged(int indexImg, int indexPoint);
    void onPointRemoved(int indexPoint);
    void onPointAppended();
    //void onPointSwaped(int indexPoint1, int indexPoint2);
    void onImageChanged(int indexImg);
    void onImageAppended();
    void onDataReset();

    void onMarkerMoved(QObject *markerFormMapper);
    void onCurrentPointChanged(int indexImg,int indexPoint);
signals:
    void requireScrollTo(QPointF pos);
private:
    void loadImage(const QImage &image);
    void needScrollToMarker(int id);
    void removeMarker(int id);
    void resizeMarkers();
    void resizeMarker(int id);
    Marker *appendMarker();
    void selectMarker(int id);
    int currentImageId;
    QList<Marker *> markerList;
    Mode myMode;
    ImageListWithPoint2D *coreData;
    Point2DView *pointView;
    QSignalMapper *mapper;
    double currentZoomScale;
};



#endif // MYSCENE_H
