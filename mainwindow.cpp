#include "mainwindow.h"
#include "imagelistmodel.h"
#include "imagelistwidget.h"
#include "distortionmodel.h"
#include "kmatrixmodel.h"
#include "point2dwidget.h"
#include "point2dmodel.h"
#include "point3dwidget.h"
#include "point3dmodel.h"
#include "console.h"
#include <QtWidgets>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),console(new Console()),con(*console)
{
    solver=new Solver(this);

    setupPhotoWidgets();
    setupKMatrixWidget();
    setupDistortionWidgets();
    setupPointWidgets();




    //layout
    QHBoxLayout* photoLay=new QHBoxLayout;
    QHBoxLayout* circleLay=new QHBoxLayout;
    QHBoxLayout* harpLay=new QHBoxLayout;
    photoLay->addWidget(photoWidget);
    photoLay->addWidget(distortion_photoWidget);
    circleLay->addWidget(photoCircleWidget);
    circleLay->addWidget(distortion_photoCircleWidget);
    harpLay->addWidget(photoHarpWidget);
    harpLay->addWidget(distortion_photoHarpWidget);

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
}

void MainWindow::startSolve()
{
    CameraPosSolution solu;
    if(!solve(solu)){
        con<<"Solve failed!";
    }else{
        con<<"Solve succeed";
    }
}

bool MainWindow::solve(CameraPosSolution& solu)
{

    if(!DistortionCorrectPhoto()){
        con<<"Distortion correction of photo failed !";
        return false;
    }
    Q_ASSERT(!distortion_photoModel->isEmpty());
    con<<"";

    if(!calculateK()){
        con<<"Failed to calculate matrix K !";
        return false;
    }
    con<<"";
    Q_ASSERT(!kModel->isEmpty());

    if(point2DModel->pointCount()==0){
        con.warning("You should set at least one 2D point");
        return false;
    }else{
        con<<"2D points loaded";
    }

    if(point3DModel->isEmpty()){
        con.warning("You should set at least one 3D point");
        return false;
    }else{
        con<<"3D points loaded";
    }

    if(point2DModel->pointCount()!=point3DModel->pointCount()){
        con.warning("You should set same amount of 2D and 3D point");
        return false;
    }

    Target2D target2D=getTarget2DFromModel();
    Target3D target3D=getTarget3DFromModel();
    QList<QImage> photoList=getPhotoListFromModel(distortion_photoModel);
    KMatrix K=getKFromModel();

    solu = solver->strechaSolver(target2D,target3D,photoList,K);
    return true;
}

bool MainWindow::DistortionCorrectPhoto()
{
    con<<"Loading distortion correction of photo...";
    if(distortion_photoModel->isEmpty()){
        con<<"Distortion correction of photo is empty. Correct distortion for photos...";
        if(!calculateDistortion()){
            con<<"Failed to load distortion !";
            return false;
        }
        Q_ASSERT(!distModel->isEmpty());

        Distortion dist=getDistortionFromModel();

        int rows=photoModel->rowCount();
        con<<"Loading photos...";
        if(rows==0){
            con.warning("No photo found ! You should load photos.");
            return false;
        }else{
            con<<"Photos loaded";
        }
        QList<QImage> photoList=getPhotoListFromModel(photoModel);
        QList<QImage> outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append(solver->correctDistortion(image,dist));
        }
        savePhotoListToModel(outputList,distortion_photoModel);
        con<<"Distortion correction of photo finished.";
    }else{
        con<<"Distortion correction of photo loaded.";
    }
    return true;
}

bool MainWindow::DistortionCorrectPhotoCircle()
{
    con<<"Loading distortion correction of circle photo...";
    if(distortion_photoCircleModel->isEmpty()){
        con<<"Distortion correction of circle photo is empty. Correct distortion for circle photos...";
        if(!calculateDistortion()){
            con<<"Failed to load distortion !";
            return false;
        }
        Q_ASSERT(!distModel->isEmpty());

        Distortion dist=getDistortionFromModel();

        int rows=photoCircleModel->rowCount();
        con<<"Loading circle photos...";
        if(rows==0){
            con.warning("No circle photo found ! You should load circle photos.");
            return false;
        }else{
            con<<"Circle photos loaded";
        }

        QList<QImage> photoList=getPhotoListFromModel(photoCircleModel);
        QList<QImage> outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append(solver->correctDistortion(image,dist));
        }
        savePhotoListToModel(outputList,distortion_photoCircleModel);



        con<<"Distortion correction of photo finished.";

    }else{
        con<<"Distortion correction of circle photo loaded.";
    }
    return true;

}

bool MainWindow::calculateDistortion()
{
    con<<"Loading distortion parameter...";
    if(distModel->isEmpty()){
        con<<"Distortion parameter is empty. Calculating distortion parameter";

        if(photoHarpModel->isEmpty()){
            con.warning("You should load harp photos");
            return false;
        }
        int rows=photoHarpModel->rowCount();
        QList<QImage> imageList=getPhotoListFromModel(photoHarpModel);
        Distortion dist = solver->calculateDistortion(imageList);
        saveDistortionToModel(dist);
        con<<"Distortion calculated";
    }else{
        con<<"Distortion parameter loaded";
    }
    return true;
}

