#include "openMVG/numeric/numeric.h"
#include "openMVG/cameras/PinholeCamera.hpp"
#include "openMVG/multiview/solver_resection_kernel.hpp"
#include "openMVG/multiview/solver_resection_p3p.hpp"
#include "openMVG/multiview/projection.hpp"
using namespace openMVG;
#include "openMVG/robust_estimation/robust_estimator_ACRansac.hpp"
#include "openMVG/robust_estimation/robust_estimator_ACRansacKernelAdaptator.hpp"
#include "openMVG/robust_estimation/robust_estimator_MaxConsensus.hpp"
#include "openMVG/robust_estimation/score_evaluator.hpp"
#include <ctime>
using namespace openMVG::robust;
static const size_t ACRANSAC_ITER = 10;

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "messager.h"
using namespace std;
namespace Strecha {
bool findCameraPosition(const std::vector<double> &K, const std::vector<double> &point2D,
                        const std::vector<double> &point3D, std::vector<double> &R_out,
                        std::vector<double> &T_out, std::vector<double> &center_out)
{
    bool valueAllOk = true;
    if (K.size() != 5) valueAllOk = false;
    if (point2D.size()%2 != 0) valueAllOk = false;
    if (point3D.size()%3 != 0) valueAllOk = false;
    if (point2D.size() == 0) valueAllOk = false;
    if (point3D.size() == 0) valueAllOk = false;
    if (point2D.size()/2 != point3D.size()/3) valueAllOk = false;
    if(!valueAllOk){
        libMsg::cout<<"Argument invalid for camera solution"<<libMsg::endl;
    }
    int pointCount = point2D.size()/2;

    srand(time(NULL));
    Mat3 Kmatrix;
    Mat x2D(2, pointCount);
    Mat x3D(3, pointCount);

    Kmatrix<<K[0], K[4], K[2], 0, K[1], K[3], 0, 0, 1;

    int idx = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < pointCount; ++j) {
            x2D(i, j) = point2D[idx];
            idx++;
        }
    }

    idx = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < pointCount; ++j) {
            x3D(i, j) = point3D[idx];
            idx++;
        }
    }
    std::vector<size_t> vec_inliers;
    Mat34 P;
    double errorMax = 4.0;
    size_t MINIMUM_SAMPLES = 0;
    typedef openMVG::euclidean_resection::P3PSolver SolverType;
    MINIMUM_SAMPLES = SolverType::MINIMUM_SAMPLES;

    typedef ACKernelAdaptorResection_K<SolverType, SolverType, UnnormalizerResection,
                                       Mat34> KernelType;

    KernelType kernel(x2D, x3D, Kmatrix);
    std::pair<double, double> ACRansacOut = ACRANSAC(kernel, vec_inliers, ACRANSAC_ITER, &P,
                                                     errorMax, true);
    errorMax = ACRansacOut.first;

    libMsg::cout<<"\n error max = "<<errorMax<<libMsg::endl;
    libMsg::cout<<"Point2D accepted: ";
    std::sort(vec_inliers.begin(), vec_inliers.end());
    for(int i=0;i<vec_inliers.size();++i){
        libMsg::cout<<vec_inliers[i]<<',';
    }
    libMsg::cout<<libMsg::endl<<libMsg::endl;

    Mat3 R, newK;
    Vec3 t;
    KRt_From_P(P, &newK, &R, &t);
    PinholeCamera cam(Kmatrix, R, t);

    R_out.clear();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            R_out.push_back(R(i, j));
    }
    T_out.clear();
    T_out.push_back(t(0));
    T_out.push_back(t(1));
    T_out.push_back(t(2));
    center_out.clear();
    center_out.push_back(cam._C(0));
    center_out.push_back(cam._C(1));
    center_out.push_back(cam._C(2));
    return true;
}
}
