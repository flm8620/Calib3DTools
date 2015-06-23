#include "mainwindow.h"
#include "doublespindelegate.h"

#include <QtWidgets>
#include <QPushButton>
#include <QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupPhotoModels();
    setupPointModels();
    setupKMatrixWidget();
    setupDistortionWidgets();

    this->solver = new Solver(this);
    this->consoleWidget = new ConsoleWidget;
    connect(this, SIGNAL(messageSignal(QString, libMsg::MessageType)), consoleWidget->getConsole(),
            SLOT(messageReceiver(QString, libMsg::MessageType)));
    this->solver->registerModels(photoModel->core(), photoCircleModel->core(),
                                 photoHarpModel->core(), undistortedPhotoModel->core(),
                                 undistortedCircleModel->core(), undistortedHarpModel->core(),
                                 harpFeedbackModel->core(),
                                 circleFeedbackModel->core(), distModel->core(),
                                 kModel->core(), point2DModel, point3DModel, this);

    tabWidget = new TabWidget;
    tabWidget->connectToSolver(this->solver);
    tabWidget->registerModel(photoHarpModel, harpFeedbackModel, photoCircleModel,
                             undistortedCircleModel, circleFeedbackModel, photoModel,
                             undistortedPhotoModel, point2DModel, point3DModel);

    this->imageViewer = new ImageViewer(this);
    tabWidget->connectToImageViewer(this->imageViewer);
    // layout

// QVBoxLayout *leftLay = new QVBoxLayout;
// leftLay->addWidget(this->distWidget);
// leftLay->addWidget(this->kWidget);
// QVBoxLayout *centerLayout = new QVBoxLayout;
// centerLayout->addWidget(this->imageViewer);
// centerLayout->addWidget(this->consoleWidget);
// QHBoxLayout *layout = new QHBoxLayout;
// layout->addLayout(leftLay);
// layout->addLayout(centerLayout);
// layout->addWidget(this->tabWidget);
    QList<int> sizes;
    QSplitter *centerSp = new QSplitter(Qt::Vertical);
    centerSp->addWidget(this->imageViewer);
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
}

void MainWindow::setupPointModels()
{
    point2DModel = new Point2DModel(this);
    point2DModel->setImageModel(undistortedPhotoModel);
    point3DModel = new Point3DModel(this);
}

void MainWindow::setupKMatrixWidget()
{
    kModel = new KMatrixModel(this);
    kView = new QTableView;
    kView->setModel(kModel);
    kWidget = new QGroupBox("K Matrix");
    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(kView);
    kWidget->setLayout(l);
}

void MainWindow::setupDistortionWidgets()
{
    distModel = new DistortionModel(this);
// distView=new QTableView;
// distView->setItemDelegate(new DoubleSpinDelegate);
// distView->setModel(distModel);
    distWidget = new DistortionWidget(this);
    distWidget->setModel(distModel);
}
