#ifndef CORRECTION_H
#define CORRECTION_H

#include "commondefs.h"
#include <vector>

Vector2D undistortPixel(const Bi<std::vector<double> > &params, const Vector2D& distort);
#endif
