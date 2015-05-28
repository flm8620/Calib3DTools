#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <solver.h>
template<typename T> class QList;
class ImageListWidget;
class ImageListModel;
class QGroupBox;
class QTextEdit;
class QTableWidget;
class QStandardItemModel;
class QTableWidget;
class QTableView;
class QTreeView;
class QImage;
class DistortionModel;
class KMatrixModel;
class Point2DWidget;
class Point2DModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
private:

private:
    ImageListWidget* photoWidget;
    ImageListWidget* photoCircleWidget;
    ImageListWidget* photoHarpWidget;
    ImageListWidget* distortion_photoWidget;
    ImageListWidget* distortion_photoCircleWidget;
    ImageListWidget* distortion_photoHarpWidget;

    ImageListModel* photoModel;
    ImageListModel* photoCircleModel;
    ImageListModel* photoHarpModel;
    ImageListModel* distortion_photoModel;
    ImageListModel* distortion_photoCircleModel;
    ImageListModel* distortion_photoHarpModel;

    QTextEdit* console;
    QStandardItemModel* target2Dmodel;
    QTreeView* target2DView;
    QTableWidget* target3DWidget;

    KMatrix kMatrix;
    Distortion distortion;
    DistortionModel* distModel;
    QTableView* distView;
    KMatrixModel* kModel;
    QTableView* kView;
    Point2DWidget* point2DWidget;
    Point2DModel* point2DModel;
};

#endif // MAINWINDOW_H
