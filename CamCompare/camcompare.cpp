#include "camcompare.h"

#include "messager.h"
#include "matrix.h"
#include "openmvgcompare.h"
#include <cmath>

using namespace libNumerics;
static double dist3d(const vector<double> &v1, const vector <double> &v2)
{
    return std::sqrt((v1-v2).qnorm());
}

static bool compareOpenMVG(std::vector<vector<double> > &C, std::vector<vector<double> > &Cc)
{
    int nCam = C.size();
    libMsg::cout<<"Distance Ratio for scaling: Cam/CamCompare"<<libMsg::endl;

    std::vector<Vec3> groundTruth, result, transformed;
    for (int i = 0; i < nCam; ++i) {
        Vec3 v;
        v(0) = C[i][0];
        v(1) = C[i][1];
        v(2) = C[i][2];
        groundTruth.push_back(v);
    }
    for (int i = 0; i < nCam; ++i) {
        Vec3 v;
        v(0) = Cc[i][0];
        v(1) = Cc[i][1];
        v(2) = Cc[i][2];
        result.push_back(v);
    }
    double Sout;
    Mat3 Rout;
    Vec3 tout;

    if (!openMVG::computeSimilarity(groundTruth, result, transformed, &Sout, &Rout, &tout))
        return false;
    std::cout<<"HEREf"<<std::endl;
    libMsg::cout<<"Scale="<<Sout<<libMsg::endl<<libMsg::endl;

    std::vector<Vec3> diff = transformed;
    for (int i = 0; i < nCam; ++i)
        diff[i] = transformed[i]-groundTruth[i];
    libMsg::cout<<"Difference: "<<libMsg::endl;

    for (int i = 0; i < nCam; ++i)
        libMsg::cout<<diff[i](0)<<'\t';
    libMsg::cout<<libMsg::endl;
    for (int i = 0; i < nCam; ++i)
        libMsg::cout<<diff[i](1)<<'\t';
    libMsg::cout<<libMsg::endl;
    for (int i = 0; i < nCam; ++i)
        libMsg::cout<<diff[i](2)<<'\t';
    libMsg::cout<<libMsg::endl;
    libMsg::cout<<"Distance: "<<libMsg::endl;
    for (int i = 0; i < nCam; ++i)
        libMsg::cout<<diff[i].norm()*1000<<"mm"<<'\t';
    libMsg::cout<<libMsg::endl<<libMsg::endl;
    return true;
}

static bool compareByAlign(std::vector<matrix<double> > &R, std::vector<matrix<double> > &Rc,
                           std::vector<vector<double> > &C, std::vector<vector<double> > &Cc)
{
    int nCam = R.size();
    libMsg::cout<<"Distance Ratio for scaling: Cam/CamCompare"<<libMsg::endl;
    double ratioMean = 0;
    int count = 0;
    for (int i = 0; i < nCam; ++i) {
        for (int j = i+1; j < nCam; ++j) {
            libMsg::cout<<"Cam"<<i+1<<" & Cam"<<j+1<<":\t";
            double dist = dist3d(C[i], C[j]);
            double distC = dist3d(Cc[i], Cc[j]);
            double ratio = dist/distC;
            ratioMean += ratio;
            count++;
            libMsg::cout<<dist<<" / "<<distC<<" =\t"<<ratio<<libMsg::endl;
        }
    }
    ratioMean /= count;
    libMsg::cout<<"Mean ratio="<<ratioMean<<libMsg::endl<<libMsg::endl;

    for (int centerIdx = 0; centerIdx < nCam; centerIdx++) {
        std::vector<vector<double> > Cc2C = Cc;
        libMsg::cout<<"Align to Cam "<<centerIdx+1<<libMsg::endl;
        vector<double> centralize = Cc[centerIdx];
        for (int i = 0; i < nCam; ++i) {
            Cc2C[i] = Cc[i]-centralize;
            Cc2C[i] = Cc2C[i]*ratioMean;
        }

        for (int i = 0; i < nCam; ++i)
            Cc2C[i] = R[centerIdx].t()*(Rc[centerIdx]*Cc2C[i]);
        vector<double> translation = C[centerIdx]-Cc2C[centerIdx];
        for (int i = 0; i < nCam; ++i)
            Cc2C[i] = Cc2C[i]+translation;

        std::vector<vector<double> > diff = Cc2C;
        for (int i = 0; i < nCam; ++i)
            diff[i] = Cc2C[i]-C[i];
        libMsg::cout<<"Difference: "<<libMsg::endl;

        for (int i = 0; i < nCam; ++i)
            libMsg::cout<<diff[i][0]<<'\t';
        libMsg::cout<<libMsg::endl;
        for (int i = 0; i < nCam; ++i)
            libMsg::cout<<diff[i][1]<<'\t';
        libMsg::cout<<libMsg::endl;
        for (int i = 0; i < nCam; ++i)
            libMsg::cout<<diff[i][2]<<'\t';
        libMsg::cout<<libMsg::endl;
        libMsg::cout<<"Distance: "<<libMsg::endl;
        for (int i = 0; i < nCam; ++i)
            libMsg::cout<<std::sqrt(diff[i].qnorm())*1000<<"mm"<<'\t';
        libMsg::cout<<libMsg::endl<<libMsg::endl;
    }
    return true;
}

bool CamSolver::camCompare(const CamSet &camSet1, const CamSet &camSet2)
{
    if (camSet1.size() != camSet2.size()) return false;
    if (camSet1.size() <= 1) return false;
    int nCam = camSet1.size();
    std::vector<matrix<double> > R, Rc;
    std::vector<vector<double> > C, Cc;
    for (int i = 0; i < camSet1.size(); ++i) {
        const std::vector<double> &r1 = camSet1[i].first;
        const std::vector<double> &r2 = camSet2[i].first;
        const std::vector<double> &c1 = camSet1[i].second;
        const std::vector<double> &c2 = camSet2[i].second;
        if (r1.size() != 9) return false;
        if (r2.size() != 9) return false;
        if (c1.size() != 3) return false;
        if (c2.size() != 3) return false;
        matrix<double> R1(3, 3), R2(3, 3);
        vector<double> C1(3), C2(3);
        R1(0, 0) = r1[0], R2(0, 0) = r2[0];
        R1(0, 1) = r1[1], R2(0, 1) = r2[1];
        R1(0, 2) = r1[2], R2(0, 2) = r2[2];
        R1(1, 0) = r1[3], R2(1, 0) = r2[3];
        R1(1, 1) = r1[4], R2(1, 1) = r2[4];
        R1(1, 2) = r1[5], R2(1, 2) = r2[5];
        R1(2, 0) = r1[6], R2(2, 0) = r2[6];
        R1(2, 1) = r1[7], R2(2, 1) = r2[7];
        R1(2, 2) = r1[8], R2(2, 2) = r2[8];
        R.push_back(R1);
        Rc.push_back(R2);
        C1(0) = c1[0], C2(0) = c2[0];
        C1(1) = c1[1], C2(1) = c2[1];
        C1(2) = c1[2], C2(2) = c2[2];
        C.push_back(C1);
        Cc.push_back(C2);
    }
    //if (!compareByAlign(R,Rc,C, Cc)) return false;
    if (!compareOpenMVG(C, Cc)) return false;
    return true;
}
