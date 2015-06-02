#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <solver.h>
template<typename T> class QList;
class ImageListWidget;
class ImageListModel;
class QGroupBox;
class QPlainTextEdit;
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
class Point3DWidget;
class Point3DModel;
class Console;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
private slots:
    void startSolve();
private:
    void setupPhotoWidgets();
    void setupKMatrixWidget();
    void setupDistortionWidgets();
    void setupPointWidgets();

    Distortion getDistortionFromModel();
    void saveDistortionToModel(const Distortion &dist);
    KMatrix getKFromModel();
    void saveKToModel(const KMatrix& K);
    Target2D getTarget2DFromModel();
    void saveTarget2DToModel(const Target2D& target2D);
    Target3D getTarget3DFromModel();
    void saveTarget3DToModel(const Target3D& target3D);
    QList<QImage> getPhotoListFromModel(ImageListModel* model);
    void savePhotoListToModel(QList<QImage> list,ImageListModel* model);

    bool solve(CameraPosSolution &solu);
    bool DistortionCorrectPhoto();
    bool DistortionCorrectPhotoCircle();
    bool calculateDistortion();
    bool calculateK();

private:
    Solver* solver;
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

    Console* console;
    Console& con;

    DistortionModel* distModel;
    QTableView* distView;
    QWidget* distWidget;

    KMatrixModel* kModel;
    QTableView* kView;
    QWidget* kWidget;

    Point2DWidget* point2DWidget;
    Point2DModel* point2DModel;
    Point3DModel* point3DModel;
    Point3DWidget* point3DWidget;
};

#endif // MAINWINDOW_H
