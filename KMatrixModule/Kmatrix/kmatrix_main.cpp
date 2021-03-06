#include "kmatrix_main.h"

#include <vector>
#include <iostream>

#include "messager.h"
#include "matrix.h"
#include "ellipse_operations.h"

#include "Hmatrix.h"
#include "Kmatrix.h"

using namespace libNumerics;

#define PI 3.14159265358979323846

template<typename T>
matrix<T> vec2mat(vector<T> v, int w, int h)
{
    matrix<T> m(h, w);
    int n = v.size();
    assert(n == w*h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            int idx = j*w+i;
            m(j, i) = v[idx];
        }
    }
    return m;
}

template<typename T>
vector<T> mat2vec(const matrix<T> &m, int l)
{
    vector<T> v(l);
    int w = m.ncol();
    int h = m.nrow();
    assert(l == w*h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            int idx = j*w+i;
            v[idx] = m(j, i);
        }
    }
    return v;
}

template<typename T>
bool extractK_real(std::vector<matrix<T> > &S, std::vector<matrix<T> > &Ellipse_centers, T tolFun,
                   std::vector<matrix<double> > &CHS, matrix<T> &Kout)
{
    int nimage = Ellipse_centers.size();
    int ncircle = S.size();
    assert(nimage > 0 && (S.size() == Ellipse_centers[0].ncol()));
    std::vector<matrix<T> > H;
    matrix<T> XY(2, ncircle);
    for (int i = 0; i < ncircle; i++) {
        T x, y;
        getEllipseCenter(S[i], x, y);
        XY(0, i) = x;
        XY(1, i) = y;
    }
    std::vector<matrix<T> > H_ellip(nimage);
    std::vector<matrix<T> > H_point(nimage);

    // calculate homographies through minimization of d|CHS-CH0S|
    for (int i = 0; i < nimage; i++) {
        matrix<T> H_ini;
        if (!solveHomography(XY, Ellipse_centers[i], H_ini)) return false;
        H_point[i] = H_ini;
        LMhomography2<T> HeLMA(S, Ellipse_centers[i]);
        HeLMA.relativeTol = 1e-9;
        vector<T> trgData = vector<T>::zeros(ncircle);
        vector<T> h_ = mat2vec(H_ini.inv(), 9);
        T rmse_ellip = HeLMA.minimize(h_, trgData, tolFun);
        matrix<T> H_fin = (vec2mat(h_, 3, 3)).inv();
        H_ellip[i] = H_fin;
        libMsg::cout<<"Image_"<<i<<"\t"<<"Iterations: "<<HeLMA.iterations<<" RMSE_ellipse: "
                    <<rmse_ellip<<libMsg::endl;
        CHS.push_back( matrix<T>::zeros(2, ncircle));
        matrix<T> HCS = matrix<T>::zeros(2, ncircle);
        rotateVirtualImg(S, H_ellip[i], CHS[i], HCS);
        libMsg::abortIfAsked();
    }
    matrix<T> K_ellip;
    matrix<T> K_point;
    if (!extractKfromH(H_ellip, K_ellip)) return false;
    if (!extractKfromH(H_point, K_point)) return false;
    T ea, eb, eu, ev, eg;
    errorKparams(K_point, K_ellip, ea, eb, eu, ev, eg);
    libMsg::cout<<"Compare K_point and K_ellip:"<<libMsg::endl;
    libMsg::cout<<"( K_point - K_ellip ) / K_point"<<libMsg::endl;
    libMsg::cout<<"alpha:\t"<<ea<<" %"<<libMsg::endl;
    libMsg::cout<<"beta:\t"<<eb<<" %"<<libMsg::endl;
    libMsg::cout<<"gamme:\t"<<eg<<" absolution difference."<<libMsg::endl;
    libMsg::cout<<"u0:\t"<<eu<<" pixel"<<libMsg::endl;
    libMsg::cout<<"v0:\t"<<ev<<" pixel"<<libMsg::endl;
    Kout = K_ellip;
    return true;
}

bool extractK_real_double(std::vector<matrix<double> > &S,
                          std::vector<matrix<double> > &Ellipse_centers, double tolFun,
                          std::vector<matrix<double> > &CHSlist, libNumerics::matrix<double> &Kout)
{
    return extractK_real<double>(S, Ellipse_centers, tolFun, CHSlist, Kout);
}
