#include "solver.h"
#include <QImage>
solver::solver(QObject *parent) : QObject(parent)
{

}

Distortion solver::calculateDistortion(const QList<QImage> &imageList)
{
    return Distortion();
}

QImage solver::correctDistortion(const QImage &image, const Distortion &distortion)
{
    return QImage();
}

KMatrix solver::calculateK(const QList<QImage> &circlePhotoList)
{
    return KMatrix();
}

CameraPosSolution solver::openMVGSolver(Target2D target2D, const QList<QImage> &photoList, KMatrix K)
{
    return CameraPosSolution();
}

CameraPosSolution solver::strechaSolver(Target2D target2D, Target3D target3D, const QList<QImage> &photoList, KMatrix K)
{
    return CameraPosSolution();
}

