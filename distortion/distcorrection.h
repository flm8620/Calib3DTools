#ifndef DISTCORRECTION_H
#define DISTCORRECTION_H
//libImage
#include "image.h"
#include <vector>

namespace DistortionModule {
bool distortionCorrect_RGB(image_double_RGB in, image_double_RGB &out,
                           std::vector<double> &polynome, int order);

bool distortionCorrect(image_double in, image_double &out, std::vector<double> &polynome,
                       int order);

bool polyEstime(const std::vector<image_char> &list, std::vector<double> &polynome, int order);
}
#endif // DISTCORRECTION_H
