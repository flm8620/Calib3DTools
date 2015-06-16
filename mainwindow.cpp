
#include "mainwindow.h"
#include "doublespindelegate.h"
#include <QtWidgets>
#include <QPushButton>
#include <QtConcurrent>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),console(new Console()),con(*console)
{
    setupPhotoWidgets();
    setupKMatrixWidget();
    setupDistortionWidgets();
    setupPointWidgets();

    this->solver=new Solver(this);
    connect(this,SIGNAL(message(QString,bool)),console,SLOT(messageReceiver(QString,bool)));
    this->solver->registerModels(photoModel,photoCircleModel,photoHarpModel,
                           noDistortion_photoModel,noDistortion_photoCircleModel,
                           noDistortion_photoHarpModel,distModel->core(),
                           kModel->core(),point2DModel,point3DModel, this);



    //layout
    QHBoxLayout* photoLay=new QHBoxLayout;
    QHBoxLayout* circleLay=new QHBoxLayout;
    QHBoxLayout* harpLay=new QHBoxLayout;
    photoLay->addWidget(photoWidget);
    photoLay->addWidget(noDistortion_photoWidget);
    circleLay->addWidget(photoCircleWidget);
    circleLay->addWidget(noDistortion_photoCircleWidget);
    harpLay->addWidget(photoHarpWidget);
    harpLay->addWidget(noDistortion_photoHarpWidget);

    QVBoxLayout* leftLay=new QVBoxLayout;
    leftLay->addLayout(photoLay);
    leftLay->addLayout(circleLay);
    leftLay->addLayout(harpLay);


    QHBoxLayout* bLayout=new QHBoxLayout;
    QPushButton* generateButton=new QPushButton(tr("Generate"));
    QPushButton* saveDistortionButton=new QPushButton(tr("Save Distortion"));
    QPushButton* saveKMatrixButton=new QPushButton(tr("Save K Matrix"));

    connect(generateButton,SIGNAL(clicked(bool)),this,SLOT(startSolve()));

    bLayout->addWidget(generateButton);
    bLayout->addWidget(saveDistortionButton);
    bLayout->addWidget(saveKMatrixButton);
    QGridLayout* rightLay=new QGridLayout;
    rightLay->addWidget(kWidget,0,0);
    rightLay->addWidget(distWidget,1,0);
    rightLay->addWidget(point2DWidget,0,1,2,1);
    rightLay->addWidget(point3DWidget,0,2,2,1);
    rightLay->addLayout(bLayout,2,0,1,3);
    rightLay->addWidget(console,3,0,1,3);

    QHBoxLayout* layout=new QHBoxLayout;
    layout->addLayout(leftLay);
    layout->addLayout(rightLay);

    QWidget* center=new QWidget;
    center->setLayout(layout);
    setCentralWidget(center);
    statusBar();

    //connect(generateButton,SIGNAL(clicked(bool)),worker,SLOT(solve()));
}

void MainWindow::message( const char *content, MessageType type )
{
    emit this->message(tr(content), type>=M_WARN);
}

void MainWindow::startSolve()
{
    QtConcurrent::run(this->solver,&Solver::startSolve);
}


void MainWindow::setupPhotoWidgets()
{
    photoWidget=new ImageListWidget(tr("Photo"));
    photoCircleWidget=new ImageListWidget(tr("Circle Photo"));
    photoHarpWidget=new ImageListWidget(tr("Harp Photo"));

    photoModel=new ImageListModel(this);
    photoCircleModel=new ImageListModel(this);
    photoHarpModel=new ImageListModel(this);

    photoWidget->setModel(photoModel);
    photoCircleWidget->setModel(photoCircleModel);
    photoHarpWidget->setModel(photoHarpModel);

    noDistortion_photoWidget=new ImageListWidget(tr("Correction: Photo"));
    noDistortion_photoCircleWidget=new ImageListWidget(tr("Correction: Circle Photo"));
    noDistortion_photoHarpWidget=new ImageListWidget(tr("Correction: Harp Photo"));

    noDistortion_photoModel=new ImageListModel(this);
    noDistortion_photoCircleModel=new ImageListModel(this);
    noDistortion_photoHarpModel=new ImageListModel(this);

    noDistortion_photoWidget->setModel(noDistortion_photoModel);
    noDistortion_photoCircleWidget->setModel(noDistortion_photoCircleModel);
    noDistortion_photoHarpWidget->setModel(noDistortion_photoHarpModel);
}

void MainWindow::setupKMatrixWidget()
{
    kModel=new KMatrixModel(this);
    kView=new QTableView;
    kView->setModel(kModel);
    kWidget=new QGroupBox("K Matrix");
    QHBoxLayout* l=new QHBoxLayout;
    l->addWidget(kView);
    kWidget->setLayout(l);

}

void MainWindow::setupDistortionWidgets()
{
    distModel=new DistortionModel(this);
//    distView=new QTableView;
//    distView->setItemDelegate(new DoubleSpinDelegate);
//    distView->setModel(distModel);
    distWidget=new DistortionWidget(this);
    distWidget->setModel(distModel);
}

void MainWindow::setupPointWidgets()
{
    point2DModel=new Point2DModel(this);
    point2DModel->setImageModel(noDistortion_photoModel);
    point2DWidget=new Point2DWidget;
    point2DWidget->setModel(point2DModel);

    point3DModel=new Point3DModel(this);
    point3DWidget=new Point3DWidget;
    point3DWidget->setModel(point3DModel);
}

