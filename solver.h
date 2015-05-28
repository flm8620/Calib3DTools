#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>
template<typename T> class QList;
class QImage;
struct KMatrix{
    double a;
};

struct Distortion{
    double a2,a4,a6,a8,a10;
};
struct Target2D{
    double a;
};
struct Target3D{
    double a;
};
struct CameraPosSolution{
    double a;
};

class solver : public QObject
{
    Q_OBJECT
public:
    explicit solver(QObject *parent = 0);
    Distortion calculateDistortion(const QList<QImage>& imageList);
    QImage correctDistortion(const QImage& image,const Distortion& distortion);
    KMatrix calculateK(const QList<QImage>& circlePhotoList);
    CameraPosSolution openMVGSolver(Target2D target2D,const QList<QImage>& photoList,KMatrix K);
    CameraPosSolution strechaSolver(Target2D target2D,Target3D target3D,const QList<QImage>& photoList,KMatrix K);
signals:

public slots:
};

#endif // SOLVER_H
