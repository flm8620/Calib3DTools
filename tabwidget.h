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
    void connectToImageViewer(ImageViewer* viewer);
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
    void connectToImageViewer(ImageViewer* viewer);
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
    void connectToImageViewer(ImageViewer* viewer);
private:
    ImageListWidget *photoWidget;
    ImageListWidget *correctedWidget;
    ImageListWidget *feedbackWidget;
    QPushButton *correctDistButton;
};

class Point2D3DTab : public QWidget
{
    Q_OBJECT
public:
    Point2D3DTab(QWidget *parent = 0);
    void connectToSolver(Solver *solver);
    void registerModel(ImageListModel *correctedModel, Point2DModel *point2DModel,
                       Point3DModel *point3DModel);
    void connectToImageViewer(ImageViewer* viewer);
    void connectToMarkerViewer(MarkerImageView *markerViewer);
private:
    ImageListWidget *correctedWidget;
    Point2DWidget *point2DWidget;
    Point3DWidget *point3DWidget;
    QPushButton *solveStrecha;
    QPushButton *solveOpenMVG;
};
class CamPosTab :public QWidget
{
public:
    CamPosTab(QWidget *parent = 0);
    void registerModel(CamPosModel* camPosModel);
private:
    CamPosWidget *camPosWidget;
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
                       ImageListModel *photoCorrectedModel,
                       Point2DModel *point2DModel, Point3DModel *point3DModel, CamPosModel *camPosModel);
    void connectToImageViewer(ImageViewer* viewer);
    void connectToMarkerViewer(MarkerImageView* markerViewer);
private:
    DistortionTab *distortionTab;
    KMatrixTab *kmatrixTab;
    PhotoTab *photoTab;
    Point2D3DTab *point2d3dTab;
    CamPosTab *camPosTab;
};

#endif // TABWIDGET_H
