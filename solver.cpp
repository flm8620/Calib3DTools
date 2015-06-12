#include "solver.h"

#include <QtGlobal>

Solver::Solver(QObject *parent) : QObject(parent)
{

}

static Distortion calculateDistortion(const ImageList &imageList)
{
    Q_ASSERT(!imageList.isEmpty());
    Distortion dist;
    dist.setMaxOrder(3);
    for(int i=0;i<dist.getTotalNum();++i){
        dist[i]=1.2345678901;
    }
    return dist;
}

static QImage correctDistortion(const QImage &image, const Distortion &distortion)
{
    QImage result=image;
    QPainter painter(&result);
    QRectF rect(100,100,500,500);
    painter.drawText(rect,"Distortion Corrected");
    return result;
}

static KMatrix calculateK(const ImageList& circlePhotoList)
{
    Q_ASSERT(!circlePhotoList.isEmpty());

    double  K[5] = {10.0, 10.0, 100.0, 100.0, 0.0};
    return K;
}

static CameraPosSolution openMVGSolver(Target2D target2D, const ImageList& photoList, KMatrix K)
{
    CameraPosSolution s;
    s << QVector3D(10,10,10) << QVector3D(20,20,20);
    return s;
}

static CameraPosSolution strechaSolver(Target2D target2D, Target3D target3D, const ImageList& photoList, KMatrix K)
{
    CameraPosSolution s;
    s << QVector3D(10,10,10) << QVector3D(20,20,20);
    return s;
}

void Solver::registerModels(ImageListContainer *photoContainer,
                            ImageListContainer *photoCircleContainer,
                            ImageListContainer *photoHarpContainer,
                            ImageListContainer *noDistortion_photoContainer,
                            ImageListContainer *noDistortion_photoCircleContainer,
                            ImageListContainer *noDistortion_photoHarpContainer,
                            DistortionContainer *distContainer,
                            KMatrixContainer *kContainer,
                            Target2DContainer *point2DContainer,
                            Target3DContainer* point3DContainer)
{
    this->photoContainer=photoContainer;
    this->photoCircleContainer=photoCircleContainer;
    this->photoHarpContainer=photoHarpContainer;
    this->noDistortionPhotoContainer=noDistortion_photoContainer;
    this->noDistortionPhotoCircleContainer=noDistortion_photoCircleContainer;
    this->noDistortionPhotoHarpContainer=noDistortion_photoHarpContainer;
    this->kContainer=kContainer;
    this->distContainer =distContainer;
    this->point2DContainer =point2DContainer;
    this->point3DContainer =point3DContainer;
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
    Q_ASSERT(!noDistortionPhotoContainer->isEmpty());
    emit message(tr(""));

    if(!calculateK()){
        emit message(tr("Failed to calculate matrix K !"));
        return false;
    }
    emit message(tr(""));
    Q_ASSERT(!kContainer->isEmpty());

    if(point2DContainer->isEmpty()){
        emit message(tr("You should set at least one 2D point"),true);
        return false;
    }else{
        emit message(tr("2D points loaded"));
    }

    if(point3DContainer->isEmpty()){
        emit message(tr("You should set at least one 3D point"),true);
        return false;
    }else{
        emit message(tr("3D points loaded"));
    }

    Target2D target2D=this->point2DContainer->getTarget2D_threadSafe();
    Target3D target3D=this->point3DContainer->getTarget3D_threadSafe();

    if(target2D.pointCount()!=target3D.count()){
        emit message(tr("You should set same amount of 2D and 3D point"),true);
        return false;
    }

    ImageList photoList=this->noDistortionPhotoContainer->getImageList_threadSafe();
    KMatrix K=this->kContainer->getKMatrix_threadSafe();

    solu = strechaSolver(target2D,target3D,photoList,K);
    return true;
}

bool Solver::DistortionCorrectPhoto()
{
    emit message(tr("Loading distortion correction of photo..."));
    if(noDistortionPhotoContainer->isEmpty()){
        emit message(tr("Distortion correction of photo is empty. Correct distortion for photos..."));
        if(!calculateDistortion()){
            emit message(tr("Failed to load distortion !"));
            return false;
        }
        Q_ASSERT(!this->distContainer->isEmpty());

        Distortion dist=this->distContainer->getDistortion_threadSafe();

        emit message(tr("Loading photos..."));
        if(this->photoContainer->isEmpty()){
            emit message(tr("No photo found ! You should load photos."),true);
            return false;
        }else{
            emit message(tr("Photos loaded"));
        }

        ImageList photoList=photoContainer->getImageList_threadSafe();
        ImageList outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append(correctDistortion(image, dist));
        }
        noDistortionPhotoContainer->saveImageList_threadSafe(outputList);
        emit message(tr("Distortion correction of photo finished."));
    }else{
        emit message(tr("Distortion correction of photo loaded."));
    }
    return true;
}

bool Solver::DistortionCorrectPhotoCircle()
{
    emit message(tr("Loading distortion correction of circle photo..."));
    if(noDistortionPhotoCircleContainer->isEmpty()){
        emit message(tr("Distortion correction of circle photo is empty. Correct distortion for circle photos..."));
        if(!calculateDistortion()){
            emit message(tr("Failed to load distortion !"));
            return false;
        }
        Q_ASSERT(!distContainer->isEmpty());

        Distortion dist=distContainer->getDistortion_threadSafe();

        emit message(tr("Loading circle photos..."));
        if(this->photoCircleContainer->isEmpty()){
            emit message(tr("No circle photo found ! You should load circle photos."),true);
            return false;
        }else{
            emit message(tr("Circle photos loaded"));
        }

        ImageList photoList=photoCircleContainer->getImageList_threadSafe();
        ImageList outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append( correctDistortion(image,dist) );
        }
        noDistortionPhotoCircleContainer->saveImageList_threadSafe(outputList);

        emit message(tr("Distortion correction of photo finished."));
    }else{
        emit message(tr("Distortion correction of circle photo loaded."));
    }
    return true;

}

bool Solver::calculateDistortion( )
{
    emit message(tr("Loading distortion parameter..."));
    if(distContainer->isEmpty()){
        emit message(tr("Distortion parameter is empty. Calculating distortion parameter"));

        if(photoHarpContainer->isEmpty()){
            emit message(tr("You should load harp photos"),true);
            return false;
        }
        ImageList imageList=photoHarpContainer->getImageList_threadSafe();
        Distortion dist = ::calculateDistortion(imageList);
        distContainer->saveDistortion_threadSafe(dist);
        emit message(tr("Distortion calculated"));
    }else{
        emit message(tr("Distortion parameter loaded"));
    }
    return true;
}

bool Solver::calculateK( )
{
    emit message(tr("Loading matrix K..."));
    if(kContainer->isEmpty()){
        emit message(tr("Matrix K is empty. Calculating K from corrected harp photos..."));

        if(!DistortionCorrectPhotoCircle()){
            emit message(tr("Distortion Correction of circle photos failed !"));
            return false;
        }
        Q_ASSERT(!noDistortionPhotoCircleContainer->isEmpty());
        ImageList imageList=noDistortionPhotoCircleContainer->getImageList_threadSafe();
        KMatrix K= ::calculateK(imageList);
        kContainer->saveKMatrix_threadSafe(K);
        emit message(tr("Matrix K generated"));
    }else{
        emit message(tr("Matrix K loaded"));
    }
    return true;
}

