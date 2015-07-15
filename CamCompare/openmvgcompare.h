#ifndef OPENMVGCOMPARE_H
#define OPENMVGCOMPARE_H
#include <vector>
#include "../eigen/Eigen/Core"
#include "../eigen/Eigen/Eigenvalues"
#include "../eigen/Eigen/Geometry"
#include "../eigen/Eigen/LU"
#include "../eigen/Eigen/QR"
#include "../eigen/Eigen/SparseCore"
#include "../eigen/Eigen/SVD"
#include "../eigen/Eigen/StdVector"
//#include "../eigen/unsupported/Eigen/ModuleHeader"
#include "../eigen/unsupported/Eigen/NonLinearOptimization"
#include "../eigen/unsupported/Eigen/NumericalDiff"
typedef Eigen::Vector3d Vec3;
typedef Eigen::MatrixXd Mat;
typedef Eigen::VectorXd Vec;
typedef Eigen::Matrix<double, 3, 3> Mat3;
namespace openMVG {
using namespace Eigen;
// Generic functor Levenberg-Marquardt minimization
template<typename _Scalar, int NX = Dynamic, int NY = Dynamic>
struct Functor
{
    typedef _Scalar Scalar;
    enum {
        InputsAtCompileTime = NX,
        ValuesAtCompileTime = NY
    };
    typedef Matrix<Scalar, InputsAtCompileTime, 1> InputType;
    typedef Matrix<Scalar, ValuesAtCompileTime, 1> ValueType;
    typedef Matrix<Scalar, ValuesAtCompileTime, InputsAtCompileTime> JacobianType;

    const int m_inputs, m_values;

    Functor() : m_inputs(InputsAtCompileTime),
        m_values(ValuesAtCompileTime)
    {
    }

    Functor(int inputs, int values) : m_inputs(inputs),
        m_values(values)
    {
    }

    int inputs() const
    {
        return m_inputs;
    }

    int values() const
    {
        return m_values;
    }

    // you should define that in the subclass :
    // void operator() (const InputType& x, ValueType* v, JacobianType* _j=0) const;
};
}  // namespace openMVG

namespace openMVG {
namespace geometry {
/** 3D rigid transformation estimation (7 dof)
 * Compute a Scale Rotation and Translation rigid transformation.
 * This transformation provide a distortion-free transformation
 * using the following formulation Xb = S * R * Xa + t.
 * "Least-squares estimation of transformation parameters between two point patterns",
 * Shinji Umeyama, PAMI 1991, DOI: 10.1109/34.88573
 *
 * \param[in] x1 The first 3xN matrix of euclidean points
 * \param[in] x2 The second 3xN matrix of euclidean points
 * \param[out] S The scale factor
 * \param[out] t The 3x1 translation
 * \param[out] R The 3x3 rotation
 *
 * \return true if the transformation estimation has succeeded
 *
 * \note Need at least 3 points
 */

static bool FindRTS(const Mat &x1, const Mat &x2, double *S, Vec3 *t, Mat3 *R)
{
    assert(3 == x1.rows());
    assert(3 <= x1.cols());
    assert(x1.rows() == x2.rows());
    assert(x1.cols() == x2.cols());

    std::cout<<"HERE3"<<std::endl;
    const int n = static_cast<int>(x1.cols());

    // Get the transformation via Umeyama's least squares algorithm. This returns
    // a matrix of the form:
    // [ s * R t]
    // [ 0 1]
    // from which we can extract the scale, rotation, and translation.
    std::cout<<"HERE4"<<std::endl;
    const Eigen::Matrix4d transform
        = Eigen::umeyama(x1, x2, true);
    std::cout<<"HERE5"<<std::endl;
    *R = transform.topLeftCorner<3, 3>();

    std::cout<<"HERE6"<<std::endl;
    if (R->determinant() < 0)
        return false;

    std::cout<<"HERE7"<<std::endl;
    *S = pow(R->determinant(), 1.0 / 3.0);
    *R /= *S;
    *t = transform.topRightCorner<3, 1>();

    return true;
}

// Eigen LM functor to refine translation, Rotation and Scale parameter.
struct lm_SRTRefine_functor : Functor<double>
{
    lm_SRTRefine_functor(int inputs, int values, const Mat &x1, const Mat &x2, const double &S,
                         const Mat3 &R, const Vec &t) : Functor<double>(inputs, values),
        _x1(x1),
        _x2(x2),
        _t(t),
        _R(R),
        _S(S)
    {
    }

