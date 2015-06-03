#include "solver.h"
#include "distortionmodel.h"
#include "imagelistmodel.h"
#include "kmatrixmodel.h"
#include "point2dmodel.h"
#include "point3dmodel.h"
#include <QImage>
#include <QPainter>
Solver::Solver(QObject *parent) : QObject(parent)
{

}

Distortion Solver::calculateDistortion(const QList<QImage> &imageList)
{
    Q_ASSERT(!imageList.isEmpty());
    Distortion dist;
    dist.data.append(1.0);
    dist.data.append(2.0);
    dist.data.append(3.0);
    dist.data.append(4.0);
    dist.data.append(5.0);
    return dist;
}

QImage Solver::correctDistortion(const QImage &image, const Distortion &distortion)
{
    QImage result=image;
    QPainter painter(&result);
    QRectF rect(100,100,500,500);
    painter.drawText(rect,tr("Distortion Corrected"));
    return result;
}

KMatrix Solver::calculateK(const QList<QImage> &circlePhotoList)
{
    Q_ASSERT(!circlePhotoList.isEmpty());
    KMatrix K;
    K.fx=10;K.fy=10;
    K.s=0;
    K.x0=100;
    K.y0=100;
    return K;
}

CameraPosSolution Solver::openMVGSolver(Target2D target2D, const QList<QImage> &photoList, KMatrix K)
{
    CameraPosSolution s;
    s.data.append(QVector3D(10,10,10));
    s.data.append(QVector3D(20,20,20));
    return s;
}

CameraPosSolution Solver::strechaSolver(Target2D target2D, Target3D target3D, const QList<QImage> &photoList, KMatrix K)
{
    CameraPosSolution s;
    s.data.append(QVector3D(10,10,10));
    s.data.append(QVector3D(20,20,20));
    return s;
}

void Solver::registerModels(ImageListModel *photoModel, ImageListModel *photoCircleModel, ImageListModel *photoHarpModel, ImageListModel *noDistortion_photoModel, ImageListModel *noDistortion_photoCircleModel, ImageListModel *noDistortion_photoHarpModel, DistortionModel *distModel, KMatrixModel *kModel, Point2DModel *point2DModel, Point3DModel *point3DModel)
{
    this->photoModel=photoModel;
    this->photoCircleModel=photoCircleModel;
    this->photoHarpModel=photoHarpModel;
    this->noDistortion_photoModel=noDistortion_photoModel;
    this->noDistortion_photoCircleModel=noDistortion_photoCircleModel;
    this->noDistortion_photoHarpModel=noDistortion_photoHarpModel;
    this->kModel=kModel;
    this->distModel=distModel;
    this->point2DModel=point2DModel;
    this->point3DModel=point3DModel;
}

void Solver::startSolve()
{
    CameraPosSolution solu;
    if(!solve(solu)){
        emit message(tr("Solve failed!"),true);
    }else{
        emit message(tr("Solve succeed"));
    }
    //return solu;
}

bool Solver::solve(CameraPosSolution &solu)
{
    if(!DistortionCorrectPhoto()){
        emit message(tr("Distortion correction of photo failed !"));
        return false;
    }
    Q_ASSERT(!noDistortion_photoModel->isEmpty());
    emit message(tr(""));

    if(!calculateK()){
        emit message(tr("Failed to calculate matrix K !"));
        return false;
    }
    emit message(tr(""));
    Q_ASSERT(!kModel->isEmpty());

    if(point2DModel->pointCount()==0){
        emit message(tr("You should set at least one 2D point"),true);
        return false;
    }else{
        emit message(tr("2D points loaded"));
    }

    if(point3DModel->isEmpty()){
        emit message(tr("You should set at least one 3D point"),true);
        return false;
    }else{
        emit message(tr("3D points loaded"));
    }

    if(point2DModel->pointCount()!=point3DModel->pointCount()){
        emit message(tr("You should set same amount of 2D and 3D point"),true);
        return false;
    }

    Target2D target2D=point2DModel->getTarget2D_threadSafe();
    Target3D target3D=point3DModel->getTarget3D_threadSafe();
    QList<QImage> photoList=noDistortion_photoModel->getImageList_threadSafe();
    KMatrix K=kModel->getKMatrix_threadSafe();

    solu = this->strechaSolver(target2D,target3D,photoList,K);
    return true;
}

