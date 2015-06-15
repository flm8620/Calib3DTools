#include "solver.h"

#include <QtGlobal>

Solver::Solver(QObject *parent) : QObject(parent)
{

}

static void calculateDistortion(const ImageList &imageList, Distortion * result)
{
    Q_ASSERT(!imageList.isEmpty());
    for(int i=0; i<5; i++)
        (*result)[i] = i + 1.0;
}

static QImage correctDistortion(const QImage &image, const Distortion * distortion )
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
                            Distortion *dist,
                            KMatrix *kMatrix,
                            Target2DContainer *point2DContainer,
                            Target3DContainer* point3DContainer, Messager *messager)
{
    this->photoContainer=photoContainer;
    this->photoCircleContainer=photoCircleContainer;
    this->photoHarpContainer=photoHarpContainer;
    this->noDistortionPhotoContainer=noDistortion_photoContainer;
    this->noDistortionPhotoCircleContainer=noDistortion_photoCircleContainer;
    this->noDistortionPhotoHarpContainer=noDistortion_photoHarpContainer;
    this->kMatrix = kMatrix;
    this->distortion =dist;
    this->point2DContainer =point2DContainer;
    this->point3DContainer =point3DContainer;
    this->messager = messager;
}

void Solver::message(const char * message, Messager::MessageType type)
{
    if(this->messager != NULL)
        this->messager->message(message, type);
}


void Solver::startSolve()
{
    CameraPosSolution solu;
    if(!solve(solu)){
        this->message("Solve failed!", Messager::WARN);
    }else{
        this->message("Solve succeed");
    }
    //return solu;
}

bool Solver::solve(CameraPosSolution &solu)
{
    if(!DistortionCorrectPhoto()){
        this->message("Distortion correction of photo failed !");
        return false;
    }
    Q_ASSERT(!noDistortionPhotoContainer->isEmpty());
    this->message("");

    if(!calculateK()){
        this->message("Failed to calculate matrix K !");
        return false;
    }
    this->message("");
    Q_ASSERT(!kMatrix->isEmpty());

    if(point2DContainer->isEmpty()){
        this->message("You should set at least one 2D point", Messager::WARN);
        return false;
    }else{
        this->message("2D points loaded");
    }

    if(point3DContainer->isEmpty()){
        this->message("You should set at least one 3D point", Messager::WARN);
        return false;
    }else{
        this->message("3D points loaded");
    }

    Target2D target2D=this->point2DContainer->getTarget2D_threadSafe();
    Target3D target3D=this->point3DContainer->getTarget3D_threadSafe();

    if(target2D.pointCount()!=target3D.count()){
        this->message("You should set same amount of 2D and 3D point", Messager::WARN);
        return false;
    }

    ImageList photoList=this->noDistortionPhotoContainer->getImageList_threadSafe();
    KValue K=this->kMatrix->getValue();

    solu = strechaSolver(target2D,target3D,photoList,K);
    return true;
}

bool Solver::DistortionCorrectPhoto()
{
    this->message("Loading distortion correction of photo...");
    if(noDistortionPhotoContainer->isEmpty()){
        this->message("Distortion correction of photo is empty. Correct distortion for photos...");
        if(!calculateDistortion()){
            this->message("Failed to load distortion !");
            return false;
        }
        Q_ASSERT(this->distortion->isNotEmpty());

        this->message("Loading photos...");
        if(this->photoContainer->isEmpty()){
            this->message("No photo found ! You should load photos.", Messager::WARN);
            return false;
        }else{
            this->message("Photos loaded");
        }

        ImageList photoList=photoContainer->getImageList_threadSafe();
        ImageList outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append(correctDistortion(image, this->distortion));
        }
        noDistortionPhotoContainer->saveImageList_threadSafe(outputList);
        this->message("Distortion correction of photo finished.");
    }else{
        this->message("Distortion correction of photo loaded.");
    }
    return true;
}

bool Solver::DistortionCorrectPhotoCircle()
{
    this->message("Loading distortion correction of circle photo...");
    if(noDistortionPhotoCircleContainer->isEmpty()){
        this->message("Distortion correction of circle photo is empty. Correct distortion for circle photos...");
        if(!calculateDistortion()){
            this->message("Failed to load distortion !");
            return false;
        }
        Q_ASSERT(this->distortion->isNotEmpty());

        this->message("Loading circle photos...");
        if(this->photoCircleContainer->isEmpty()){
            this->message("No circle photo found ! You should load circle photos.", Messager::WARN);
            return false;
        }else{
            this->message("Circle photos loaded");
        }

        ImageList photoList=photoCircleContainer->getImageList_threadSafe();
        ImageList outputList;
        QImage image;
        foreach (image, photoList) {
            outputList.append( correctDistortion(image,this->distortion) );
        }
        noDistortionPhotoCircleContainer->saveImageList_threadSafe(outputList);

        this->message("Distortion correction of photo finished.");
    }else{
        this->message("Distortion correction of circle photo loaded.");
    }
    return true;

}

bool Solver::calculateDistortion( )
{
    this->message("Loading distortion parameter...");
    if(this->distortion->isEmpty()){
        this->message("Distortion parameter is empty. Calculating distortion parameter");

        if(photoHarpContainer->isEmpty()){
            this->message("You should load harp photos", Messager::WARN);
            return false;
        }
        ImageList imageList=photoHarpContainer->getImageList_threadSafe();
        ::calculateDistortion(imageList, this->distortion);
        this->message("Distortion calculated");
    }else{
        this->message("Distortion parameter loaded");
    }
    return true;
}

bool Solver::calculateK( )
{
    this->message("Loading matrix K...");
    if(kMatrix->isEmpty()){
        this->message("Matrix K is empty. Calculating K from corrected harp photos...");

        if(!DistortionCorrectPhotoCircle()){
            this->message("Distortion Correction of circle photos failed !");
            return false;
        }
        Q_ASSERT(!noDistortionPhotoCircleContainer->isEmpty());
        ImageList imageList=noDistortionPhotoCircleContainer->getImageList_threadSafe();
        *(this->kMatrix) = ::calculateK(imageList);
        this->message("Matrix K generated");
    }else{
        this->message("Matrix K loaded");
    }
    return true;
}

