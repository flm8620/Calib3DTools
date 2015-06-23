#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QtWidgets>
#include "imagelistwidget.h"
#include "imageviewer.h"
#include "solver.h"
class ImageListModel;
class Point3DWidget;
class Point2DWidget;
class Point2DModel;
class Point3DModel;
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
private:
    ImageListWidget *correctedWidget;
    Point2DWidget *point2DWidget;
    Point3DWidget *point3DWidget;
    QPushButton *solveStrecha;
    QPushButton *solveOpenMVG;
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
                       Point2DModel *point2DModel, Point3DModel *point3DModel);
    void connectToImageViewer(ImageViewer* viewer);
private:
    DistortionTab *distortionTab;
    KMatrixTab *kmatrixTab;
    PhotoTab *photoTab;
    Point2D3DTab *point2d3dTab;
};

#endif // TABWIDGET_H
