#ifndef KMATRIX_MAIN_H
#define KMATRIX_MAIN_H
#include "matrix.h"
#include <vector>
bool extractK_real_double(std::vector<libNumerics::matrix<double> > &S,
                          std::vector<libNumerics::matrix<double> > &Ellipse_centers, double tolFun,
                          std::vector<libNumerics::matrix<double> > &CHSlist,
                          libNumerics::matrix<double> &Kout);
#endif // KMATRIX_MAIN_H
