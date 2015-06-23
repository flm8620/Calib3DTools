#ifndef MAIN_CENTERING_H
#define MAIN_CENTERING_H
#include "image.h"
#include "matrix.h"
void detectEllipseCenters(const ImageGray<double> &img, libNumerics::vector<double> &x, libNumerics::vector<double> &y, libNumerics::vector<double> &r, double scale);
#endif // MAIN_CENTERING_H

