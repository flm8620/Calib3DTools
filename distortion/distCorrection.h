#ifndef DISTCORRECTION_H
#define DISTCORRECTION_H

#include "../commondefs.h"
// libImage
#include "image.h"

#include <vector>
#include <utility>
#include <QImage>
#include <QList>
namespace DistortionModule {
bool distortionCorrect_RGB(ImageRGB<double> &in, ImageRGB<double> &out, const Bi<std::vector<double> > &polynome);

bool distortionCorrect(ImageGray<double> &in, ImageGray<double> &out, const Bi<std::vector<double> > &polynome);

bool polyEstime(const QList<QImage> &list, std::vector<double> &polynome, int order,
                std::vector<std::vector<std::vector<std::pair<double, double> > > > &detectedLines);
}
#endif // DISTCORRECTION_H
