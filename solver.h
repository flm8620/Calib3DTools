#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>
#include <QList>
#include <QPointF>
#include <QVector3D>
class QImage;
struct KMatrix{
    double fx,fy,x0,y0,s;
};

struct Distortion{
    QList<double> data;
};
struct Target2D{
    QList<QList<QPointF> > data;
};
struct Target3D{
    QList<QVector3D> data;
};
struct CameraPosSolution{
    QList<QVector3D> data;
};

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = 0);
    Distortion calculateDistortion(const QList<QImage>& imageList);
    QImage correctDistortion(const QImage& image,const Distortion& distortion);
    KMatrix calculateK(const QList<QImage>& circlePhotoList);
    CameraPosSolution openMVGSolver(Target2D target2D,const QList<QImage>& photoList,KMatrix K);
    CameraPosSolution strechaSolver(Target2D target2D,Target3D target3D,const QList<QImage>& photoList,KMatrix K);
signals:

public slots:
};

#endif // SOLVER_H
