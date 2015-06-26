#ifndef SOLVER_H
#define SOLVER_H

#include "imagelist.h"
#include "imagelistwithpoint2d.h"
#include "distortion.h"
#include "kmatrix.h"
#include "point3d.h"
#include "cameraposition.h"
#include "messager.h"
#include <QtCore>
#include <QtGui>

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = 0);
    void registerModels(ImageList *photoList, ImageList *circleList, ImageList *harpList,
                        ImageListWithPoint2D *undistortedPhotoPoint2DList, ImageList *undistortedCircleList,
                        ImageList *undistortedHarpList, ImageList *harpFeedbackList,
                        ImageList *circleFeedbackList, Distortion *distortion, KMatrix *kMatrix, Point3D *point3D,
                        libMsg::Messager *messager = 0);

public slots:
    bool onCalculateDistortion();
    bool onCalculateK();
    bool onCorrectPhoto();
    bool onCorrectCircle();

private:
    bool calculateDistortion();
    bool calculateK();
    bool correctPhoto();
    bool correctCircle();
    bool solveCamPos();

    bool calculateDistortionThread();
    bool calculateKThread();
    bool correctPhotoThread();
    bool correctCircleThread();
    bool solveCamPosThread();

    void message(std::string message, libMsg::MessageType type = libMsg::M_INFO);
    ImageList *photoList;
    ImageList *circleList;
    ImageList *harpList;
    ImageListWithPoint2D *undistortedPhotoPoint2DList;
    ImageList *undistortedCircleList;
    ImageList *undistortedHarpList;
    ImageList *harpFeedbackList;
    ImageList *circleFeedbackList;
    Distortion *distortion;
    KMatrix *kMatrix;
    Point3D *point3D;
    libMsg::Messager *messager;
};

#endif // SOLVER_H
