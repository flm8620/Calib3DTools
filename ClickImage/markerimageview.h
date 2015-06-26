#ifndef MARKERIMAGEVIEW_H
#define MARKERIMAGEVIEW_H
#include <QGraphicsView>
#include <QObject>
#include <QList>
#include "myscene.h"
#include "marker.h"
#include "imagelistwithpoint2d.h"
#include "point2dview.h"
class QModelIndex;
class QAbstractItemModel;
class QItemSelectionModel;
class QSignalMapper;
class QImage;
class QItemSelection;
class QMatrix;
class MarkerImageView : public QGraphicsView
{
    Q_OBJECT

public:
    enum ViewMode {
        InsertItem, MoveItem
    };
    MarkerImageView(QWidget *parent = 0);
    void setCoreData(ImageListWithPoint2D* core);
    void setPoint2DView(Point2DView* point2DView);
    void loadImage(const QImage &image);
protected:
    void wheelEvent(QWheelEvent *event);
public slots:
    void scrollTo(QPointF pos);
    void zoomIn();
    void zoomOut();
    void zoomRestore();
private:

    myScene *scene;
};

#endif // MARKERIMAGEVIEW_H
