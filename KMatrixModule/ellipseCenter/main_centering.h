#ifndef MAIN_CENTERING_H
#define MAIN_CENTERING_H
#include "image.h"
#include "matrix.h"
bool detectEllipseCenters(const ImageGray<double> &img, ImageRGB<BYTE> &imgFeedback, libNumerics::vector<double> &x, libNumerics::vector<double> &y, libNumerics::vector<double> &r, std::vector<libNumerics::vector<double> > &P, double scale);
#endif // MAIN_CENTERING_H

