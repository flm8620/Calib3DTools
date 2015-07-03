#include "mainwindow.h"
#include "sciencedoubledelegate.h"
#include "imagelistwithpoint2d.h"
#include <QtWidgets>
#include <QPushButton>
#include <QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupPhotoModels();
    setupPointModels();
    setupCamPosModel();
    setupKMatrixWidget();
    setupDistortionWidgets();

    this->solver = new Solver(this);
    this->consoleWidget = new ConsoleWidget;
    connect(this, SIGNAL(messageSignal(QString, libMsg::MessageType)), consoleWidget->getConsole(),
            SLOT(messageReceiver(QString, libMsg::MessageType)));
    this->solver->registerModels(photoModel->core(), photoCircleModel->core(),
                                 photoHarpModel->core(), this->imagePoint2DCore,
                                 undistortedCircleModel->core(), undistortedHarpModel->core(),
                                 harpFeedbackModel->core(),
                                 circleFeedbackModel->core(), distModel->core(),
                                 kModel->core(), point3DModel->core(),camPosModel->core(), this);

    tabWidget = new TabWidget;
    tabWidget->connectToSolver(this->solver);
    tabWidget->registerModel(photoHarpModel, harpFeedbackModel, photoCircleModel,
                             undistortedCircleModel, circleFeedbackModel, photoModel,
                             undistortedPhotoModel, point2DModel, point3DModel,camPosModel);

    this->markerViewer=new MarkerImageView(this);
    this->imageViewer = new ImageViewer(this);
    QTabWidget *centerTab=new QTabWidget;
    centerTab->addTab(this->imageViewer,"ImageViewer");
    centerTab->addTab(this->markerViewer,"Point2DViewer");

    tabWidget->connectToImageViewer(this->imageViewer);
    tabWidget->connectToMarkerViewer(this->markerViewer);
    // layout

    QList<int> sizes;
    QSplitter *centerSp = new QSplitter(Qt::Vertical);
    centerSp->addWidget(centerTab);
    centerSp->addWidget(this->consoleWidget);
    centerSp->setStretchFactor(0, 3);
    centerSp->setStretchFactor(2, 1);
    QSplitter *leftSp = new QSplitter(Qt::Vertical);
    leftSp->addWidget(this->distWidget);
    leftSp->addWidget(this->kWidget);
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(leftSp);
    splitter->addWidget(centerSp);
    splitter->addWidget(this->tabWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);
    splitter->setStretchFactor(2, 1);
    sizes.clear();

    this->setCentralWidget(splitter);

    this->resize(1000, 800);
}

void MainWindow::message(std::string content, libMsg::MessageType type)
{
    emit this->messageSignal(QString::fromStdString(content), type);
}

void MainWindow::setupPhotoModels()
{
    photoModel = new ImageListModel(this);
    photoCircleModel = new ImageListModel(this);
    photoHarpModel = new ImageListModel(this);
    circleFeedbackModel = new ImageListModel(this);
    harpFeedbackModel = new ImageListModel(this);
    undistortedPhotoModel = new ImageListModel(this);
    undistortedCircleModel = new ImageListModel(this);
    undistortedHarpModel = new ImageListModel(this);


    this->imagePoint2DCore=new ImageListWithPoint2D(this);
    undistortedPhotoModel->setCoreData(this->imagePoint2DCore);
}

void MainWindow::setupPointModels()
{
    point2DModel = new Point2DModel(this);
    point2DModel->setCoreData(this->imagePoint2DCore);
    point3DModel = new Point3DModel(this);
}

void MainWindow::setupCamPosModel()
{
    this->camPosModel=new CamPosModel(this);
}

void MainWindow::setupKMatrixWidget()
{
    this->kModel = new KMatrixModel(this);
    this->kWidget=new KMatrixWidget(this);
    this->kWidget->setModel(this->kModel);
}

void MainWindow::setupDistortionWidgets()
{
    distModel = new DistortionModel(this);
    distWidget = new DistortionWidget(this);
    distWidget->setModel(distModel);
}