bool MainWindow::calculateK()
{
    con<<"Loading matrix K...";
    if(kModel->isEmpty()){
        con<<"Matrix K is empty. Calculating K from corrected harp photos...";

        if(!DistortionCorrectPhotoCircle()){
            con<<"Distortion Correction of circle photos failed !";
            return false;
        }
        Q_ASSERT(!distortion_photoCircleModel->isEmpty());
        QList<QImage> imageList=getPhotoListFromModel(distortion_photoCircleModel);
        KMatrix K=solver->calculateK(imageList);
        saveKToModel(K);

        con<<"Matrix K generated";
    }else{
        con<<"Matrix K loaded";
    }
    return true;
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

    distortion_photoWidget=new ImageListWidget(tr("Correction: Photo"));
    distortion_photoCircleWidget=new ImageListWidget(tr("Correction: Circle Photo"));
    distortion_photoHarpWidget=new ImageListWidget(tr("Correction: Harp Photo"));

    distortion_photoModel=new ImageListModel(this);
    distortion_photoCircleModel=new ImageListModel(this);
    distortion_photoHarpModel=new ImageListModel(this);

    distortion_photoWidget->setModel(distortion_photoModel);
    distortion_photoCircleWidget->setModel(distortion_photoCircleModel);
    distortion_photoHarpWidget->setModel(distortion_photoHarpModel);
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

Distortion MainWindow::getDistortionFromModel()
{
    Distortion dist;
    int rows=distModel->rowCount();
    for(int i=0;i<rows;++i){
        QModelIndex id=distModel->index(i);
        dist.data.append( distModel->data(id).toDouble());
    }
    return dist;
}

void MainWindow::saveDistortionToModel(const Distortion& dist)
{
    distModel->makeEmpty();
    int rows=dist.data.size();
    for(int i=0;i<rows;++i){
        distModel->insertRow(i);
        distModel->setData(distModel->index(i),dist.data.value(i));
    }
}

KMatrix MainWindow::getKFromModel()
{
    KMatrix K;
    K.fx=kModel->data(kModel->index(0)).toDouble();
    K.fy=kModel->data(kModel->index(1)).toDouble();
    K.x0=kModel->data(kModel->index(2)).toDouble();
    K.y0=kModel->data(kModel->index(3)).toDouble();
    K.s=kModel->data(kModel->index(4)).toDouble();
    return K;
}

void MainWindow::saveKToModel(const KMatrix &K)
{
    kModel->setData(kModel->index(0),K.fx);
    kModel->setData(kModel->index(1),K.fy);
    kModel->setData(kModel->index(2),K.x0);
    kModel->setData(kModel->index(3),K.y0);
    kModel->setData(kModel->index(4),K.s);
}

Target2D MainWindow::getTarget2DFromModel()
{
    Target2D target2D;
    int rows=point2DModel->rowCount();
    int points=point2DModel->item(0)->rowCount();
    for(int i=0;i<rows;++i){
        target2D.data.append(QList<QPointF>());
        QList<QPointF>& l=target2D.data.last();
        for(int j=0;j<points;j++){
            QPointF p;
            p.setX(point2DModel->item(i)->child(j,1)->text().toDouble());
            p.setY(point2DModel->item(i)->child(j,2)->text().toDouble());
            l.append(p);
        }
    }
    return target2D;
}

void MainWindow::saveTarget2DToModel(const Target2D &target2D)
{
    //not needed
}

Target3D MainWindow::getTarget3DFromModel()
{
    Target3D target3D;
    int points=point3DModel->rowCount();
    for(int j=0;j<points;j++){
        QVector3D p;
        p.setX(point3DModel->item(j,0)->text().toDouble());
        p.setY(point3DModel->item(j,1)->text().toDouble());
        p.setZ(point3DModel->item(j,2)->text().toDouble());
        target3D.data.append(p);
    }
    return target3D;
}

void MainWindow::saveTarget3DToModel(const Target3D &target3D)
{
    //not needed
}

QList<QImage> MainWindow::getPhotoListFromModel(ImageListModel *model)
{
    QList<QImage> photoList;
    int rows=model->rowCount();
    for(int i=0;i<rows;++i){
        QModelIndex id=model->index(i);
        photoList.append( qvariant_cast<QImage>( model->data(id,Qt::UserRole)));
    }
    return photoList;
}

void MainWindow::savePhotoListToModel(QList<QImage> list, ImageListModel *model)
{
    model->makeEmpty();
    QImage image;
    int i=0;
    foreach (image,list) {
        model->insertRow(i);
        QModelIndex id=model->index(i);
        model->setData(id,tr("Image%1").arg(i),Qt::DisplayRole);
        model->setData(id,image,Qt::UserRole);
        i++;
    }
}
