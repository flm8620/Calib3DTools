
#include "mainwindow.h"
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
    connect(solver,SIGNAL(message(QString,bool)),console,SLOT(messageReceiver(QString,bool)));
    this->solver->registerModels(photoModel,photoCircleModel,photoHarpModel,
                           noDistortion_photoModel,noDistortion_photoCircleModel,
                           noDistortion_photoHarpModel,distModel,
                           kModel->core(),point2DModel,point3DModel);



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
    distView=new QTableView;
    distView->setModel(distModel);
    distWidget=new QGroupBox("Distortion");
    QHBoxLayout* l=new QHBoxLayout;
    l->addWidget(distView);
    distWidget->setLayout(l);
}

void MainWindow::setupPointWidgets()
{
    point2DModel=new Point2DModel(this);
    point2DModel->setImageModel(photoModel);
    point2DWidget=new Point2DWidget;
    point2DWidget->setModel(point2DModel);

    point3DModel=new Point3DModel(this);
    point3DWidget=new Point3DWidget;
    point3DWidget->setModel(point3DModel);
}

//Distortion MainWindow::getDistortionFromModel()
//{
//    Distortion dist;
//    int rows=distModel->rowCount();
//    for(int i=0;i<rows;++i){
//        QModelIndex id=distModel->index(i);
//        dist.data.append( distModel->data(id).toDouble());
//    }
//    return dist;
//}

//void MainWindow::saveDistortionToModel(const Distortion& dist)
//{
//    distModel->makeEmpty();
//    int rows=dist.data.size();
//    for(int i=0;i<rows;++i){
//        distModel->insertRow(i);
//        distModel->setData(distModel->index(i),dist.data.value(i));
//    }
//}

//KMatrix MainWindow::getKFromModel()
//{
//    KMatrix K;
//    K.fx=kModel->data(kModel->index(0)).toDouble();
//    K.fy=kModel->data(kModel->index(1)).toDouble();
//    K.x0=kModel->data(kModel->index(2)).toDouble();
//    K.y0=kModel->data(kModel->index(3)).toDouble();
//    K.s=kModel->data(kModel->index(4)).toDouble();
//    return K;
//}

//void MainWindow::saveKToModel(const KMatrix &K)
//{
//    kModel->setData(kModel->index(0),K.fx);
//    kModel->setData(kModel->index(1),K.fy);
//    kModel->setData(kModel->index(2),K.x0);
//    kModel->setData(kModel->index(3),K.y0);
//    kModel->setData(kModel->index(4),K.s);
//}

//Target2D MainWindow::getTarget2DFromModel()
//{
//    Target2D target2D;
//    int rows=point2DModel->rowCount();
//    int points=point2DModel->item(0)->rowCount();
//    for(int i=0;i<rows;++i){
//        target2D.data.append(QList<QPointF>());
//        QList<QPointF>& l=target2D.data.last();
//        for(int j=0;j<points;j++){
//            QPointF p;
//            p.setX(point2DModel->item(i)->child(j,1)->text().toDouble());
//            p.setY(point2DModel->item(i)->child(j,2)->text().toDouble());
//            l.append(p);
//        }
//    }
//    return target2D;
//}

//void MainWindow::saveTarget2DToModel(const Target2D &target2D)
//{
//    //not needed
//}

//Target3D MainWindow::getTarget3DFromModel()
//{
//    Target3D target3D;
//    int points=point3DModel->rowCount();
//    for(int j=0;j<points;j++){
//        QVector3D p;
//        p.setX(point3DModel->item(j,0)->text().toDouble());
//        p.setY(point3DModel->item(j,1)->text().toDouble());
//        p.setZ(point3DModel->item(j,2)->text().toDouble());
//        target3D.data.append(p);
//    }
//    return target3D;
//}

//void MainWindow::saveTarget3DToModel(const Target3D &target3D)
//{
//    //not needed
//}

//QList<QImage> MainWindow::getPhotoListFromModel(ImageListModel *model)
//{
//    QList<QImage> photoList;
//    int rows=model->rowCount();
//    for(int i=0;i<rows;++i){
//        QModelIndex id=model->index(i);
//        photoList.append( qvariant_cast<QImage>( model->data(id,Qt::UserRole)));
//    }
//    return photoList;
//}

//void MainWindow::savePhotoListToModel(QList<QImage> list, ImageListModel *model)
//{
//    model->makeEmpty();
//    QImage image;
//    int i=0;
//    foreach (image,list) {
//        model->insertRow(i);
//        QModelIndex id=model->index(i);
//        model->setData(id,tr("Image%1").arg(i),Qt::DisplayRole);
//        model->setData(id,image,Qt::UserRole);
//        i++;
//    }
//}
