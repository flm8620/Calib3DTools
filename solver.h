#ifndef SOLVER_H
#define SOLVER_H

<<<<<<< HEAD
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
Q_DECLARE_METATYPE(KMatrix)
class Distortion{
public:
    QList<double> data;
    bool isEmpty(){return data.size()==0;}
    void makeEmpty(){data.clear();}
};
Q_DECLARE_METATYPE(Distortion)
class Target2D{
public:
    QList<QList<QPointF> > data;
    bool isEmpty(){return data.size()==0;}
    void makeEmpty(){data.clear();}
};
Q_DECLARE_METATYPE(Target2D)
class Target3D{
public:
    QList<QVector3D> data;
    bool isEmpty(){return data.size()==0;}
    void makeEmpty(){data.clear();}
};
Q_DECLARE_METATYPE(Target3D)
class CameraPosSolution{
public:
    QList<QVector3D> data;
};
=======
#include "imagelist.h"
#include "distrortion.h"
#include "kmatrix.h"
#include "target2d.h"
#include "target3d.h"
#include "cameraposition.h"

#include <QtCore>
#include <QtGui>
>>>>>>> origin/refactor

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = 0);
    void registerModels(ImageListContainer* photoContainer,
                        ImageListContainer* photoCircleContainer,
                        ImageListContainer* photoHarpContainer,
                        ImageListContainer* noDistortionPhotoContainer,
                        ImageListContainer* noDistortionPhotoCircleContainer,
                        ImageListContainer* noDistortionPhotoHarpContainer,
                        DistortionContainer* distContainer,
                        KMatrixContainer* kContainer,
                        Target2DContainer* point2DContainer,
                        Target3DContainer* point3DContainer
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
    ImageListContainer* photoContainer;
    ImageListContainer* photoCircleContainer;
    ImageListContainer* photoHarpContainer;
    ImageListContainer* noDistortionPhotoContainer;
    ImageListContainer* noDistortionPhotoCircleContainer;
    ImageListContainer* noDistortionPhotoHarpContainer;
    DistortionContainer* distContainer;
    KMatrixContainer* kContainer;
    Target2DContainer* point2DContainer;
    Target3DContainer* point3DContainer;
};

#endif // SOLVER_H
