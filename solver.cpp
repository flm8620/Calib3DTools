#include "solver.h"
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

