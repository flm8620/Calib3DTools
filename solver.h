#ifndef SOLVER_H
#define SOLVER_H

#include "imagelist.h"
#include "distrortion.h"
#include "kmatrix.h"
#include "target2d.h"
#include "target3d.h"
#include "cameraposition.h"

#include <QtCore>
#include <QtGui>

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
                        KMatrix* kMatrix,
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
    KMatrix* kMatrix;
    Target2DContainer* point2DContainer;
    Target3DContainer* point3DContainer;
};

#endif // SOLVER_H
