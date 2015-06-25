#include "tabwidget.h"
// #include "imagelistmodel.h"
#include "point2dwidget.h"
#include "point3dwidget.h"
DistortionTab::DistortionTab(QWidget *parent) : QWidget(parent)
{
    this->harpPhotoWidget = new ImageListWidget(tr("Harp Photo"));
    this->harpFeedbackWidget = new ImageListWidget(tr("Detect Feedback"));
    this->calculateButton = new QPushButton(tr("Calculate Distortion Polynomial"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->harpPhotoWidget);
    lay->addWidget(this->calculateButton);
    lay->addWidget(this->harpFeedbackWidget);
    this->setLayout(lay);
}

void DistortionTab::connectToSolver(Solver *solver)
{
    connect(this->calculateButton, SIGNAL(clicked(bool)), solver, SLOT(onCalculateDistortion()));
}

void DistortionTab::registerModel(ImageListModel *harpPhotoModel, ImageListModel *harpFeedbackModel)
{
    this->harpPhotoWidget->setModel(harpPhotoModel);
    this->harpFeedbackWidget->setModel(harpFeedbackModel);
}

void DistortionTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->harpPhotoWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->harpFeedbackWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

KMatrixTab::KMatrixTab(QWidget *parent) : QWidget(parent)
{
    this->circlePhotoWidget = new ImageListWidget(tr("Circle Photo"));
    this->circleCorrectedWidget = new ImageListWidget(tr("Corrected Circle Photo"));
    this->circleFeedbackWidget = new ImageListWidget(tr("Detect Feedback"));
    this->calculateButton = new QPushButton(tr("Calculate Matrix K"));
    this->correctDistButton = new QPushButton(tr("Apply Distortion Correction"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->circlePhotoWidget);
    lay->addWidget(this->correctDistButton);
    lay->addWidget(this->circleCorrectedWidget);
    lay->addWidget(this->calculateButton);
    lay->addWidget(this->circleFeedbackWidget);
    this->setLayout(lay);
}

void KMatrixTab::connectToSolver(Solver *solver)
{
    connect(this->correctDistButton, SIGNAL(clicked(bool)), solver,
            SLOT(onCorrectCircle()));
    connect(this->calculateButton, SIGNAL(clicked(bool)), solver, SLOT(onCalculateK()));
}

void KMatrixTab::registerModel(ImageListModel *circlePhotoModel,
                               ImageListModel *circleCorrectedModel,
                               ImageListModel *circleFeedbackModel)
{
    this->circlePhotoWidget->setModel(circlePhotoModel);
    this->circleCorrectedWidget->setModel(circleCorrectedModel);
    this->circleFeedbackWidget->setModel(circleFeedbackModel);
}

void KMatrixTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->circlePhotoWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->circleCorrectedWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->circleFeedbackWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

PhotoTab::PhotoTab(QWidget *parent) : QWidget(parent)
{
    this->photoWidget = new ImageListWidget(tr("Photo"));
    this->correctedWidget = new ImageListWidget(tr("Corrected Photo"));
    this->correctDistButton = new QPushButton(tr("Apply Distortion Correction"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->photoWidget);
    lay->addWidget(this->correctDistButton);
    lay->addWidget(this->correctedWidget);
    this->setLayout(lay);
}

void PhotoTab::connectToSolver(Solver *solver)
{
    connect(this->correctDistButton, SIGNAL(clicked(bool)), solver, SLOT(onCorrectPhoto()));
}

void PhotoTab::registerModel(ImageListModel *photoModel, ImageListModel *correctedModel)
{
    this->photoWidget->setModel(photoModel);
    this->correctedWidget->setModel(correctedModel);
}

void PhotoTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->photoWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->correctedWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

Point2D3DTab::Point2D3DTab(QWidget *parent) : QWidget(parent)
{
    this->correctedWidget = new ImageListWidget(tr("Corrected Photo"));
    this->point2DWidget = new Point2DWidget;
    this->point3DWidget = new Point3DWidget;
    this->solveStrecha = new QPushButton(tr("Solve by Strecha's' Method"));
    this->solveOpenMVG = new QPushButton(tr("Solve by OpenMVG"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->correctedWidget);
    lay->addWidget(this->point2DWidget);
    lay->addWidget(this->point3DWidget);
    lay->addWidget(this->solveStrecha);
    lay->addWidget(this->solveOpenMVG);
    this->setLayout(lay);
}

void Point2D3DTab::connectToSolver(Solver *solver)
{
    // TODO
}

void Point2D3DTab::registerModel(ImageListModel *correctedModel, Point2DModel *point2DModel,
                                 Point3DModel *point3DModel)
{
    this->correctedWidget->setModel(correctedModel);
    this->point2DWidget->setModel(point2DModel);
    this->point3DWidget->setModel(point3DModel);
}

void Point2D3DTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->correctedWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

void Point2D3DTab::connectToMarkerViewer(MarkerImageView *markerViewer)
{
    markerViewer->setPoint2DView(this->point2DWidget->getPoint2DView());
}

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    this->distortionTab = new DistortionTab;
    this->kmatrixTab = new KMatrixTab;
    this->photoTab = new PhotoTab;
    this->point2d3dTab = new Point2D3DTab;

    this->addTab(distortionTab, tr("Distortion"));
    this->addTab(kmatrixTab, tr("KMatrix"));
    this->addTab(photoTab, tr("Photo"));
    this->addTab(point2d3dTab, tr("Point2D-3D"));
}

void TabWidget::connectToSolver(Solver *solver)
{
    this->distortionTab->connectToSolver(solver);
    this->kmatrixTab->connectToSolver(solver);
    this->photoTab->connectToSolver(solver);
    this->point2d3dTab->connectToSolver(solver);
}

void TabWidget::registerModel(ImageListModel *harpPhotoModel, ImageListModel *harpFeedbackModel,
                              ImageListModel *circlePhotoModel,
                              ImageListModel *circleCorrectedModel,
                              ImageListModel *circleFeedbackModel, ImageListModel *photoModel,
                              ImageListModel *photoCorrectedModel, Point2DModel *point2DModel,
                              Point3DModel *point3DModel)
{
    this->distortionTab->registerModel(harpPhotoModel, harpFeedbackModel);
    this->kmatrixTab->registerModel(circlePhotoModel, circleCorrectedModel, circleFeedbackModel);
    this->photoTab->registerModel(photoModel, photoCorrectedModel);
    this->point2d3dTab->registerModel(photoCorrectedModel, point2DModel, point3DModel);
}

void TabWidget::connectToImageViewer(ImageViewer *viewer)
{
    this->distortionTab->connectToImageViewer(viewer);
    this->kmatrixTab->connectToImageViewer(viewer);
    this->photoTab->connectToImageViewer(viewer);
}

void TabWidget::connectToMarkerViewer(MarkerImageView *markerViewer)
{
    this->point2d3dTab->connectToMarkerViewer(markerViewer);
}
