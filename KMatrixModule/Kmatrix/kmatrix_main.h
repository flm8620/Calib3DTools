#ifndef KMATRIX_MAIN_H
#define KMATRIX_MAIN_H
#include "matrix.h"
#include <vector>
libNumerics::matrix<double> extractK_real_double(std::vector<libNumerics::matrix<double> > &S,
                                                 std::vector<libNumerics::matrix<double> > &Ellipse_centers,
                                                 double tolFun, libNumerics::matrix<double> &CH0S);
#endif // KMATRIX_MAIN_H
