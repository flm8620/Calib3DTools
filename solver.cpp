#include "solver.h"

#include <QtGlobal>

Solver::Solver(QObject *parent) : QObject(parent)
{

}

static Distortion calculateDistortion(const ImageList &imageList)
{
    Q_ASSERT(!imageList.isEmpty());
    Distortion dist;
    dist << 1.0 << 2.0 << 3.0 << 4.0 << 5.0;
    return dist;
}

static QImage correctDistortion(const QImage &image, const Distortion &distortion )
{
    const static int LABEL_WIDTH = 240;
    const static int LABEL_HEIGHT = 30;
    const static QColor LABEL_BACKGROUND_COLOR("white");
    const static QColor LABEL_TEXT_COLOR("blue");
    const static char * LABEL_FONT_NAME = "Arial";
    const static int LABEL_FONT_SIZE = 24;
    const static char *LABEL_TEXT = "Distortion Corrected";

     QImage  result = image.convertToFormat(QImage::Format_RGB888);
     if(result.width()<LABEL_WIDTH)
         result = result.scaledToWidth(LABEL_WIDTH);
    if(result.height()<LABEL_HEIGHT)
        result = result.scaledToHeight(LABEL_HEIGHT);

    QRectF labelRect((result.width()-LABEL_WIDTH)/2, (result.height()-LABEL_HEIGHT)/2, LABEL_WIDTH, LABEL_HEIGHT );
    QPainter painter(&result);
    painter.setPen( QPen( LABEL_TEXT_COLOR ) );
    QFont labelFont( LABEL_FONT_NAME );
    labelFont.setPixelSize( LABEL_FONT_SIZE );
    painter.setFont( labelFont );

    painter.fillRect( labelRect, LABEL_BACKGROUND_COLOR );
    painter.drawText(labelRect, Qt::AlignCenter, LABEL_TEXT);

    return result;
}

static KValue calculateK(const ImageList& circlePhotoList)
{
    Q_ASSERT(!circlePhotoList.isEmpty());

    return {10.0, 10.0, 100.0, 100.0, 3.14};
}

static CameraPosSolution openMVGSolver(Target2D target2D, const ImageList& photoList, KMatrix K)
{
    CameraPosSolution s;
    s << QVector3D(10,10,10) << QVector3D(20,20,20);
    return s;
}

static CameraPosSolution strechaSolver(Target2D target2D, Target3D target3D, const ImageList& photoList, KValue K)
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
                            KMatrix *kMatrix,
                            Target2DContainer *point2DContainer,
                            Target3DContainer* point3DContainer)
{
    this->photoContainer=photoContainer;
    this->photoCircleContainer=photoCircleContainer;
    this->photoHarpContainer=photoHarpContainer;
    this->noDistortionPhotoContainer=noDistortion_photoContainer;
    this->noDistortionPhotoCircleContainer=noDistortion_photoCircleContainer;
    this->noDistortionPhotoHarpContainer=noDistortion_photoHarpContainer;
    this->kMatrix = kMatrix;
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
    Q_ASSERT(!kMatrix->isEmpty());

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
    KValue K=this->kMatrix->getValue();

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
    if(kMatrix->isEmpty()){
        emit message(tr("Matrix K is empty. Calculating K from corrected harp photos..."));

        if(!DistortionCorrectPhotoCircle()){
            emit message(tr("Distortion Correction of circle photos failed !"));
            return false;
        }
        Q_ASSERT(!noDistortionPhotoCircleContainer->isEmpty());
        ImageList imageList=noDistortionPhotoCircleContainer->getImageList_threadSafe();
        *(this->kMatrix) = ::calculateK(imageList);
        emit message(tr("Matrix K generated"));
    }else{
        emit message(tr("Matrix K loaded"));
    }
    return true;
}

