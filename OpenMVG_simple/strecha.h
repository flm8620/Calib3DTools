#ifndef STRECHA_H
#define STRECHA_H
namespace Strecha{
bool findCameraPosition(const std::vector<double> &K, const std::vector<double> &point2D,
                        const std::vector<double> &point3D, std::vector<double> &R_out,
                        std::vector<double> &T_out, std::vector<double> &center_out);
}
#endif // STRECHA_H

