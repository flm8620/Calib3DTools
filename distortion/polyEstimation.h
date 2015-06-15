#ifndef POLYESTIMATION
#define POLYESTIMATION

#endif // POLYESTIMATION

#include <vector>

struct image_double_s;
typedef image_double_s* image_double;
namespace PolyEstimation{
bool polyEstime(const std::vector<image_double>& list, std::vector<double>& polynome, int order);
}