bool Solver::DistortionCorrectPhoto()
{
    emit message(tr("Loading distortion correction of photo..."));
    if(noDistortion_photoModel->isEmpty()){
        emit message(tr("Distortion correction of photo is empty. Correct distortion for photos..."));
        if(!calculateDistortion()){
            emit message(tr("Failed to load distortion !"));
            return false;
        }
        Q_ASSERT(!distModel->isEmpty());

        Distortion dist=distModel->getDistortion_threadSafe();

        int rows=photoModel->rowCount();
        emit message(tr("Loading photos..."));
        if(rows==0){
            emit message(tr("No photo found ! You should load photos."),true);
            return false;
        }else{
            emit message(tr("Photos loaded"));
        }
        QList<QImage> photoList=photoModel->getImageList_threadSafe();
        QList<QImage> outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append(this->correctDistortion(image,dist));
        }
        noDistortion_photoModel->saveImageList_threadSafe(outputList);
        emit message(tr("Distortion correction of photo finished."));
    }else{
        emit message(tr("Distortion correction of photo loaded."));
    }
    return true;
}

bool Solver::DistortionCorrectPhotoCircle()
{
    emit message(tr("Loading distortion correction of circle photo..."));
    if(noDistortion_photoCircleModel->isEmpty()){
        emit message(tr("Distortion correction of circle photo is empty. Correct distortion for circle photos..."));
        if(!calculateDistortion()){
            emit message(tr("Failed to load distortion !"));
            return false;
        }
        Q_ASSERT(!distModel->isEmpty());

        Distortion dist=distModel->getDistortion_threadSafe();

        int rows=photoCircleModel->rowCount();
        emit message(tr("Loading circle photos..."));
        if(rows==0){
            emit message(tr("No circle photo found ! You should load circle photos."),true);
            return false;
        }else{
            emit message(tr("Circle photos loaded"));
        }

        QList<QImage> photoList=photoCircleModel->getImageList_threadSafe();
        QList<QImage> outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append(this->correctDistortion(image,dist));
        }
        noDistortion_photoCircleModel->saveImageList_threadSafe(outputList);

        emit message(tr("Distortion correction of photo finished."));
    }else{
        emit message(tr("Distortion correction of circle photo loaded."));
    }
    return true;

}

bool Solver::calculateDistortion()
{
    emit message(tr("Loading distortion parameter..."));
    if(distModel->isEmpty()){
        emit message(tr("Distortion parameter is empty. Calculating distortion parameter"));

        if(photoHarpModel->isEmpty()){
            emit message(tr("You should load harp photos"),true);
            return false;
        }
        QList<QImage> imageList=photoHarpModel->getImageList_threadSafe();
        Distortion dist = this->calculateDistortion(imageList);
        distModel->saveDistortion_threadSafe(dist);
        emit message(tr("Distortion calculated"));
    }else{
        emit message(tr("Distortion parameter loaded"));
    }
    return true;
}

bool Solver::calculateK()
{
    emit message(tr("Loading matrix K..."));
    if(kModel->isEmpty()){
        emit message(tr("Matrix K is empty. Calculating K from corrected harp photos..."));

        if(!DistortionCorrectPhotoCircle()){
            emit message(tr("Distortion Correction of circle photos failed !"));
            return false;
        }
        Q_ASSERT(!noDistortion_photoCircleModel->isEmpty());
        QList<QImage> imageList=noDistortion_photoCircleModel->getImageList_threadSafe();
        KMatrix K=this->calculateK(imageList);
        kModel->saveKMatrix_threadSafe(K);
        emit message(tr("Matrix K generated"));
    }else{
        emit message(tr("Matrix K loaded"));
    }
    return true;
}

