#ifndef MAIN_CENTERING_H
#define MAIN_CENTERING_H
#include "image.h"
#include "matrix.h"

bool detectEllipseCenters(const ImageGray<double> &img, ImageRGB<pixel::BYTE> &imgFeedback,
                          libNumerics::vector<double> &x, libNumerics::vector<double> &y,
                          libNumerics::vector<double> &r,
                          std::vector<libNumerics::vector<double> > &P, double scale);
bool detectEllipseCenters_noRefine(const ImageGray<double> &img, ImageRGB<pixel::BYTE> &imgFeedback,
                                   libNumerics::vector<double> &x, libNumerics::vector<double> &y,
                                   libNumerics::vector<double> &r);
#endif // MAIN_CENTERING_H
