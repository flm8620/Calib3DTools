#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagelistmodel.h"
#include "imagelistwidget.h"
#include "distortionmodel.h"
#include "distortionwidget.h"
#include "kmatrixmodel.h"
#include "point2dmodel.h"
#include "point3dmodel.h"
#include "imageviewer.h"
#include "tabwidget.h"
#include "messager.h"
#include "console.h"
#include "consolewidget.h"
#include "solver.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, public libMsg::Messager
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void message(std::string content, libMsg::MessageType type);

signals:
    void messageSignal(QString s, libMsg::MessageType type);

private:
    void setupPhotoModels();
    void setupPointModels();
    void setupKMatrixWidget();
    void setupDistortionWidgets();

private:
    Solver *solver;
    TabWidget *tabWidget;

    ImageListModel *photoModel;
    ImageListModel *photoCircleModel;
    ImageListModel *photoHarpModel;
    ImageListModel *circleFeedbackModel;
    ImageListModel *harpFeedbackModel;
    ImageListModel *undistortedPhotoModel;
    ImageListModel *undistortedCircleModel;
    ImageListModel *undistortedHarpModel;

    ImageViewer* imageViewer;

    ConsoleWidget* consoleWidget;

    DistortionModel *distModel;
    DistortionWidget *distWidget;

    KMatrixModel *kModel;
    QTableView *kView;
    QWidget *kWidget;

    Point2DModel *point2DModel;
    Point3DModel *point3DModel;
};

#endif // MAINWINDOW_H
