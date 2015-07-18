#ifndef DISTCORRECTION_H
#define DISTCORRECTION_H

#include "commondefs.h"
// libImage
#include "image.h"

#include <vector>
#include <utility>

// libConcurrent
#include "simplethreadpool.h"
//#include "qthreadpoolbridge.h"

namespace DistortionModule {
static concurrent::AbstractThreadPool& DEFAULT_THREAD_POOL = concurrent::SimpleThreadPool::DEFAULT;
//static concurrent::AbstractThreadPool& DEFAULT_THREAD_POOL = QThreadpoolBridge::DEFAULT;

bool correct_image_RGB(ImageRGB<double> &in, ImageRGB<double> &out, int spline_order,
                              const Bi<std::vector<double> > &poly_params_inv,
                              concurrent::AbstractThreadPool& thPool =DEFAULT_THREAD_POOL);
bool correct_image(ImageGray<double> &in, ImageGray<double> &out, int spline_order,
                          const Bi<std::vector<double> > &poly_params_inv,
                          concurrent::AbstractThreadPool& thPool =DEFAULT_THREAD_POOL);

typedef std::vector<Vector2D> Line;
typedef std::vector<Line> LineCollection;
bool polyEstime(const std::vector<ImageGray<pixel::BYTE> > &list,
                std::vector<double> &polynome, int order,
                std::vector<LineCollection> &detectedLines);
}
#endif // DISTCORRECTION_H
