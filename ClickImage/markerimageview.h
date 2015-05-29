#ifndef MARKERIMAGEVIEW_H
#define MARKERIMAGEVIEW_H
#include <QGraphicsView>
#include <QObject>
#include <QList>
class QModelIndex;
class QAbstractItemModel;
class QItemSelectionModel;
class QSignalMapper;
class Marker;
class QImage;
class QItemSelection;
class myScene;
class QMatrix;
class MarkerImageView: public QGraphicsView
{
    Q_OBJECT

public:
    enum ViewMode {InsertItem,MoveItem};
    MarkerImageView(QWidget * parent = 0);
    void setModel(QAbstractItemModel* m);
    void setMode(ViewMode mode);
    void setSelectionModel(QItemSelectionModel* sModel);
    void loadImage(const QImage& image);
    void resizeMarkers();
    void resizeMarker(int id);
signals:
    void markerInsertedOnScreen();
public slots:
    void zoomIn();
    void zoomOut();
    void zoomRestore();
private slots:
    void insertMarkerOnScreen(double x,double y);
    void selectionChanged(const QItemSelection& selected);
    void sceneSelectionChanged();
    void markerMoved(int id);
    void currentChanged();
    void reset();
    void modelDestroyed();
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &);
private:
    Marker *addMarker(int id);
    void removeMarker(int id);
    void resetScene();
    void editMarker(const QModelIndex& index);
    void scrollToMarker(int index);
    myScene* scene;
    QList<Marker*> markerList;
    QAbstractItemModel* model;
    QItemSelectionModel* selectionModel;
    QSignalMapper* mapper;
    QMatrix invertedMatrix;
};

#endif // MARKERIMAGEVIEW_H
