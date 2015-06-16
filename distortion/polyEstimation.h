#ifndef POLYESTIMATION
#define POLYESTIMATION

#endif // POLYESTIMATION

#include <vector>

struct image_char_s;
typedef image_char_s* image_char;
namespace DistortionModule{
bool polyEstime(const std::vector<image_char> &list, std::vector<double>& polynome, int order);
}
