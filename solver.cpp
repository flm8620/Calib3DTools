#include "solver.h"

#include <QtGlobal>
#include <QDebug>
#include <vector>
#include <QtConcurrent>

#include "image.h"
#include "qimageconvert.h"

#include "distCorrection.h"
#include "kmatrixsolve.h"
#include "strecha.h"
using namespace libMsg;
Solver::Solver(QObject *parent) : QObject(parent)
{
}

// deprecated
///**
// * @brief PolyOrderConvert_Qt2Lib
// * @param poly
// * @param maxOrder
// * a : order in numeric lib
// * b : order in Qt
// * a0 * x^0*y^0    b0 * x^3*y^0
// *                 b1 * x^2*y^1
// * a1 * x^1*y^0    b2 * x^1*y^2
// * a2 * x^0*y^1    b3 * x^0*y^3
// *
// * a3 * x^2*y^0    b4 * x^2*y^0
// * a4 * x^1*y^1    b5 * x^1*y^1
// * a5 * x^0*y^2    b6 * x^0*y^2
// *
// * a6 * x^3*y^0    b7 * x^1*y^0
// * a7 * x^2*y^1    b8 * x^0*y^1
// * a8 * x^1*y^2
// * a9 * x^0*y^3    b9 * x^0*y^0
// */
// static bool PolyOrderConvert_Qt2Lib(Bi<std::vector<double> > &poly)
// {
// size_t polysize =poly.x.size(), ysize =poly.y.size();
// int maxOrder = (isqrt(8*polysize+1) - 1)/2-1;
// if (polysize != (maxOrder+1)*(maxOrder+2)/2 || polysize!=ysize)
// return false;

// poly.x.reserve(polysize*2-maxOrder-1);
// poly.y.reserve(polysize*2-maxOrder-1);
// std::vector<double>::const_iterator xbegin = poly.x.cbegin(), ybegin = poly.y.cbegin();
// for(int order = maxOrder-1; order>=0; order--)
// for(int i=0, idx = (order*(order+1)/2); i<=order; i++, idx++) {
// poly.x.push_back(poly.x[idx]);
// poly.y.push_back(poly.y[idx]);
// }
// int newtop = maxOrder*(maxOrder+1)/2;
// poly.x.erase( xbegin, xbegin + newtop );
// poly.y.erase( ybegin, ybegin + newtop );
// poly.x.shrink_to_fit();
// poly.y.shrink_to_fit();
// return true;
// }

static bool PolyOrderConvert_Lib2Qt(std::vector<double> &poly, int maxOrder)
{
    if (poly.size() != (maxOrder+1)*(maxOrder+2)/2*2) return false;
    std::vector<double> Qpoly(poly.size());
    int sizexy = poly.size()/2;
    int qPos = 0, libPos = sizexy;
    // Poly for X
    for (int order = 0; order <= maxOrder; ++order) {
        int numCoef = order+1;
        libPos -= numCoef;
        for (int j = 0; j < numCoef; ++j) {
            Qpoly[qPos] = poly[libPos];
            libPos++;
            qPos++;
        }
        libPos -= numCoef;
    }
    // Poly for Y
    qPos = sizexy;
    libPos = sizexy*2;
    for (int order = 0; order <= maxOrder; ++order) {
        int numCoef = order+1;
        libPos -= numCoef;
        for (int j = 0; j < numCoef; ++j) {
            Qpoly[qPos] = poly[libPos];
            libPos++;
            qPos++;
        }
        libPos -= numCoef;
    }
    poly = Qpoly;
    return true;
}

