#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QtWidgets>
#include "imagelistmodel.h"
#include "imagelistwidget.h"
#include "point2dmodel.h"
#include "point2dwidget.h"
#include "point3dmodel.h"
#include "point3dwidget.h"
#include "camposmodel.h"
#include "camposwidget.h"
#include "imageviewer.h"
#include "solver.h"
#include "markerimageview.h"

class DistortionTab : public QWidget
{
    Q_OBJECT
public:
    DistortionTab(QWidget *parent = 0);
    void connectToSolver(Solver *solver);
    void registerModel(ImageListModel *harpPhotoModel, ImageListModel *harpFeedbackModel);
    void connectToImageViewer(ImageViewer *viewer);
private:
    ImageListWidget *harpPhotoWidget;
    ImageListWidget *harpFeedbackWidget;
    QPushButton *calculateButton;
};

class KMatrixTab : public QWidget
{
    Q_OBJECT
public:
    KMatrixTab(QWidget *parent = 0);
    void connectToSolver(Solver *solver);
    void registerModel(ImageListModel *circlePhotoModel, ImageListModel *circleCorrectedModel,
                       ImageListModel *circleFeedbackModel);
    void connectToImageViewer(ImageViewer *viewer);
private:
    ImageListWidget *circlePhotoWidget;
    ImageListWidget *circleCorrectedWidget;
    ImageListWidget *circleFeedbackWidget;
    QPushButton *correctDistButton;
    QPushButton *calculateButton;
};

class PhotoTab : public QWidget
{
    Q_OBJECT
public:
    PhotoTab(QWidget *parent = 0);
    void connectToSolver(Solver *solver);
    void registerModel(ImageListModel *photoModel, ImageListModel *correctedModel);
    void connectToImageViewer(ImageViewer *viewer);
private:
    ImageListWidget *photoWidget;
    ImageListWidget *correctedWidget;
    ImageListWidget *feedbackWidget;
    QPushButton *correctDistButton;
};

class Point2DTab : public QWidget
{
    Q_OBJECT
public:
    Point2DTab(QWidget *parent = 0);
    void registerModel(ImageListModel *correctedModel, Point2DModel *point2DModel);
    void connectToImageViewer(ImageViewer *viewer);
    void connectToMarkerViewer(MarkerImageView *markerViewer);
private:
    ImageListWidget *correctedWidget;
    Point2DWidget *point2DWidget;

};

class Point3DTab : public QWidget
{
    Q_OBJECT
public:
    Point3DTab(QWidget *parent = 0);
    void registerModel(Point3DModel *point3DModel);
private:
    Point3DWidget *point3DWidget;

};

class CamPosTab : public QWidget
{
public:
    CamPosTab(QWidget *parent = 0);
    void connectToSolver(Solver *solver);
    void registerModel(CamPosModel *camPosModel);
private:
    CamPosWidget *camPosWidget;
    QPushButton *solveStrecha;
};

class CamCompareTab : public QWidget
{
    Q_OBJECT
public:
    CamCompareTab(QWidget *parent = 0);
    void connectToSolver(Solver *solver);
    void registerModel(CamPosModel *camPosModel);
private slots:
    void loadJson();
private:
    bool loadCamPos(const QStringList &list);
    CamPosWidget *camPosWidget;
    QPushButton *loadFromOpenMVGjson;
    QPushButton *compareButton;
};


class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *parent = 0);
    void connectToSolver(Solver *solver);
    void registerModel(ImageListModel *harpPhotoModel, ImageListModel *harpFeedbackModel,
                       ImageListModel *circlePhotoModel, ImageListModel *circleCorrectedModel,
                       ImageListModel *circleFeedbackModel, ImageListModel *photoModel,
                       ImageListModel *photoCorrectedModel, Point2DModel *point2DModel,
                       Point3DModel *point3DModel, CamPosModel *camPosModel, CamPosModel *camCompareModel);
    void connectToImageViewer(ImageViewer *viewer);
    void connectToMarkerViewer(MarkerImageView *markerViewer);
private:
    DistortionTab *distortionTab;
    KMatrixTab *kmatrixTab;
    PhotoTab *photoTab;
    Point2DTab *point2dTab;
    Point3DTab *point3dTab;
    CamPosTab *camPosTab;
    CamCompareTab *camCompareTab;
};

#endif // TABWIDGET_H
