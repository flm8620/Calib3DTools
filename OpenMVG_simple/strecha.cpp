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
#include <iomanip>
using namespace std;
static printdouble(const char *s, double a){
    std::cout<<s<<std::setprecision(16)<<a<<" "<<std::hex<<*reinterpret_cast<long long *>(&a)
             <<std::endl;
}
namespace Strecha {
bool findCameraPosition(const std::vector<double> &K, const std::vector<double> &point2D,
                        const std::vector<double> &point3D, std::vector<double> &R_out,
                        std::vector<double> &T_out, std::vector<double> &center_out)
{
    if (K.size() != 5) return false;
    if (point2D.size()%2 != 0) return false;
    if (point3D.size()%3 != 0) return false;
    if (point2D.size() == 0) return false;
    if (point3D.size() == 0) return false;

    if (point2D.size()/2 != point3D.size()/3) return false;
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

    // std::cout << P << std::endl;
    // std::cout << errorMax << std::endl;

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
}
}
