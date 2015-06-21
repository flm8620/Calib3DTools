#ifndef SOLVER_H
#define SOLVER_H


#include "imagelist.h"
#include "distortion.h"
#include "kmatrix.h"
#include "target2d.h"
#include "target3d.h"
#include "cameraposition.h"
#include "messager.h"
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
                        Distortion *distortion,
                        KMatrix* kMatrix,
                        Target2DContainer* point2DContainer,
                        Target3DContainer* point3DContainer,
                        libMsg::Messager* messager =0
                        );

    bool solve(CameraPosSolution &solu);
    bool DistortionCorrectPhoto();
    bool DistortionCorrectPhotoCircle();
    bool calculateDistortion();
    bool calculateK();
public slots:
    void startSolve();
private:
    ImageListContainer* photoContainer;
    ImageListContainer* photoCircleContainer;
    ImageListContainer* photoHarpContainer;
    ImageListContainer* noDistortionPhotoContainer;
    ImageListContainer* noDistortionPhotoCircleContainer;
    ImageListContainer* noDistortionPhotoHarpContainer;
    Distortion* distortion;
    KMatrix* kMatrix;
    Target2DContainer* point2DContainer;
    Target3DContainer* point3DContainer;
    libMsg::Messager* messager;
    void message(const char * message, libMsg::MessageType type=libMsg::M_INFO);
};

#endif // SOLVER_H