static void distortionValue2Polynome(const DistortionValue &distValue,
                                     Bi<std::vector<double> > &polynome)
{
    polynome.x.clear();
    polynome.y.clear();
    Q_ASSERT(distValue.isValid());
    for (int i = 0; i < distValue._size; ++i) {
        polynome.x.push_back(distValue._XYData[i].first);
        polynome.y.push_back(distValue._XYData[i].second);
    }
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

static bool distortionFromImages(ImageList *imageList, ImageList *feedbackList,
                                 DistortionValue &out)
{
    QList<QPair<QString, QImage> > snapshot;
    imageList->getContent(snapshot);
    if (snapshot.size() == 0) return false;
    std::vector<ImageGray<BYTE> > byteImageList(snapshot.size());
    for (int i = 0; i < snapshot.size(); ++i)
        QImage2ImageByte(snapshot[i].second, byteImageList[i]);

    libMsg::abortIfAsked();
    std::vector<double> polynome;
    int order = 11;
    std::vector<std::vector<std::vector<std::pair<double, double> > > > detectedLines;
    if (!DistortionModule::polyEstime(byteImageList, polynome, order, detectedLines))
        return false;
    PolyOrderConvert_Lib2Qt(polynome, order);
    polynome2DistortionValue(out, polynome, order);

    QList<QPair<QString, QImage> > feedback;
    for (int i = 0; i < snapshot.size(); ++i) {
        QString name = snapshot[i].first+" Feedback";
        QImage image = snapshot[i].second.convertToFormat(QImage::Format_RGB32);
        checkQImageMemory(image);
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        std::vector<std::vector<std::pair<double, double> > > &lines = detectedLines[i];
        for (int j = 0; j < lines.size(); ++j) {
            std::vector<std::pair<double, double> > &oneline = lines[j];
            double x1, y1, x2, y2;
            x1 = oneline[0].first;
            y1 = oneline[0].second;
            for (int k = 1; k < oneline.size(); ++k) {
                x2 = oneline[k].first;
                y2 = oneline[k].second;
                painter.setPen(Qt::green);
                painter.drawLine(x1, y1, x2, y2);
// painter.setPen(Qt::red);
// painter.drawPoint(x2, y2);
                painter.fillRect(x2-2, y2-2, 5, 5, Qt::red);
                x1 = x2;
                y1 = y2;
            }
        }
        feedback.append(qMakePair(name, image));
    }
    feedbackList->clear();
    feedbackList->setContent(feedback);
    return true;
}

static bool correctDistortion(const QImage &imageIn, QImage &out, Distortion *distortion)
{
    if (imageIn.isNull()) {
        libMsg::cout<<"DistortionCorrection: image is empty!"<<libMsg::endl;
        return false;
    }
    DistortionValue distValue = distortion->getValue();
    if (!distValue.isValid() || distValue._size == 0) {
        libMsg::cout<<"DistortionCorrection: distortion polynomial is empty!"<<libMsg::endl;
        return false;
    }
    Bi<std::vector<double> > polynome;
    distortionValue2Polynome(distValue, polynome);
// bool success = PolyOrderConvert_Qt2Lib(polynome);
// Q_ASSERT(success);

    QImage result;
    if (imageIn.isGrayscale()) {
        libMsg::cout<<"Color type: Gray scale "<<libMsg::endl;
        ImageGray<double> in, out;
        QImage2ImageDouble(imageIn, in);
        if (!DistortionModule::distortionCorrect(in, out, polynome))
            return false;
        ImageDouble2QImage(out, result);
    } else {
        libMsg::cout<<"Color type: RGB "<<libMsg::endl;
        ImageRGB<double> in, out;
        QColorImage2ImageDoubleRGB(imageIn, in);
        if (!DistortionModule::distortionCorrect_RGB(in, out, polynome))
            return false;
        ImageDoubleRGB2QColorImage(out, result);
    }
    out = result;
    return true;
}

static bool calculateKFromImages(ImageList *circlePhotoList, ImageList *feedbackList,
                                 KValue &kValue)
{
    QList<QPair<QString, QImage> > snapshot;
    circlePhotoList->getContent(snapshot);
    if (snapshot.size() == 0) return false;
    std::vector<QImage> stdImageList;
    std::vector<QImage> feedback;
    for (int i = 0; i < snapshot.size(); ++i)
        stdImageList.push_back(snapshot[i].second);
    double alpha, beta, u0, v0, gamma;

    bool ok = KMatrixSolve::KMatrixSolver(stdImageList, feedback, alpha, beta, u0, v0, gamma, 3.0,
                                          1.0);

    QList<QPair<QString, QImage> > tempFeedback;
    for (int i = 0; i < feedback.size(); ++i)
        tempFeedback.push_back(qMakePair(QString("Feedback_%1").arg(1+i), feedback[i]));
    feedbackList->clear();
    feedbackList->setContent(tempFeedback);

    if (!ok) return false;
    kValue = {alpha, beta, u0, v0, gamma };
    return true;
}

void Solver::registerModels(ImageList *photoList, ImageList *circleList, ImageList *harpList,
                            ImageListWithPoint2D *undistortedPhotoPoint2DList,
                            ImageList *undistortedCircleList, ImageList *undistortedHarpList,
                            ImageList *harpFeedbackList, ImageList *circleFeedbackList,
                            Distortion *distortion, KMatrix *kMatrix, Point3D *point3D,
                            CameraPos *camPos, libMsg::Messager *messager)
{
    this->photoList = photoList;
    this->circleList = circleList;
    this->harpList = harpList;
    this->undistortedPhotoPoint2DList = undistortedPhotoPoint2DList;
    this->undistortedCircleList = undistortedCircleList;
    this->undistortedHarpList = undistortedHarpList;
    this->harpFeedbackList = harpFeedbackList;
    this->circleFeedbackList = circleFeedbackList;
    this->kMatrix = kMatrix;
    this->distortion = distortion;
    this->point3D = point3D;
    this->camPos = camPos;
    this->messager = messager;
}

void Solver::message(std::string message, MessageType type)
{
    if (this->messager != NULL)
        this->messager->message(message, type);
}

bool Solver::solveCamPos()
{
    if (this->undistortedPhotoPoint2DList->isEmpty()) {
        this->message("Didn't find undistorted photos!", M_WARN);
        return false;
    }

    if (this->kMatrix->isEmpty()) {
        this->message("Didn't find Matrix K!", M_WARN);
        return false;
    }
    if (this->undistortedPhotoPoint2DList->pointCount() == 0) {
        this->message("You should set at least one 2D point", M_WARN);
        return false;
    }

    if (this->point3D->isEmpty()) {
        this->message("You should set at least one 3D point", M_WARN);
        return false;
    }

    if (undistortedPhotoPoint2DList->pointCount() != this->point3D->pointCount()) {
        this->message("You should set same amount of 2D and 3D point", M_WARN);
        return false;
    }
    KValue Kvalue = this->kMatrix->getValue();
    QList<QList<QPointF> > qpt2DList;
    QList<QVector3D> qpt3D;
    this->undistortedPhotoPoint2DList->getAllPoints(qpt2DList);
    this->point3D->getContent(qpt3D);
    std::vector<double> K, pt2D, pt3D, matrixR, vectorT, center;
    CameraPosValue camPosValue;

    K.push_back(Kvalue.fx);
    K.push_back(Kvalue.fy);
    K.push_back(Kvalue.x0);
    K.push_back(Kvalue.y0);
    K.push_back(Kvalue.s);

    for (int i = 0; i < qpt3D.size(); ++i)
        pt3D.push_back(qpt3D[i].x());
    for (int i = 0; i < qpt3D.size(); ++i)
        pt3D.push_back(qpt3D[i].y());
    for (int i = 0; i < qpt3D.size(); ++i)
        pt3D.push_back(qpt3D[i].z());

    for (int imageId = 0; imageId < qpt2DList.size(); ++imageId) {
        pt2D.clear();
        matrixR.clear();
        vectorT.clear();
        center.clear();
        QList<QPointF> &qpt2D = qpt2DList[imageId];
        for (int i = 0; i < qpt2D.size(); ++i)
            pt2D.push_back(qpt2D[i].x());
        for (int i = 0; i < qpt2D.size(); ++i)
            pt2D.push_back(qpt2D[i].y());
        if (!Strecha::findCameraPosition(K, pt2D, pt3D, matrixR, vectorT, center))
            return false;
        camPosValue.data.append(qMakePair(matrixR, center));
    }
    if (!this->camPos->setValue(camPosValue))
        return false;
    return true;
}

bool Solver::calculateDistortionThread()
{
    bool ok;
    if (this->processLock.tryLock()) {
        libMsg::abortFlag.resetFlag();
        try{
            ok = this->calculateDistortion();
        }catch (MyException &bad) {
            this->message("Exception catched :"+std::string(bad.what()), M_ERROR);
            ok = false;
        }
        libMsg::abortFlag.resetFlag();
        this->processLock.unlock();
    } else {
        ok = false;
        this->message("Please wait for current job to finish", M_WARN);
    }
    return ok;
}

bool Solver::calculateKThread()
{
    bool ok;
    if (this->processLock.tryLock()) {
        libMsg::abortFlag.resetFlag();
        try{
            ok = this->calculateK();
        }catch (MyException &bad) {
            this->message("Exception catched :"+std::string(bad.what()), M_ERROR);
            ok = false;
        }
        libMsg::abortFlag.resetFlag();
        this->processLock.unlock();
    } else {
        ok = false;
        this->message("Please wait for current job to finish", M_WARN);
    }
    return ok;
}

bool Solver::correctPhotoThread()
{
    bool ok;
    if (this->processLock.tryLock()) {
        libMsg::abortFlag.resetFlag();
        try{
            ok = this->correctPhoto();
        }catch (MyException &bad) {
            this->message("Exception catched :"+std::string(bad.what()), M_ERROR);
            ok = false;
        }
        libMsg::abortFlag.resetFlag();
        this->processLock.unlock();
    } else {
        ok = false;
        this->message("Please wait for current job to finish", M_WARN);
    }
    return ok;
}

bool Solver::correctCircleThread()
{
    bool ok;
    if (this->processLock.tryLock()) {
        libMsg::abortFlag.resetFlag();
        try{
            ok = this->correctCircle();
        }catch (MyException &bad) {
            this->message("Exception catched :"+std::string(bad.what()), M_ERROR);
            ok = false;
        }
        libMsg::abortFlag.resetFlag();
        this->processLock.unlock();
    } else {
        ok = false;
        this->message("Please wait for current job to finish", M_WARN);
    }
    return ok;
}

bool Solver::solveCamPosThread()
{
    bool ok;
    if (this->processLock.tryLock()) {
        libMsg::abortFlag.resetFlag();
        try{
            ok = this->solveCamPos();
        }catch (MyException &bad) {
            this->message("Exception catched :"+std::string(bad.what()), M_ERROR);
            ok = false;
        }
        libMsg::abortFlag.resetFlag();
        this->processLock.unlock();
    } else {
        ok = false;
        this->message("Please wait for current job to finish", M_WARN);
    }
    return ok;
}

bool Solver::onCalculateDistortion()
{
    QtConcurrent::run(this, &Solver::calculateDistortionThread);
}

bool Solver::onCalculateK()
{
    QtConcurrent::run(this, &Solver::calculateKThread);
}

bool Solver::onCorrectPhoto()
{
    QtConcurrent::run(this, &Solver::correctPhotoThread);
}

bool Solver::onCorrectCircle()
{
    QtConcurrent::run(this, &Solver::correctCircleThread);
}

bool Solver::onSolveStrecha()
{
    QtConcurrent::run(this, &Solver::solveCamPosThread);
}

bool Solver::correctPhoto()
{
    if (this->undistortedPhotoPoint2DList->isEmpty()) {
        this->message("Correct distortion for photos...");
        qint64 start = QDateTime::currentMSecsSinceEpoch();
        if (this->distortion->isEmpty()) {
            this->message("Didn't find distortion polynomial!");
            return false;
        } else {
            this->message("Distortion polynomial found.");
        }
        if (this->photoList->isEmpty()) {
            this->message("Didn't find photos !", M_WARN);
            return false;
        } else {
            this->message("Photos loaded.");
        }
        QList<QPair<QString, QImage> > correctionList;
        QList<QPair<QString, QImage> > resultList;
        this->photoList->getContent(correctionList);
        QPair<QString, QImage> pair;
        int k = 0;
        foreach (pair, correctionList) {
            QImage result;
            this->message("Correct photo:"+pair.first.toStdString());
            if (!correctDistortion(pair.second, result, this->distortion)) {
                this->message(
                    "Distortion correction of photo failed. FileName:"+pair.first.toStdString(),
                    M_WARN);
                return false;
            }
            resultList.append(qMakePair(QString("Photo_corrected_%1").arg(k+1), result));
            ++k;
        }
        this->undistortedPhotoPoint2DList->setContent(resultList);
        libMsg::cout << static_cast<double>(QDateTime::currentMSecsSinceEpoch()-start)/1000.
                     <<"Seconds spent."<<libMsg::endl;
        this->message("Distortion correction of photo finished.");
    } else {
        this->message("Undistorted photos already exist, please remove them.");
        return false;
    }
    return true;
}

bool Solver::correctCircle()
{
    if (this->undistortedCircleList->isEmpty()) {
        if (this->circleList->isEmpty()) {
            this->message("No circle photo found !", M_WARN);
            return false;
        }

        qint64 start = QDateTime::currentMSecsSinceEpoch();
        QList<QPair<QString, QImage> > correctionList;
        QList<QPair<QString, QImage> > resultList;
        this->circleList->getContent(correctionList);
        QPair<QString, QImage> pair;
        int k = 0;
        foreach (pair, correctionList) {
            QImage result;
            this->message("Correct photo:"+pair.first.toStdString());
            if (!correctDistortion(pair.second, result, this->distortion)) {
                this->message(
                    "Distortion correction of circle photo failed. FileName:"+pair.first.toStdString(),
                    M_WARN);
                return false;
            }
            resultList.append(qMakePair(QString("Circle_corrected_%1").arg(k+1), result));
            ++k;
        }
        this->undistortedCircleList->setContent(resultList);
        libMsg::cout << static_cast<double>(QDateTime::currentMSecsSinceEpoch()-start)/1000.
                     <<"Seconds spent."<<libMsg::endl;
        this->message("Distortion correction of photo finished.");
    } else {
        this->message("Undistorted circle photos already exist, please remove them.");
        return false;
    }
    return true;
}

bool Solver::calculateDistortion()
{
    if (this->distortion->isEmpty()) {
        qint64 start = QDateTime::currentMSecsSinceEpoch();
        this->message("Starting calculation of distortion polynomial...");

        if (this->harpList->isEmpty()) {
            this->message("You should load harp photos", M_WARN);
            return false;
        }
        DistortionValue distValue;
        if (!distortionFromImages(this->harpList, this->harpFeedbackList, distValue)) {
            this->message("Distortion calculation failed!", M_WARN);
            return false;
        }
        if (!this->distortion->setValue(distValue)) {
            this->message("Distortion calculated by program turns out to be corrupted");
            return false;
        }
        libMsg::cout << static_cast<double>(QDateTime::currentMSecsSinceEpoch()-start)/1000.
                     <<"Seconds spent."<<libMsg::endl;
        this->message("Distortion calculated");
    } else {
        this->message(
            "Distortion polynomial already exist, please clear it if you want to calculate a new one");
    }
    return true;
}

bool Solver::calculateK()
{
    if (this->kMatrix->isEmpty()) {
        this->message("Starting calculation of Matrix K");
        qint64 start = QDateTime::currentMSecsSinceEpoch();
        if (this->undistortedCircleList->isEmpty()) {
            this->message(
                "Didn't find undistorted circle photo. Please load them,"
                "or you can generate them from original circle photos");
            return false;
        } else {
            this->message("Undistorted circle photo loaded.");
        }
        KValue kValue;
        if (!calculateKFromImages(this->undistortedCircleList, this->circleFeedbackList, kValue)) {
            this->message("Failed to calculate K Matrix", M_WARN);
            return false;
        }
        this->kMatrix->setValue(kValue);
        libMsg::cout << static_cast<double>(QDateTime::currentMSecsSinceEpoch()-start)/1000.
                     <<"Seconds spent."<<libMsg::endl;
        this->message("Matrix K generated");
        return true;
    } else {
        this->message(
            "Matrix K already exist, please clear it if you want to calculate a new one");
        return false;
    }
}
