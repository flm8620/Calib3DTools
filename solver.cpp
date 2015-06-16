#include "solver.h"
#include "distortion/polyEstimation.h"
#include "distortion/libImage/image.h"
#include <QtGlobal>
#include <vector>
Solver::Solver(QObject *parent) : QObject(parent)
{
}

image_char qimage_to_image_char(const QImage &qimage)
{
    int w = qimage.width(), h = qimage.height();
    image_char image = new_image_char(w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            image->data[ x + y * w ] = qGray(qimage.pixel(x, y));
    return image;
}

static void distortionValue2Polynome(const DistortionValue &distValue,
                                     std::vector<double> &polynome)
{
    polynome.clear();
    Q_ASSERT(distValue.isValid());
    for (int i = 0; i <distValue._size; ++i)
        polynome.push_back(distValue._XYData[i].first);
    for (int i = 0; i <distValue._size; ++i)
        polynome.push_back(distValue._XYData[i].second);
}

static void polynome2DistortionValue(DistortionValue &distValue,
                                     const std::vector<double> &polynome, int maxOrder)
{
    distValue.setMaxOrder(maxOrder);
    Q_ASSERT(polynome.size() == 2*distValue._size);// one for Xparam one for Yparam
    for (int i = 0; i < distValue._size; ++i) {
        distValue._XYData[i].first = polynome[i];
        distValue._XYData[i].second = polynome[i+distValue._size];
    }
}

static DistortionValue calculateDistortion(const ImageList &imageList)
{
    Q_ASSERT(!imageList.isEmpty());
    DistortionValue distValue;
    std::vector<image_char> doubleList;
    for (int i = 0; i < imageList.size(); ++i)
        doubleList.push_back(qimage_to_image_char(imageList.at(i)));
    std::vector<double> polynome;
    int order = 11;

    if (PolyEstimation::polyEstime(doubleList, polynome, order))
        polynome2DistortionValue(distValue, polynome, order);
    // else distValue is empty
    for (int i = 0; i < doubleList.size(); ++i)
        free_image_char(doubleList[i]);
    return distValue;
}

static QImage correctDistortion(const QImage &image, const Distortion &distortion)
{
    Q_ASSERT(!image.isNull());
    DistortionValue distValue = distortion.getValue();
    std::vector<double> polynome;
    distortionValue2Polynome(distValue, polynome);
    // TODO: use real function

    const static int LABEL_WIDTH = 240;
    const static int LABEL_HEIGHT = 30;
    const static QColor LABEL_BACKGROUND_COLOR("white");
    const static QColor LABEL_TEXT_COLOR("blue");
    const static char *LABEL_FONT_NAME = "Arial";
    const static int LABEL_FONT_SIZE = 24;
    const static char *LABEL_TEXT = "Distortion Corrected";

    QImage result = image.convertToFormat(QImage::Format_RGB888);
    if (result.width() < LABEL_WIDTH)
        result = result.scaledToWidth(LABEL_WIDTH);
    if (result.height() < LABEL_HEIGHT)
        result = result.scaledToHeight(LABEL_HEIGHT);

    QRectF labelRect((result.width()-LABEL_WIDTH)/2,
                     (result.height()-LABEL_HEIGHT)/2, LABEL_WIDTH, LABEL_HEIGHT);
    QPainter painter(&result);
    painter.setPen(QPen(LABEL_TEXT_COLOR));
    QFont labelFont(LABEL_FONT_NAME);
    labelFont.setPixelSize(LABEL_FONT_SIZE);
    painter.setFont(labelFont);

    painter.fillRect(labelRect, LABEL_BACKGROUND_COLOR);
    painter.drawText(labelRect, Qt::AlignCenter, LABEL_TEXT);

    return result;
}

static KValue calculateK(const ImageList &circlePhotoList)
{
    Q_ASSERT(!circlePhotoList.isEmpty());
    KValue k = {10.0, 10.0, 100.0, 100.0, 3.14};
    return k;
}

static CameraPosSolution openMVGSolver(Target2D target2D, const ImageList &photoList, KMatrix K)
{
    CameraPosSolution s;
    s << QVector3D(10, 10, 10) << QVector3D(20, 20, 20);
    return s;
}

static CameraPosSolution strechaSolver(Target2D target2D, Target3D target3D,
                                       const ImageList &photoList, KValue K)
{
    CameraPosSolution s;
    s << QVector3D(10, 10, 10) << QVector3D(20, 20, 20);
    return s;
}

void Solver::registerModels(ImageListContainer *photoContainer,
                            ImageListContainer *photoCircleContainer,
                            ImageListContainer *photoHarpContainer,
                            ImageListContainer *noDistortion_photoContainer,
                            ImageListContainer *noDistortion_photoCircleContainer,
                            ImageListContainer *noDistortion_photoHarpContainer,
                            Distortion *distortion, KMatrix *kMatrix,
                            Target2DContainer *point2DContainer,
                            Target3DContainer *point3DContainer, Messager *messager)
{
    this->photoContainer = photoContainer;
    this->photoCircleContainer = photoCircleContainer;
    this->photoHarpContainer = photoHarpContainer;
    this->noDistortionPhotoContainer = noDistortion_photoContainer;
    this->noDistortionPhotoCircleContainer = noDistortion_photoCircleContainer;
    this->noDistortionPhotoHarpContainer = noDistortion_photoHarpContainer;
    this->kMatrix = kMatrix;
    this->distortion = distortion;
    this->point2DContainer = point2DContainer;
    this->point3DContainer = point3DContainer;
    this->messager = messager;
}

void Solver::message(const char *message, Messager::MessageType type)
{
    if (this->messager != NULL)
        this->messager->message(message, type);
}

void Solver::startSolve()
{
    CameraPosSolution solu;
    if (!solve(solu))
        this->message("Solve failed!", Messager::M_WARN);
    else
        this->message("Solve succeed");
    // return solu;
}

bool Solver::solve(CameraPosSolution &solu)
{
    if (!DistortionCorrectPhoto()) {
        this->message("Distortion correction of photo failed !");
        return false;
    }
    Q_ASSERT(!noDistortionPhotoContainer->isEmpty());
    this->message("");

    if (!calculateK()) {
        this->message("Failed to calculate matrix K !");
        return false;
    }
    this->message("");
    Q_ASSERT(!kMatrix->isEmpty());

    if (point2DContainer->isEmpty()) {
        this->message("You should set at least one 2D point", Messager::M_WARN);
        return false;
    } else {
        this->message("2D points loaded");
    }

    if (point3DContainer->isEmpty()) {
        this->message("You should set at least one 3D point", Messager::M_WARN);
        return false;
    } else {
        this->message("3D points loaded");
    }

    Target2D target2D = this->point2DContainer->getTarget2D_threadSafe();
    Target3D target3D = this->point3DContainer->getTarget3D_threadSafe();

    if (target2D.pointCount() != target3D.count()) {
        this->message("You should set same amount of 2D and 3D point", Messager::M_WARN);
        return false;
    }

    ImageList photoList = this->noDistortionPhotoContainer->getImageList_threadSafe();
    KValue K = this->kMatrix->getValue();

    solu = strechaSolver(target2D, target3D, photoList, K);
    return true;
}

bool Solver::DistortionCorrectPhoto()
{
    this->message("Loading distortion correction of photo...");
    if (noDistortionPhotoContainer->isEmpty()) {
        this->message("Distortion correction of photo is empty. Correct distortion for photos...");
        if (!calculateDistortion()) {
            this->message("Failed to load distortion !");
            return false;
        }
        Q_ASSERT(!this->distortion->isEmpty());

        this->message("Loading photos...");
        if (this->photoContainer->isEmpty()) {
            this->message("No photo found ! You should load photos.", Messager::M_WARN);
            return false;
        } else {
            this->message("Photos loaded");
        }

        ImageList photoList = photoContainer->getImageList_threadSafe();
        ImageList outputList;
        QImage image;
        foreach (image, photoList)
            outputList.append(correctDistortion(image, distortion));
        noDistortionPhotoContainer->saveImageList_threadSafe(outputList);
        this->message("Distortion correction of photo finished.");
    } else {
        this->message("Distortion correction of photo loaded.");
    }
    return true;
}

bool Solver::DistortionCorrectPhotoCircle()
{
    this->message("Loading distortion correction of circle photo...");
    if (noDistortionPhotoCircleContainer->isEmpty()) {
        this->message(
            "Distortion correction of circle photo is empty. Correct distortion for circle photos...");
        if (!calculateDistortion()) {
            this->message("Failed to load distortion !");
            return false;
        }
        Q_ASSERT(!this->distortion->isEmpty());

        this->message("Loading circle photos...");
        if (this->photoCircleContainer->isEmpty()) {
            this->message("No circle photo found ! You should load circle photos.",
                          Messager::M_WARN);
            return false;
        } else {
            this->message("Circle photos loaded");
        }

        ImageList photoList = photoCircleContainer->getImageList_threadSafe();
        ImageList outputList;
        QImage image;
        foreach (image, photoList)
            outputList.append(correctDistortion(image, distortion));
        noDistortionPhotoCircleContainer->saveImageList_threadSafe(outputList);

        this->message("Distortion correction of photo finished.");
    } else {
        this->message("Distortion correction of circle photo loaded.");
    }
    return true;
}

bool Solver::calculateDistortion()
{
    this->message("Loading distortion parameter...");
    if (distortion->isEmpty()) {
        this->message("Distortion parameter is empty. Calculating distortion parameter ...");

        if (photoHarpContainer->isEmpty()) {
            this->message("You should load harp photos", Messager::M_WARN);
            return false;
        }
        ImageList imageList = photoHarpContainer->getImageList_threadSafe();

        bool ok = distortion->setValue(::calculateDistortion(imageList));
        Q_ASSERT(ok);
        if (distortion->isEmpty()) {
            this->message("Distortion calculation failed!", Messager::M_WARN);
            return false;
        }
        this->message("Distortion calculated");
    } else {
        this->message("Distortion parameter loaded");
    }
    return true;
}

bool Solver::calculateK()
{
    this->message("Loading matrix K...");
    if (kMatrix->isEmpty()) {
        this->message("Matrix K is empty. Calculating K from corrected harp photos...");

        if (!DistortionCorrectPhotoCircle()) {
            this->message("Distortion Correction of circle photos failed !");
            return false;
        }
        Q_ASSERT(!noDistortionPhotoCircleContainer->isEmpty());
        ImageList imageList = noDistortionPhotoCircleContainer->getImageList_threadSafe();
        this->kMatrix->setValue(::calculateK(imageList));
        this->message("Matrix K generated");
    } else {
        this->message("Matrix K loaded");
    }
    return true;
}