    int operator()(const Vec &x, Vec &fvec) const
    {
        // convert x to rotation matrix and a translation vector and a Scale factor
        // x = {tx,ty,tz,anglex,angley,anglez,S}
        Vec3 transAdd = x.block<3, 1>(0, 0);
        Vec3 rot = x.block<3, 1>(3, 0);
        double Sadd = x(6);

        // Build the rotation matrix
        Mat3 Rcor
            = (Eigen::AngleAxis<double>(rot(0), Vec3::UnitX())
               * Eigen::AngleAxis<double>(rot(1), Vec3::UnitY())
               * Eigen::AngleAxis<double>(rot(2), Vec3::UnitZ())).toRotationMatrix();

        const Mat3 nR = _R*Rcor;
        const Vec3 nt = _t+transAdd;
        const double nS = _S+Sadd;

        // Evaluate re-projection errors
        Vec3 proj;
        for (Mat::Index i = 0; i < _x1.cols(); ++i) {
            proj = _x2.col(i) -  (nS *  nR * (_x1.col(i)) + nt);
            fvec[i*3] = proj(0);
            fvec[i*3+1] = proj(1);
            fvec[i*3+2] = proj(2);
        }
        return 0;
    }

    Mat _x1, _x2;
    Vec3 _t;
    Mat3 _R;
    double _S;
};

// Eigen LM functor to refine Rotation.
struct lm_RRefine_functor : Functor<double>
{
    lm_RRefine_functor(int inputs, int values, const Mat &x1, const Mat &x2, const double &S,
                       const Mat3 &R, const Vec &t) : Functor<double>(inputs, values),
        _x1(x1),
        _x2(x2),
        _t(t),
        _R(R),
        _S(S)
    {
    }

    int operator()(const Vec &x, Vec &fvec) const
    {
        // convert x to rotation matrix
        // x = {anglex,angley,anglez}
        Vec3 rot = x.block<3, 1>(0, 0);

        // Build the rotation matrix
        Mat3 Rcor
            = (Eigen::AngleAxis<double>(rot(0), Vec3::UnitX())
               * Eigen::AngleAxis<double>(rot(1), Vec3::UnitY())
               * Eigen::AngleAxis<double>(rot(2), Vec3::UnitZ())).toRotationMatrix();

        const Mat3 nR = _R*Rcor;
        const Vec3 nt = _t;
        const double nS = _S;

        // Evaluate re-projection errors
        Vec3 proj;
        for (Mat::Index i = 0; i < _x1.cols(); ++i) {
            proj = _x2.col(i) -  (nS *  nR * (_x1.col(i)) + nt);
            fvec[i*3] = proj(0);
            fvec[i*3+1] = proj(1);
            fvec[i*3+2] = proj(2);
        }
        return 0;
    }

