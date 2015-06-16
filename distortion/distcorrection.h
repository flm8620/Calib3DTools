#ifndef DISTCORRECTION_H
#define DISTCORRECTION_H

#include <vector>

struct image_double_s;
typedef image_double_s *image_double;
struct image_double_RGB_s;
typedef image_double_RGB_s *image_double_RGB;
namespace DistortionModule {
bool distortionCorrect_RGB(image_double_RGB in, image_double_RGB &out,
                           std::vector<double> &polynome, int order);

bool distortionCorrect(image_double in, image_double &out, std::vector<double> &polynome,
                       int order);
}
#endif // DISTCORRECTION_H
