#ifndef KMATRIXSOLVE_H
#define KMATRIXSOLVE_H

#endif // KMATRIXSOLVE_H
#include <vector>
#include <QImage>
namespace KMatrixSolve {
bool KMatrixSolver(std::vector<QImage> &imageList, std::vector<QImage> &feedbackList, double &alpha,
                   double &beta, double &u0, double &v0, double &gamma, double seperation,
                   double radius);
}