    Mat _x1, _x2;
    Vec3 _t;
    Mat3 _R;
    double _S;
};

/** 3D rigid transformation refinement using LM
 * Refine the Scale, Rotation and translation rigid transformation
 * using a Levenberg-Marquardt opimization.
 *
 * \param[in] x1 The first 3xN matrix of euclidean points
 * \param[in] x2 The second 3xN matrix of euclidean points
 * \param[out] S The initial scale factor
 * \param[out] t The initial 3x1 translation
 * \param[out] R The initial 3x3 rotation
 *
 * \return none
 */
static void Refine_RTS(const Mat &x1, const Mat &x2, double *S, Vec3 *t, Mat3 *R)
{
    {
        lm_SRTRefine_functor functor(7, 3*x1.cols(), x1, x2, *S, *R, *t);

        Eigen::NumericalDiff<lm_SRTRefine_functor> numDiff(functor);

        Eigen::LevenbergMarquardt<Eigen::NumericalDiff<lm_SRTRefine_functor> > lm(numDiff);
        lm.parameters.maxfev = 1000;
        Vec xlm = Vec::Zero(7); // The deviation vector {tx,ty,tz,rotX,rotY,rotZ,S}

        lm.minimize(xlm);

        Vec3 transAdd = xlm.block<3, 1>(0, 0);
        Vec3 rot = xlm.block<3, 1>(3, 0);
        double SAdd = xlm(6);

        // Build the rotation matrix
        Mat3 Rcor
            = (Eigen::AngleAxis<double>(rot(0), Vec3::UnitX())
               * Eigen::AngleAxis<double>(rot(1), Vec3::UnitY())
               * Eigen::AngleAxis<double>(rot(2), Vec3::UnitZ())).toRotationMatrix();

        *R = (*R)*Rcor;
        *t = (*t)+transAdd;
        *S = (*S)+SAdd;
    }

    // Refine rotation
    {
        lm_RRefine_functor functor(3, 3*x1.cols(), x1, x2, *S, *R, *t);

        Eigen::NumericalDiff<lm_RRefine_functor> numDiff(functor);

        Eigen::LevenbergMarquardt<Eigen::NumericalDiff<lm_RRefine_functor> > lm(numDiff);
        lm.parameters.maxfev = 1000;
        Vec xlm = Vec::Zero(3); // The deviation vector {rotX,rotY,rotZ}

        lm.minimize(xlm);

        Vec3 rot = xlm.block<3, 1>(0, 0);

        // Build the rotation matrix
        Mat3 Rcor
            = (Eigen::AngleAxis<double>(rot(0), Vec3::UnitX())
               * Eigen::AngleAxis<double>(rot(1), Vec3::UnitY())
               * Eigen::AngleAxis<double>(rot(2), Vec3::UnitZ())).toRotationMatrix();

        *R = (*R)*Rcor;
    }
}
} // namespace geometry
bool computeSimilarity(
    const std::vector<Vec3> &vec_camPosGT, const std::vector<Vec3> &vec_camPosComputed,
    std::vector<Vec3> &vec_camPosComputed_T, double *Sout, Mat3 *Rout, Vec3 *tout)
{
    if (vec_camPosGT.size() != vec_camPosComputed.size()) {
        std::cerr << "Cannot perform registration, vector sizes are different" << std::endl;
        return false;
    }

    // Move input point in appropriate container
    Mat x1(3, vec_camPosGT.size());
    Mat x2(3, vec_camPosGT.size());
    for (size_t i = 0; i < vec_camPosGT.size(); ++i) {
        x1.col(i) = vec_camPosComputed[i];
        x2.col(i) = vec_camPosGT[i];
    }
    // Compute rigid transformation p'i = S R pi + t

    std::cout<<"HERE2"<<std::endl;
    double S;
    Vec3 t;
    Mat3 R;
    openMVG::geometry::FindRTS(x1, x2, &S, &t, &R);
    std::cout << "\n Non linear refinement" << std::endl;
    openMVG::geometry::Refine_RTS(x1, x2, &S, &t, &R);

    vec_camPosComputed_T.resize(vec_camPosGT.size());
    std::vector<double> vec_residualErrors(vec_camPosGT.size());
    for (size_t i = 0; i < vec_camPosGT.size(); ++i) {
        Vec3 newPos = S * R * (vec_camPosComputed[i]) + t;
        vec_camPosComputed_T[i] = newPos;
        double dResidual = (newPos - vec_camPosGT[i]).norm();
        vec_residualErrors[i] = dResidual;
    }

    *Sout = S;
    *Rout = R;
    *tout = t;
    return true;
}
} // namespace openMVG

#endif // OPENMVGCOMPARE_H
