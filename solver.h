#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>
#include <QList>
#include <QPointF>
#include <QVector3D>
class QImage;
class ImageListModel;
class DistortionModel;
class KMatrixModel;
class Point2DModel;
class Point3DModel;
class KMatrix{
public:
    double fx,fy,x0,y0,s;
};

class Distortion{
public:
    QList<double> data;
    bool isEmpty(){return data.size()==0;}
    void makeEmpty(){data.clear();}
};
class Target2D{
public:
    QList<QList<QPointF> > data;
    bool isEmpty(){return data.size()==0;}
    void makeEmpty(){data.clear();}
};
class Target3D{
public:
    QList<QVector3D> data;
    bool isEmpty(){return data.size()==0;}
    void makeEmpty(){data.clear();}
};
class CameraPosSolution{
public:
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
    void registerModels(ImageListModel* photoModel,
                        ImageListModel* photoCircleModel,
                        ImageListModel* photoHarpModel,
                        ImageListModel* noDistortion_photoModel,
                        ImageListModel* noDistortion_photoCircleModel,
                        ImageListModel* noDistortion_photoHarpModel,
                        DistortionModel* distModel,
                        KMatrixModel* kModel,
                        Point2DModel* point2DModel,
                        Point3DModel* point3DModel
                        );

    bool solve(CameraPosSolution &solu);
    bool DistortionCorrectPhoto();
    bool DistortionCorrectPhotoCircle();
    bool calculateDistortion();
    bool calculateK();
signals:
    void message(QString s,bool warning=false);
public slots:
    void startSolve();
private:
    ImageListModel* photoModel;
    ImageListModel* photoCircleModel;
    ImageListModel* photoHarpModel;
    ImageListModel* noDistortion_photoModel;
    ImageListModel* noDistortion_photoCircleModel;
    ImageListModel* noDistortion_photoHarpModel;
    DistortionModel* distModel;
    KMatrixModel* kModel;
    Point2DModel* point2DModel;
    Point3DModel* point3DModel;
};

#endif // SOLVER_H
