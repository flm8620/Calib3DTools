#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagelistmodel.h"
#include "imagelistwidget.h"
#include "distortionmodel.h"
#include "distortionwidget.h"
#include "kmatrixmodel.h"
#include "point2dwidget.h"
#include "point2dmodel.h"
#include "point3dwidget.h"
#include "point3dmodel.h"
#include "messager.h"
#include "console.h"
#include "solver.h"

#include <QMainWindow>


class MainWindow : public QMainWindow, public libMsg::Messager
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void message(std::string content, libMsg::MessageType type );

signals:
    void messageSignal(QString s, libMsg::MessageType type);

private slots:
    void startSolve();
private:
    void setupPhotoWidgets();
    void setupKMatrixWidget();
    void setupDistortionWidgets();
    void setupPointWidgets();

private:
    Solver * solver;
    ImageListWidget* photoWidget;
    ImageListWidget* photoCircleWidget;
    ImageListWidget* photoHarpWidget;
    ImageListWidget* noDistortion_photoWidget;
    ImageListWidget* noDistortion_photoCircleWidget;
    ImageListWidget* noDistortion_photoHarpWidget;

    ImageListModel* photoModel;
    ImageListModel* photoCircleModel;
    ImageListModel* photoHarpModel;
    ImageListModel* noDistortion_photoModel;
    ImageListModel* noDistortion_photoCircleModel;
    ImageListModel* noDistortion_photoHarpModel;

    Console* console;
    Console& con;

    DistortionModel* distModel;
    DistortionWidget* distWidget;

    KMatrixModel* kModel;
    QTableView* kView;
    QWidget* kWidget;

    Point2DWidget* point2DWidget;
    Point2DModel* point2DModel;
    Point3DModel* point3DModel;
    Point3DWidget* point3DWidget;
};

#endif // MAINWINDOW_H
