#include "mainwindow.h"
#include "imagelistmodel.h"
#include "imagelistwidget.h"
#include "distortionmodel.h"
#include "kmatrixmodel.h"
#include "point2dwidget.h"
#include "point2dmodel.h"
#include <QtWidgets>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* center=new QWidget;
    QVBoxLayout* imageListlayout=new QVBoxLayout;

    photoWidget=new ImageListWidget;
    photoCircleWidget=new ImageListWidget;
    photoHarpWidget=new ImageListWidget;

    photoModel=new ImageListModel(this);
    photoCircleModel=new ImageListModel(this);
    photoHarpModel=new ImageListModel(this);

    photoWidget->setModel(photoModel);
    photoCircleWidget->setModel(photoCircleModel);
    photoHarpWidget->setModel(photoHarpModel);

    distModel=new DistortionModel;
    distView=new QTableView;
    distView->setModel(distModel);
    kModel=new KMatrixModel;
    kView=new QTableView;
    kView->setModel(kModel);
    kView->setEnabled(false);
    point2DWidget=new Point2DWidget;
    point2DModel=new Point2DModel(this);
    point2DModel->setImageModel(photoModel);
    point2DWidget->setModel(point2DModel);



    //layout
    imageListlayout->addWidget(photoWidget);
    imageListlayout->addWidget(photoCircleWidget);
    imageListlayout->addWidget(photoHarpWidget);

    QHBoxLayout* bLayout=new QHBoxLayout;
    QPushButton* generateButton=new QPushButton(tr("Generate"));
    QPushButton* saveDistortionButton=new QPushButton(tr("Save Distortion"));
    QPushButton* saveKMatrixButton=new QPushButton(tr("Save K Matrix"));

    bLayout->addWidget(generateButton);
    bLayout->addWidget(saveDistortionButton);
    bLayout->addWidget(saveKMatrixButton);
    QVBoxLayout* leftLayout=new QVBoxLayout;
    leftLayout->addLayout(imageListlayout);
    leftLayout->addLayout(bLayout);

    QHBoxLayout* rightLayout=new QHBoxLayout;
    rightLayout->addWidget(distView);
    rightLayout->addWidget(kView);
    rightLayout->addWidget(point2DWidget);
    QHBoxLayout* layout=new QHBoxLayout;
    layout->addLayout(leftLayout);
    layout->addLayout(rightLayout);
    center->setLayout(layout);
    setCentralWidget(center);
    statusBar();
}
