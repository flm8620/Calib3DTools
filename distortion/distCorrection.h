#ifndef DISTCORRECTION_H
#define DISTCORRECTION_H
// libImage
#include "image.h"

#include <vector>
#include <utility>
namespace DistortionModule {
bool distortionCorrect_RGB(ImageRGB<double> &in, ImageRGB<double> &out,
                           std::vector<double> &polynome, int order);

bool distortionCorrect(ImageGray<double> &in, ImageGray<double> &out, std::vector<double> &polynome,
                       int order);

bool polyEstime(const std::vector<ImageGray<BYTE> > &list, std::vector<double> &polynome, int order,
                std::vector<std::vector<std::vector<std::pair<double, double> > > > &detectedLines);
}
#endif // DISTCORRECTION_H
