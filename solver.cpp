#include "solver.h"
#include "distortion/polyEstimation.h"
#include "distortion/distCorrection.h"
#include "distortion/libImage/image.h"
#include <QtGlobal>
#include <QDebug>
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
/* a : order in numeric lib
 * b : order in Qt
 * a0 * x^0*y^0    b0 * x^3*y^0
 * a1 * x^1*y^0    b1 * x^2*y^1
 * a2 * x^0*y^1    b2 * x^1*y^2
 * a3 * x^2*y^0    b3 * x^0*y^3
 * a4 * x^1*y^1    b4 * x^2*y^0
 * a5 * x^0*y^2    b5 * x^1*y^1
 * a6 * x^3*y^0    b6 * x^0*y^2
 * a7 * x^2*y^1    b7 * x^1*y^0
 * a8 * x^1*y^2    b8 * x^0*y^1
 * a9 * x^0*y^3    b9 * x^0*y^0
 */
static bool PolyOrderConvert_Qt2Lib(std::vector<double> &poly, int maxOrder)
{
    if (poly.size() != (maxOrder+1)*(maxOrder+2)/2*2) return false;
    std::vector<double> lib(poly.size());
    int sizexy=poly.size()/2;
    int qPos=0,libPos=sizexy;
    //Poly for X
    for(int order=0;order<=maxOrder;++order){
        int numCoef=order+1;
        libPos-=numCoef;
        for(int j=0;j<numCoef;++j){
            lib[libPos]=poly[qPos];
            libPos++;
            qPos++;
        }
        libPos-=numCoef;
    }
    //Poly for Y
    qPos=sizexy;
    libPos=sizexy*2;
    for(int order=0;order<=maxOrder;++order){
        int numCoef=order+1;
        libPos-=numCoef;
        for(int j=0;j<numCoef;++j){
            lib[libPos]=poly[qPos];
            libPos++;
            qPos++;
        }
        libPos-=numCoef;
    }
    poly=lib;
    return true;
}

static bool PolyOrderConvert_Lib2Qt(std::vector<double> &poly, int maxOrder)
{
    if (poly.size() != (maxOrder+1)*(maxOrder+2)/2*2) return false;
    std::vector<double> Qpoly(poly.size());
    int sizexy=poly.size()/2;
    int qPos=0,libPos=sizexy;
    //Poly for X
    for(int order=0;order<=maxOrder;++order){
        int numCoef=order+1;
        libPos-=numCoef;
        for(int j=0;j<numCoef;++j){
            Qpoly[qPos]=poly[libPos];
            libPos++;
            qPos++;
        }
        libPos-=numCoef;
    }
    //Poly for Y
    qPos=sizexy;
    libPos=sizexy*2;
    for(int order=0;order<=maxOrder;++order){
        int numCoef=order+1;
        libPos-=numCoef;
        for(int j=0;j<numCoef;++j){
            Qpoly[qPos]=poly[libPos];
            libPos++;
            qPos++;
        }
        libPos-=numCoef;
    }
    poly=Qpoly;
    return true;
}

static void QColorImageToImageDoubleRGB(const QImage &qimage, image_double_RGB &out)
{
    Q_ASSERT(!qimage.isNull());
    int w = qimage.width(), h = qimage.height();
    out = new_image_double_RGB(w, h);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            out->Rdata[x+y*w] = qRed(qimage.pixel(x, y));
            out->Gdata[x+y*w] = qGreen(qimage.pixel(x, y));
            out->Bdata[x+y*w] = qBlue(qimage.pixel(x, y));
        }
    }
}

static void QGrayImageToImageDouble(const QImage &qimage, image_double &out)
{
    Q_ASSERT(!qimage.isNull());
    int w = qimage.width(), h = qimage.height();
    out = new_image_double(w, h);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++)
            out->data[x+y*w] = qGray(qimage.pixel(x, y));
    }
}

static QImage ImageDoubleRGBToQColorImage(image_double_RGB in)
{
    int w = in->xsize, h = in->ysize;
    QImage image(w, h, QImage::Format_RGB32);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int red = in->Rdata[x+y*w];
            int green = in->Gdata[x+y*w];
            int blue = in->Bdata[x+y*w];
            image.setPixel(x, y, qRgb(red, green, blue));
        }
    }
    return image;
}

static QImage ImageDoubleToQGrayImage(image_double in)
{
    int w = in->xsize, h = in->ysize;
    QImage image(w, h, QImage::Format_RGB32);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int color = in->data[x+y*w];
            image.setPixel(x, y, qRgb(color, color, color));
        }
    }
    return image;
}

static void distortionValue2Polynome(const DistortionValue &distValue,
                                     std::vector<double> &polynome)
{
    polynome.clear();
    Q_ASSERT(distValue.isValid());
    for (int i = 0; i < distValue._size; ++i)
        polynome.push_back(distValue._XYData[i].first);
    for (int i = 0; i < distValue._size; ++i)
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
    std::vector<image_char> charImageList;
    for (int i = 0; i < imageList.size(); ++i)
        charImageList.push_back(qimage_to_image_char(imageList.at(i)));
    std::vector<double> polynome;
    int order = 11;

    if (DistortionModule::polyEstime(charImageList, polynome, order)){
        PolyOrderConvert_Lib2Qt(polynome,order);
        polynome2DistortionValue(distValue, polynome, order);
    }
    // else distValue is empty
    for (int i = 0; i < charImageList.size(); ++i)
        free_image_char(charImageList[i]);
    return distValue;
}

static QImage correctDistortion(const QImage &image, Distortion *distortion)
{
    Q_ASSERT(!image.isNull());
    DistortionValue distValue = distortion->getValue();
    std::vector<double> polynome;
    QImage result;
    distortionValue2Polynome(distValue, polynome);
    PolyOrderConvert_Qt2Lib(polynome,distValue._maxOrder);
    if (image.isGrayscale()) {
        qDebug()<<"isGrayscale";
        image_double in, out;
        QGrayImageToImageDouble(image, in);
        DistortionModule::distortionCorrect(in, out, polynome, distortion->maxOrder());
        result = ImageDoubleToQGrayImage(out);
        free_image_double(in);
        free_image_double(out);
    } else {
        qDebug()<<"isRGB";
        image_double_RGB in, out;
        QColorImageToImageDoubleRGB(image, in);
        DistortionModule::distortionCorrect_RGB(in, out, polynome,
                                                distortion->maxOrder());
        result = ImageDoubleRGBToQColorImage(out);
        free_image_double_RGB(in);
        free_image_double_RGB(out);
    }
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
