#ifndef JAC_EQS_H
#define JAC_EQS_H
#include <math.h>
#include <stdio.h>
#include "matrix.h"
template<typename T>
T Power(T base, T pow)
{
    return std::pow(base, pow);
}

template<typename T>
T Sqrt(T exp)
{
    return std::sqrt(exp);
}

template<typename T>
void jac_inv_maple_noOptimize(const libNumerics::vector<T> &P, const libNumerics::matrix<T> &s, T u, T v, T &dEdh1, T &dEdh2,
                              T &dEdh3, T &dEdh4, T &dEdh5, T &dEdh6, T &dEdh7, T &dEdh8, T &dEdh9)
{
    T h1 = P[0], h2 = P[1], h3 = P[2];
    T h4 = P[3], h5 = P[4], h6 = P[5];
    T h7 = P[6], h8 = P[7], h9 = P[8];
    T a = s(0, 2), b = s(1, 2), f = s(2, 2);
    dEdh1
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u,
                  0.2e1)
              + pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                      * h1 + h5
                      * h4)
                    / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                       * h4 * h2 * h8
                       * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                       * h1 * h1 * f * h8
                       * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                       - 0.1e1 * f * h7 * h7
                       * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                       * h1 * h1 * h8 * h8
                       + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                       * h2 * h2 + 0.2e1
                       * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                       * h8 * h8 * b * h4
                       - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                       + 0.2e1 * h2 * h1 * h5
                       * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                       + 0.2e1 * h2 * h7 * a
                       * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                       * h8 * b - 0.2e1 * h4
                       * h7 * b * h2 * h8 * a)
                    * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                       + (h1 * a + h4 * b + h7 * f) * h9)
                    + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                    / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                       * h4 * h2 * h8
                       * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                       * h1 * h1 * f * h8
                       * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                       - 0.1e1 * f * h7 * h7
                       * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                       * h1 * h1 * h8 * h8
                       + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                       * h2 * h2 + 0.2e1
                       * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                       * h8 * h8 * b * h4
                       - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                       + 0.2e1 * h2 * h1 * h5
                       * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                       + 0.2e1 * h2 * h7 * a
                       * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                       * h8 * b - 0.2e1 * h4
                       * h7 * b * h2 * h8 * a)
                    * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                       + (h2 * a + h5 * b + h8 * f) * h9)
                    - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * (-(0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.4e1 * h1 * h5 * h8 * b - 0.2e1 * h7 * a * h5 * h5 + 0.2e1 * h2 * h5 * h4
                   - 0.2e1 * h1
                   * f * h8 * h8 + 0.2e1 * a * a * h1 * h8 * h8 - 0.2e1 * h1 * h5 * h5 + 0.2e1
                   * h5 * h4 * a * h8
                   + 0.2e1 * a * h8 * h8 * b * h4 - 0.2e1 * h7 * a * a * h2 * h8 + 0.2e1 * h2 * h5
                   * h7 * b
                   + 0.2e1 * h2 * b * h4 * h8 + 0.2e1 * h2 * f * h7 * h8 - 0.2e1 * h7 * a * h5
                   * h8 * b)
                + (0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h3 + h9 * a) - (h8 * a + h2)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.4e1 * h1 * h5 * h8 * b - 0.2e1 * h7 * a * h5 * h5 + 0.2e1 * h2 * h5 * h4
                   - 0.2e1 * h1
                   * f * h8 * h8 + 0.2e1 * a * a * h1 * h8 * h8 - 0.2e1 * h1 * h5 * h5 + 0.2e1
                   * h5 * h4 * a * h8
                   + 0.2e1 * a * h8 * h8 * b * h4 - 0.2e1 * h7 * a * a * h2 * h8 + 0.2e1 * h2 * h5
                   * h7 * b
                   + 0.2e1 * h2 * b * h4 * h8 + 0.2e1 * h2 * f * h7 * h8 - 0.2e1 * h7 * a * h5
                   * h8 * b)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(h8 * a + h2)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.4e1 * h1 * h5 * h8 * b - 0.2e1 * h7 * a * h5 * h5 + 0.2e1 * h2 * h5 * h4
                   - 0.2e1 * h1
                   * f * h8 * h8 + 0.2e1 * a * a * h1 * h8 * h8 - 0.2e1 * h1 * h5 * h5 + 0.2e1
                   * h5 * h4 * a * h8
                   + 0.2e1 * a * h8 * h8 * b * h4 - 0.2e1 * h7 * a * a * h2 * h8 + 0.2e1 * h2 * h5
                   * h7 * b
                   + 0.2e1 * h2 * b * h4 * h8 + 0.2e1 * h2 * f * h7 * h8 - 0.2e1 * h7 * a * h5
                   * h8 * b)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h3 + h9 * a) + (0.2e1 * h7 * a + 0.2e1 * h1)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.4e1 * h1 * h5 * h8 * b - 0.2e1 * h7 * a * h5 * h5 + 0.2e1 * h2 * h5 * h4
                   - 0.2e1 * h1
                   * f * h8 * h8 + 0.2e1 * a * a * h1 * h8 * h8 - 0.2e1 * h1 * h5 * h5 + 0.2e1
                   * h5 * h4 * a * h8
                   + 0.2e1 * a * h8 * h8 * b * h4 - 0.2e1 * h7 * a * a * h2 * h8 + 0.2e1 * h2 * h5
                   * h7 * b
                   + 0.2e1 * h2 * b * h4 * h8 + 0.2e1 * h2 * f * h7 * h8 - 0.2e1 * h7 * a * h5
                   * h8 * b))) / 0.2e1;
    dEdh2
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u,
                  0.2e1)
              + pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                      * h1 + h5
                      * h4)
                    / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                       * h4 * h2 * h8
                       * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                       * h1 * h1 * f * h8
                       * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                       - 0.1e1 * f * h7 * h7
                       * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                       * h1 * h1 * h8 * h8
                       + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                       * h2 * h2 + 0.2e1
                       * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                       * h8 * h8 * b * h4
                       - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                       + 0.2e1 * h2 * h1 * h5
                       * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                       + 0.2e1 * h2 * h7 * a
                       * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                       * h8 * b - 0.2e1 * h4
                       * h7 * b * h2 * h8 * a)
                    * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                       + (h1 * a + h4 * b + h7 * f) * h9)
                    + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                    / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                       * h4 * h2 * h8
                       * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                       * h1 * h1 * f * h8
                       * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                       - 0.1e1 * f * h7 * h7
                       * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                       * h1 * h1 * h8 * h8
                       + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                       * h2 * h2 + 0.2e1
                       * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                       * h8 * h8 * b * h4
                       - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                       + 0.2e1 * h2 * h1 * h5
                       * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                       + 0.2e1 * h2 * h7 * a
                       * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                       * h8 * b - 0.2e1 * h4
                       * h7 * b * h2 * h8 * a)
                    * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                       + (h2 * a + h5 * b + h8 * f) * h9)
                    - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * ((0.2e1 * h8 * a + 0.2e1 * h2)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h4 * h4 * h8 * a - 0.4e1 * h4 * h7 * b * h2 + 0.2e1 * h1 * h5 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h2 + 0.2e1 * h2 * h7 * h7 * a * a - 0.2e1 * h4 * h4 * h2 - 0.2e1
                   * h1 * h7 * a * a
                   * h8 + 0.2e1 * h1 * h5 * h7 * b + 0.2e1 * h1 * b * h4 * h8 + 0.2e1 * h1 * f
                   * h7 * h8 + 0.2e1
                   * h7 * a * h5 * h4 + 0.2e1 * h7 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h8 * a)
                - (h7 * a + h1)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h4 * h4 * h8 * a - 0.4e1 * h4 * h7 * b * h2 + 0.2e1 * h1 * h5 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h2 + 0.2e1 * h2 * h7 * h7 * a * a - 0.2e1 * h4 * h4 * h2 - 0.2e1
                   * h1 * h7 * a * a
                   * h8 + 0.2e1 * h1 * h5 * h7 * b + 0.2e1 * h1 * b * h4 * h8 + 0.2e1 * h1 * f
                   * h7 * h8 + 0.2e1
                   * h7 * a * h5 * h4 + 0.2e1 * h7 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h8 * a)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h3 + h9 * a)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(h7 * a + h1)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h4 * h4 * h8 * a - 0.4e1 * h4 * h7 * b * h2 + 0.2e1 * h1 * h5 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h2 + 0.2e1 * h2 * h7 * h7 * a * a - 0.2e1 * h4 * h4 * h2 - 0.2e1
                   * h1 * h7 * a * a
                   * h8 + 0.2e1 * h1 * h5 * h7 * b + 0.2e1 * h1 * b * h4 * h8 + 0.2e1 * h1 * f
                   * h7 * h8 + 0.2e1
                   * h7 * a * h5 * h4 + 0.2e1 * h7 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h8 * a)
                - (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h4 * h4 * h8 * a - 0.4e1 * h4 * h7 * b * h2 + 0.2e1 * h1 * h5 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h2 + 0.2e1 * h2 * h7 * h7 * a * a - 0.2e1 * h4 * h4 * h2 - 0.2e1
                   * h1 * h7 * a * a
                   * h8 + 0.2e1 * h1 * h5 * h7 * b + 0.2e1 * h1 * b * h4 * h8 + 0.2e1 * h1 * f
                   * h7 * h8 + 0.2e1
                   * h7 * a * h5 * h4 + 0.2e1 * h7 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h8 * a)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h3 + h9 * a))) / 0.2e1;
    dEdh3
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u,
                  0.2e1)
              + pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                      * h1 + h5
                      * h4)
                    / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                       * h4 * h2 * h8
                       * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                       * h1 * h1 * f * h8
                       * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                       - 0.1e1 * f * h7 * h7
                       * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                       * h1 * h1 * h8 * h8
                       + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                       * h2 * h2 + 0.2e1
                       * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                       * h8 * h8 * b * h4
                       - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                       + 0.2e1 * h2 * h1 * h5
                       * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                       + 0.2e1 * h2 * h7 * a
                       * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                       * h8 * b - 0.2e1 * h4
                       * h7 * b * h2 * h8 * a)
                    * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                       + (h1 * a + h4 * b + h7 * f) * h9)
                    + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                    / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                       * h4 * h2 * h8
                       * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                       * h1 * h1 * f * h8
                       * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                       - 0.1e1 * f * h7 * h7
                       * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                       * h1 * h1 * h8 * h8
                       + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                       * h2 * h2 + 0.2e1
                       * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                       * h8 * h8 * b * h4
                       - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                       + 0.2e1 * h2 * h1 * h5
                       * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                       + 0.2e1 * h2 * h7 * a
                       * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                       * h8 * b - 0.2e1 * h4
                       * h7 * b * h2 * h8 * a)
                    * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                       + (h2 * a + h5 * b + h8 * f) * h9)
                    - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h1 + h7 * a)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h2 + h8 * a)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h1 + h7 * a)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h2 + h8 * a))) / 0.2e1;
    dEdh4
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u, 0.2e1)
              +pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                     * h1 + h5 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                      + (h1 * a + h4 * b + h7 * f) * h9)
                   + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                      + (h2 * a + h5 * b + h8 * f) * h9)
                   - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * (-(0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                    * h4 * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4
                    - 0.1e1 * h1 * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                    - 0.1e1 * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                    * a * h1 * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                    * h4 * h2 * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                    * h1 * h8 * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5
                    * h8 + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                    * h8 + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                    * h5 * h8 * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.4e1 * h4 * h2 * h8 * a - 0.2e1 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1
                   * h5 - 0.2e1 * h4
                   * f * h8 * h8 + 0.2e1 * b * b * h4 * h8 * h8 - 0.2e1 * h4 * h2 * h2
                   + 0.2e1 * h5 * a * h1 * h8
                   + 0.2e1 * h5 * f * h7 * h8 + 0.2e1 * a * h1 * h8 * h8 * b - 0.2e1 * h7
                   * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * b * h8 + 0.2e1 * h2 * h7 * a * h5 - 0.2e1 * h7 * b
                   * h2 * h8 * a)
                + (0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5
                   * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                   * h4 * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                   * h1 * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                   - 0.1e1 * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                   * a * h1 * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                   * h4 * h2 * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                   * h1 * h8 * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                   * h8 + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                   * h5 * h8 * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h6 + h9 * b) - (h8 * b + h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                   * h4 * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                   * h1 * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                   - 0.1e1 * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                   * a * h1 * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                   * h4 * h2 * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                   * h1 * h8 * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                   * h8 + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                   * h5 * h8 * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8
                   + h2 * h1 + h5 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                    * h4 * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4
                    - 0.1e1 * h1 * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                    - 0.1e1 * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                    * a * h1 * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                    * h4 * h2 * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                    * h1 * h8 * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5
                    * h8 + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                    * h8 + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                    * h5 * h8 * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.4e1 * h4 * h2 * h8 * a - 0.2e1 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1
                   * h5 - 0.2e1 * h4
                   * f * h8 * h8 + 0.2e1 * b * b * h4 * h8 * h8 - 0.2e1 * h4 * h2 * h2
                   + 0.2e1 * h5 * a * h1 * h8
                   + 0.2e1 * h5 * f * h7 * h8 + 0.2e1 * a * h1 * h8 * h8 * b - 0.2e1 * h7
                   * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * b * h8 + 0.2e1 * h2 * h7 * a * h5 - 0.2e1 * h7 * b
                   * h2 * h8 * a)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(h8 * b + h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.4e1 * h4 * h2 * h8 * a - 0.2e1 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5
                   - 0.2e1 * h4
                   * f * h8 * h8 + 0.2e1 * b * b * h4 * h8 * h8 - 0.2e1 * h4 * h2 * h2 + 0.2e1
                   * h5 * a * h1 * h8
                   + 0.2e1 * h5 * f * h7 * h8 + 0.2e1 * a * h1 * h8 * h8 * b - 0.2e1 * h7 * b * b
                   * h5 * h8
                   + 0.2e1 * h2 * h1 * b * h8 + 0.2e1 * h2 * h7 * a * h5 - 0.2e1 * h7 * b * h2
                   * h8 * a)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h6 + h9 * b) + (0.2e1 * h7 * b + 0.2e1 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.4e1 * h4 * h2 * h8 * a - 0.2e1 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5
                   - 0.2e1 * h4
                   * f * h8 * h8 + 0.2e1 * b * b * h4 * h8 * h8 - 0.2e1 * h4 * h2 * h2 + 0.2e1
                   * h5 * a * h1 * h8
                   + 0.2e1 * h5 * f * h7 * h8 + 0.2e1 * a * h1 * h8 * h8 * b - 0.2e1 * h7 * b * b
                   * h5 * h8
                   + 0.2e1 * h2 * h1 * b * h8 + 0.2e1 * h2 * h7 * a * h5 - 0.2e1 * h7 * b * h2
                   * h8 * a))) / 0.2e1;
    dEdh5
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u, 0.2e1)
              +pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                     * h1 + h5 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                      + (h1 * a + h4 * b + h7 * f) * h9)
                   + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                      + (h2 * a + h5 * b + h8 * f) * h9)
                   - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * ((0.2e1 * h8 * b + 0.2e1 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h1 * h1 * h8 * b - 0.4e1 * h1 * h7 * a * h5 + 0.2e1 * h2 * h1 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h5 + 0.2e1 * h5 * h7 * h7 * b * b - 0.2e1 * h1 * h1 * h5 + 0.2e1
                   * h4 * a * h1
                   * h8 + 0.2e1 * h4 * f * h7 * h8 - 0.2e1 * h4 * h7 * b * b * h8 + 0.2e1 * h2
                   * h1 * h7 * b
                   + 0.2e1 * h2 * h7 * a * h4 + 0.2e1 * h2 * h7 * h7 * a * b - 0.2e1 * h1 * h7 * a
                   * h8 * b)
                - (h7 * b + h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h1 * h1 * h8 * b - 0.4e1 * h1 * h7 * a * h5 + 0.2e1 * h2 * h1 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h5 + 0.2e1 * h5 * h7 * h7 * b * b - 0.2e1 * h1 * h1 * h5 + 0.2e1
                   * h4 * a * h1
                   * h8 + 0.2e1 * h4 * f * h7 * h8 - 0.2e1 * h4 * h7 * b * b * h8 + 0.2e1 * h2
                   * h1 * h7 * b
                   + 0.2e1 * h2 * h7 * a * h4 + 0.2e1 * h2 * h7 * h7 * a * b - 0.2e1 * h1 * h7 * a
                   * h8 * b)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h6 + h9 * b)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(h7 * b + h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h1 * h1 * h8 * b - 0.4e1 * h1 * h7 * a * h5 + 0.2e1 * h2 * h1 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h5 + 0.2e1 * h5 * h7 * h7 * b * b - 0.2e1 * h1 * h1 * h5 + 0.2e1
                   * h4 * a * h1
                   * h8 + 0.2e1 * h4 * f * h7 * h8 - 0.2e1 * h4 * h7 * b * b * h8 + 0.2e1 * h2
                   * h1 * h7 * b
                   + 0.2e1 * h2 * h7 * a * h4 + 0.2e1 * h2 * h7 * h7 * a * b - 0.2e1 * h1 * h7 * a
                   * h8 * b)
                - (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h1 * h1 * h8 * b - 0.4e1 * h1 * h7 * a * h5 + 0.2e1 * h2 * h1 * h4
                   - 0.2e1 * f
                   * h7 * h7 * h5 + 0.2e1 * h5 * h7 * h7 * b * b - 0.2e1 * h1 * h1 * h5 + 0.2e1
                   * h4 * a * h1
                   * h8 + 0.2e1 * h4 * f * h7 * h8 - 0.2e1 * h4 * h7 * b * b * h8 + 0.2e1 * h2
                   * h1 * h7 * b
                   + 0.2e1 * h2 * h7 * a * h4 + 0.2e1 * h2 * h7 * h7 * a * b - 0.2e1 * h1 * h7 * a
                   * h8 * b)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h6 + h9 * b))) / 0.2e1;
    dEdh6
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u, 0.2e1)
              +pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                     * h1 + h5 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                      + (h1 * a + h4 * b + h7 * f) * h9)
                   + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                      + (h2 * a + h5 * b + h8 * f) * h9)
                   - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h4 + h7 * b)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h5 + h8 * b)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h4 + h7 * b)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (0.1e1 * h5 + h8 * b))) / 0.2e1;
    dEdh7
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u, 0.2e1)
              +pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                     * h1 + h5 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                      + (h1 * a + h4 * b + h7 * f) * h9)
                   + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                      + (h2 * a + h5 * b + h8 * f) * h9)
                   - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * (-(0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                    * h4 * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4
                    - 0.1e1 * h1 * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                    - 0.1e1 * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                    * a * h1 * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                    * h4 * h2 * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                    * h1 * h8 * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5
                    * h8 + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                    * h8 + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                    * h5 * h8 * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h1 * a * h5 * h5 - 0.2e1 * h4 * b * h2 * h2 - 0.2e1 * f * h7
                   * h2 * h2 - 0.2e1 * f
                   * h7 * h5 * h5 + 0.2e1 * h2 * h2 * h7 * a * a + 0.2e1 * h5 * h5 * h7
                   * b * b + 0.2e1 * h5 * h4
                   * f * h8 - 0.2e1 * h1 * a * a * h2 * h8 - 0.2e1 * h4 * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * h5
                   * b + 0.2e1 * h2 * h1 * f * h8 + 0.2e1 * h2 * a * h5 * h4 + 0.4e1 * h2
                   * h7 * a * h5 * b
                   - 0.2e1 * h1 * a * h5 * h8 * b - 0.2e1 * h4 * b * h2 * h8 * a)
                + (0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5
                   * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                   * h4 * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                   * h1 * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                   - 0.1e1 * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                   * a * h1 * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                   * h4 * h2 * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                   * h1 * h8 * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                   * h8 + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                   * h5 * h8 * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (a * h3 + b * h6 + f * h9)
                - (h2 * a + h5 * b + h8 * f)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                   * h4 * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                   * h1 * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                   - 0.1e1 * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                   * a * h1 * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                   * h4 * h2 * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                   * h1 * h8 * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                   * h8 + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                   * h5 * h8 * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8
                   + h2 * h1 + h5 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1
                    * h4 * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4
                    - 0.1e1 * h1 * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                    - 0.1e1 * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                    * a * h1 * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                    * h4 * h2 * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                    * h1 * h8 * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5
                    * h8 + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                    * h8 + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                    * h5 * h8 * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h1 * a * h5 * h5 - 0.2e1 * h4 * b * h2 * h2 - 0.2e1 * f * h7
                   * h2 * h2 - 0.2e1 * f
                   * h7 * h5 * h5 + 0.2e1 * h2 * h2 * h7 * a * a + 0.2e1 * h5 * h5 * h7
                   * b * b + 0.2e1 * h5 * h4
                   * f * h8 - 0.2e1 * h1 * a * a * h2 * h8 - 0.2e1 * h4 * b * b * h5 * h8
                   + 0.2e1 * h2 * h1 * h5
                   * b + 0.2e1 * h2 * h1 * f * h8 + 0.2e1 * h2 * a * h5 * h4 + 0.4e1 * h2
                   * h7 * a * h5 * b
                   - 0.2e1 * h1 * a * h5 * h8 * b - 0.2e1 * h4 * b * h2 * h8 * a)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(h2 * a + h5 * b + h8 * f)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h1 * a * h5 * h5 - 0.2e1 * h4 * b * h2 * h2 - 0.2e1 * f * h7 * h2 * h2
                   - 0.2e1 * f
                   * h7 * h5 * h5 + 0.2e1 * h2 * h2 * h7 * a * a + 0.2e1 * h5 * h5 * h7 * b * b
                   + 0.2e1 * h5 * h4
                   * f * h8 - 0.2e1 * h1 * a * a * h2 * h8 - 0.2e1 * h4 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * b + 0.2e1 * h2 * h1 * f * h8 + 0.2e1 * h2 * a * h5 * h4 + 0.4e1 * h2 * h7 * a
                   * h5 * b
                   - 0.2e1 * h1 * a * h5 * h8 * b - 0.2e1 * h4 * b * h2 * h8 * a)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (a * h3 + b * h6 + f * h9)
                + (0.2e1 * h1 * a + 0.2e1 * h4 * b + 0.2e1 * h7 * f)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h1 * a * h5 * h5 - 0.2e1 * h4 * b * h2 * h2 - 0.2e1 * f * h7 * h2 * h2
                   - 0.2e1 * f
                   * h7 * h5 * h5 + 0.2e1 * h2 * h2 * h7 * a * a + 0.2e1 * h5 * h5 * h7 * b * b
                   + 0.2e1 * h5 * h4
                   * f * h8 - 0.2e1 * h1 * a * a * h2 * h8 - 0.2e1 * h4 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * b + 0.2e1 * h2 * h1 * f * h8 + 0.2e1 * h2 * a * h5 * h4 + 0.4e1 * h2 * h7 * a
                   * h5 * b
                   - 0.2e1 * h1 * a * h5 * h8 * b - 0.2e1 * h4 * b * h2 * h8 * a))) / 0.2e1;
    dEdh8
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u, 0.2e1)
              +pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                     * h1 + h5 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                      + (h1 * a + h4 * b + h7 * f) * h9)
                   + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                      + (h2 * a + h5 * b + h8 * f) * h9)
                   - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * ((0.2e1 * h2 * a + 0.2e1 * h5 * b + 0.2e1 * h8 * f)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h1 * h1 * h5 * b - 0.2e1 * h4 * h4 * h2 * a - 0.2e1 * h1 * h1 * f * h8
                   - 0.2e1
                   * h4 * h4 * f * h8 + 0.2e1 * a * a * h1 * h1 * h8 + 0.2e1 * b * b * h4 * h4
                   * h8 + 0.2e1 * h5
                   * h4 * a * h1 + 0.2e1 * h5 * h4 * f * h7 + 0.4e1 * a * h1 * h8 * b * h4 - 0.2e1
                   * h1 * h7 * a
                   * a * h2 - 0.2e1 * h4 * h7 * b * b * h5 + 0.2e1 * h2 * h1 * b * h4 + 0.2e1 * h2
                   * h1 * f * h7
                   - 0.2e1 * h1 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h2 * a)
                - (h1 * a + h4 * b + h7 * f)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h1 * h1 * h5 * b - 0.2e1 * h4 * h4 * h2 * a - 0.2e1 * h1 * h1 * f * h8
                   - 0.2e1
                   * h4 * h4 * f * h8 + 0.2e1 * a * a * h1 * h1 * h8 + 0.2e1 * b * b * h4 * h4
                   * h8 + 0.2e1 * h5
                   * h4 * a * h1 + 0.2e1 * h5 * h4 * f * h7 + 0.4e1 * a * h1 * h8 * b * h4 - 0.2e1
                   * h1 * h7 * a
                   * a * h2 - 0.2e1 * h4 * h7 * b * b * h5 + 0.2e1 * h2 * h1 * b * h4 + 0.2e1 * h2
                   * h1 * f * h7
                   - 0.2e1 * h1 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h2 * a)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (a * h3 + b * h6 + f * h9)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(h1 * a + h4 * b + h7 * f)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                * pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2
                      * h8 * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1
                      * h1 * h1 * f
                      * h8 * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2
                      - 0.1e1 * f * h7
                      * h7 * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a
                      * a * h1 * h1 * h8
                      * h8 + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4
                      * h4 * h2 * h2
                      + 0.2e1 * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a
                      * h1 * h8 * h8 * b
                      * h4 - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1
                      * h5 * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7
                      * h8 + 0.2e1 * h2
                      * h7 * a * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a
                      * h5 * h8 * b
                      - 0.2e1 * h4 * h7 * b * h2 * h8 * a,
                      -0.2e1)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                * (-0.2e1 * h1 * h1 * h5 * b - 0.2e1 * h4 * h4 * h2 * a - 0.2e1 * h1 * h1 * f * h8
                   - 0.2e1
                   * h4 * h4 * f * h8 + 0.2e1 * a * a * h1 * h1 * h8 + 0.2e1 * b * b * h4 * h4
                   * h8 + 0.2e1 * h5
                   * h4 * a * h1 + 0.2e1 * h5 * h4 * f * h7 + 0.4e1 * a * h1 * h8 * b * h4 - 0.2e1
                   * h1 * h7 * a
                   * a * h2 - 0.2e1 * h4 * h7 * b * b * h5 + 0.2e1 * h2 * h1 * b * h4 + 0.2e1 * h2
                   * h1 * f * h7
                   - 0.2e1 * h1 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h2 * a)
                - (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                *
                pow(-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                    * h4 * h2 * h8
                    * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                    * h1 * f * h8
                    * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                    * f * h7 * h7
                    * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                    * h1 * h8 * h8
                    + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                    * h2 + 0.2e1
                    * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                    * h8 * b * h4
                    - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                    + 0.2e1 * h2 * h1 * h5
                    * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                    + 0.2e1 * h2 * h7 * a
                    * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                    * b - 0.2e1 * h4
                    * h7 * b * h2 * h8 * a,
                    -0.2e1)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                * (-0.2e1 * h1 * h1 * h5 * b - 0.2e1 * h4 * h4 * h2 * a - 0.2e1 * h1 * h1 * f * h8
                   - 0.2e1
                   * h4 * h4 * f * h8 + 0.2e1 * a * a * h1 * h1 * h8 + 0.2e1 * b * b * h4 * h4
                   * h8 + 0.2e1 * h5
                   * h4 * a * h1 + 0.2e1 * h5 * h4 * f * h7 + 0.4e1 * a * h1 * h8 * b * h4 - 0.2e1
                   * h1 * h7 * a
                   * a * h2 - 0.2e1 * h4 * h7 * b * b * h5 + 0.2e1 * h2 * h1 * b * h4 + 0.2e1 * h2
                   * h1 * f * h7
                   - 0.2e1 * h1 * h7 * a * h5 * b - 0.2e1 * h4 * h7 * b * h2 * a)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (a * h3 + b * h6 + f * h9))) / 0.2e1;
    dEdh9
        = pow(pow((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                     + (h1 * a + h4 * b + h7 * f) * h9)
                  - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                     + h5 * h4)
                  / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                     * h4 * h2 * h8
                     * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                     * h1 * f * h8
                     * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                     * f * h7 * h7
                     * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                     * h1 * h1 * h8 * h8
                     + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                     * h2 * h2 + 0.2e1
                     * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                     * h8 * b * h4
                     - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                     + 0.2e1 * h2 * h1 * h5
                     * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                     + 0.2e1 * h2 * h7 * a
                     * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                     * b - 0.2e1 * h4
                     * h7 * b * h2 * h8 * a)
                  * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                     + (h2 * a + h5 * b + h8 * f) * h9)
                  - u, 0.2e1)
              +pow(-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2
                     * h1 + h5 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                      + (h1 * a + h4 * b + h7 * f) * h9)
                   + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                   / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                      * h4 * h2 * h8
                      * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                      * h1 * f * h8
                      * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                      * f * h7 * h7
                      * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a
                      * h1 * h1 * h8 * h8
                      + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4
                      * h2 * h2 + 0.2e1
                      * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1
                      * h8 * h8 * b * h4
                      - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8
                      + 0.2e1 * h2 * h1 * h5
                      * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                      + 0.2e1 * h2 * h7 * a
                      * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5
                      * h8 * b - 0.2e1 * h4
                      * h7 * b * h2 * h8 * a)
                   * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                      + (h2 * a + h5 * b + h8 * f) * h9)
                   - v, 0.2e1),
              -0.1e1 / 0.2e1)
          * (0.2e1
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - u)
             * ((0.2e1 * h2 * h8 * a + 0.2e1 * h5 * h8 * b + f * h8 * h8 + h2 * h2 + h5 * h5)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (h1 * a + h4 * b + h7 * f)
                - (a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                   + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (h2 * a + h5 * b + h8 * f)) + 0.2e1
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                   + (h1 * a + h4 * b + h7 * f) * h9)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a)
                * ((0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6
                   + (h2 * a + h5 * b + h8 * f) * h9)
                - v)
             * (-(a * h1 * h8 + h2 * h7 * a + b * h4 * h8 + h5 * h7 * b + f * h7 * h8 + h2 * h1
                  + h5 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (h1 * a + h4 * b + h7 * f)
                + (0.2e1 * h1 * h7 * a + 0.2e1 * h4 * h7 * b + f * h7 * h7 + h1 * h1 + h4 * h4)
                / (-0.2e1 * h1 * h1 * h5 * h8 * b - 0.2e1 * h1 * h7 * a * h5 * h5 - 0.2e1 * h4
                   * h4 * h2 * h8
                   * a - 0.2e1 * h4 * h7 * b * h2 * h2 + 0.2e1 * h2 * h1 * h5 * h4 - 0.1e1 * h1
                   * h1 * f * h8
                   * h8 - 0.1e1 * h4 * h4 * f * h8 * h8 - 0.1e1 * f * h7 * h7 * h2 * h2 - 0.1e1
                   * f * h7 * h7
                   * h5 * h5 + h2 * h2 * h7 * h7 * a * a + h5 * h5 * h7 * h7 * b * b + a * a * h1
                   * h1 * h8 * h8
                   + b * b * h4 * h4 * h8 * h8 - 0.1e1 * h1 * h1 * h5 * h5 - 0.1e1 * h4 * h4 * h2
                   * h2 + 0.2e1
                   * h5 * h4 * a * h1 * h8 + 0.2e1 * h5 * h4 * f * h7 * h8 + 0.2e1 * a * h1 * h8
                   * h8 * b * h4
                   - 0.2e1 * h1 * h7 * a * a * h2 * h8 - 0.2e1 * h4 * h7 * b * b * h5 * h8 + 0.2e1
                   * h2 * h1 * h5
                   * h7 * b + 0.2e1 * h2 * h1 * b * h4 * h8 + 0.2e1 * h2 * h1 * f * h7 * h8
                   + 0.2e1 * h2 * h7 * a
                   * h5 * h4 + 0.2e1 * h2 * h7 * h7 * a * h5 * b - 0.2e1 * h1 * h7 * a * h5 * h8
                   * b - 0.2e1 * h4
                   * h7 * b * h2 * h8 * a) * (h2 * a + h5 * b + h8 * f))) / 0.2e1;
}

template<typename T>
void jac_inv_maple(const libNumerics::vector<T> &P, const libNumerics::matrix<T> &s, T u, T v, T &dEdh1, T &dEdh2, T &dEdh3,
                   T &dEdh4, T &dEdh5, T &dEdh6, T &dEdh7, T &dEdh8, T &dEdh9)
{
    T h1 = P[0], h2 = P[1], h3 = P[2];
    T h4 = P[3], h5 = P[4], h6 = P[5];
    T h7 = P[6], h8 = P[7], h9 = P[8];
    T a = s(0, 2), b = s(1, 2), f = s(2, 2);
    {// h1
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t11 = 0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10;
        double t12 = h1 * h1;
        double t17 = h7 * h7;
        double t20 = h4 * h4;
        double t27 = b * b;
        double t32 = a * a;
        double t37 = b * h1;
        double t38 = h2 * h4;
        double t42 = h2 * h5;
        double t46 = f * h1;
        double t48 = h2 * h7 * h8;
        double t52 = h5 * h7;
        double t53 = t52 * h8;
        double t56 = t32 * h1;
        double t59 = -0.1e1 * f * t12 * t7 - 0.1e1 * f * t9 * t17 - 0.1e1 * f * t20 * t7 - 0.1e1
                     * f * t10 * t17 + t27 * t20 * t7 + t27 * t10 * t17 + t32 * t9 * t17 + t32
                     * t12 * t7
                     + 0.2e1 * t37 * t38 * h8 + 0.2e1 * t37 * t42 * h7 + 0.2e1 * t46 * t48 + 0.2e1
                     * f * h4
                     * t53 - 0.2e1 * t56 * t48;
        double t60 = a * b;
        double t71 = h1 * a;
        double t72 = h4 * h5;
        double t86 = h5 * h8;
        double t90 = h4 * h7;
        double t93 = h1 * h2;
        double t107 = 0.2e1 * t60 * h1 * h4 * t7 + 0.2e1 * t60 * t42 * t17 - 0.2e1 * t27 * h4
                      * t53 + 0.2e1 * t71 * t72 * h8 + 0.2e1 * t1 * t72 * h7 - 0.2e1 * t71 * t10
                      * h7 - 0.2e1
                      * t1 * t20 * h8 - 0.2e1 * b * t12 * t86 - 0.2e1 * b * t9 * t90 + 0.2e1 * t93
                      * t72 - 0.2e1
                      * t60 * h1 * t53 - 0.2e1 * t60 * h2 * t90 * h8 - 0.1e1 * t12 * t10 - 0.1e1
                      * t9 * t20;
        double t108 = t59 + t107;
        double t109 = 0.1e1 / t108;
        double t110 = t11 * t109;
        double t112 = h7 * a;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t123 = (0.1e1 * h1 + t112) * h3 + (0.1e1 * h4 + h7 * b) * h6 + (t71 + t119 + t120)
                      * h9;
        double t130 = t1 * h7 + t4 * h7 + t119 * h8 + t120 * h8 + t71 * h8 + t72 + t93;
        double t131 = t130 * t109;
        double t133 = h8 * a;
        double t143 = (0.1e1 * h2 + t133) * h3 + (0.1e1 * h5 + h8 * b) * h6 + (h8 * f + t1 + t4)
                      * h9;
        double t145 = t110 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t153 = 0.2e1 * t71 * h7 + 0.2e1 * t119 * h7 + f * t17 + t12 + t20;
        double t156 = t153 * t109 * t143 - t131 * t123 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        double t161 = t108 * t108;
        double t162 = 0.1e1 / t161;
        double t177 = b * h2;
        double t184 = h7 * h8;
        double t198 = -0.2e1 * a * t10 * h7 - 0.4e1 * t37 * t86 + 0.2e1 * t38 * h5 - 0.2e1 * t46
                      * t7 + 0.2e1 * t56 * t7 - 0.2e1 * h1 * t10 + 0.2e1 * t177 * h4 * h8 + 0.2e1
                      * t177 * t52
                      + 0.2e1 * f * h2 * t184 - 0.2e1 * t32 * h2 * t184 + 0.2e1 * t60 * h4 * t7
                      + 0.2e1 * a * h4
                      * t86 - 0.2e1 * t60 * t53;
        double t199 = t123 * t198;
        double t203 = 0.1e1 * h3 + a * h9;
        double t206 = (t133 + h2) * t109;
        double t208 = t130 * t162;
        double t209 = t143 * t198;
        dEdh1 = 0.1e1 / t159
                * (t145 * (-t11 * t162 * t199 + t110 * t203 - t206 * t143 + t208 * t209) + t156
                   * (-t206 * t123 + t208 * t199 - t131 * t203 + (0.2e1 * t112 + 0.2e1 * h1)
                      * t109 * t143
                      - t153 * t162 * t209));
    }
    {// h2
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t11 = 0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10;
        double t12 = h1 * h1;
        double t17 = h7 * h7;
        double t20 = h4 * h4;
        double t27 = b * b;
        double t32 = a * a;
        double t41 = h1 * a;
        double t52 = -0.1e1 * f * t12 * t7 - 0.1e1 * f * t9 * t17 - 0.1e1 * f * t20 * t7 - 0.1e1
                     * f * t10 * t17 + t27 * t20 * t7 + t27 * t10 * t17 + t32 * t9 * t17 + t32
                     * t12 * t7
                     - 0.1e1 * t12 * t10 - 0.1e1 * t9 * t20 - 0.2e1 * t41 * t10 * h7 - 0.2e1 * t1
                     * t20 * h8
                     - 0.2e1 * b * t12 * h5 * h8;
        double t54 = h4 * h7;
        double t57 = h1 * h2;
        double t58 = h4 * h5;
        double t61 = b * h1;
        double t66 = h2 * h5;
        double t70 = f * h1;
        double t72 = h2 * h7 * h8;
        double t76 = h5 * h7;
        double t77 = t76 * h8;
        double t80 = t32 * h1;
        double t83 = a * b;
        double t84 = h1 * h4;
        double t104 = t54 * h8;
        double t107 = -0.2e1 * b * t9 * t54 + 0.2e1 * t57 * t58 + 0.2e1 * t61 * h2 * h4 * h8
                      + 0.2e1 * t61 * t66 * h7 + 0.2e1 * t70 * t72 + 0.2e1 * f * h4 * t77 - 0.2e1
                      * t80 * t72
                      + 0.2e1 * t83 * t84 * t7 + 0.2e1 * t83 * t66 * t17 - 0.2e1 * t27 * h4 * t77
                      + 0.2e1 * t41
                      * t58 * h8 + 0.2e1 * t1 * t58 * h7 - 0.2e1 * t83 * h1 * t77 - 0.2e1 * t83
                      * h2 * t104;
        double t108 = t52 + t107;
        double t109 = 0.1e1 / t108;
        double t112 = h7 * a;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t123 = (0.1e1 * h1 + t112) * h3 + (0.1e1 * h4 + h7 * b) * h6 + (t41 + t119 + t120)
                      * h9;
        double t130 = t1 * h7 + t4 * h7 + t119 * h8 + t120 * h8 + t41 * h8 + t57 + t58;
        double t131 = t130 * t109;
        double t133 = h8 * a;
        double t143 = (0.1e1 * h2 + t133) * h3 + (0.1e1 * h5 + h8 * b) * h6 + (h8 * f + t1 + t4)
                      * h9;
        double t145 = t11 * t109 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t153 = 0.2e1 * t41 * h7 + 0.2e1 * t119 * h7 + f * t17 + t12 + t20;
        double t154 = t153 * t109;
        double t156 = -t131 * t123 + t154 * t143 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        double t166 = t108 * t108;
        double t167 = 0.1e1 / t166;
        double t190 = h7 * h8;
        double t203 = -0.2e1 * a * t20 * h8 - 0.4e1 * b * h2 * t54 + 0.2e1 * t84 * h5 - 0.2e1 * f
                      * h2 * t17 + 0.2e1 * t32 * h2 * t17 - 0.2e1 * h2 * t20 + 0.2e1 * t61 * h4
                      * h8 + 0.2e1
                      * t61 * t76 + 0.2e1 * t70 * t190 - 0.2e1 * t80 * t190 + 0.2e1 * t83 * h5
                      * t17 + 0.2e1 * a
                      * h4 * t76 - 0.2e1 * t83 * t104;
        double t204 = t123 * t203;
        double t207 = (t112 + h1) * t109;
        double t209 = t130 * t167;
        double t210 = t143 * t203;
        double t214 = 0.1e1 * h3 + a * h9;
        dEdh2 = 0.1e1 / t159
                * (t145
                   * ((0.2e1 * t133 + 0.2e1 * h2) * t109 * t123 - t11 * t167 * t204 - t207 * t143
                      + t209
                      * t210 - t131 * t214) + t156
                   * (-t153 * t167 * t210 - t207 * t123 + t154 * t214 + t209 * t204));
    }
    {// h3
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t12 = b * h1;
        double t17 = h2 * h5;
        double t23 = h2 * h7 * h8;
        double t28 = h5 * h7 * h8;
        double t31 = a * a;
        double t35 = a * b;
        double t40 = h7 * h7;
        double t44 = b * b;
        double t48 = h1 * a;
        double t49 = h4 * h5;
        double t56 = h1 * h1;
        double t59 = h4 * h4;
        double t65 = 0.2e1 * t12 * h2 * h4 * h8 + 0.2e1 * t12 * t17 * h7 + 0.2e1 * f * h1 * t23
                     + 0.2e1 * f * h4 * t28 - 0.2e1 * t31 * h1 * t23 + 0.2e1 * t35 * h1 * h4 * t7
                     + 0.2e1 * t35
                     * t17 * t40 - 0.2e1 * t44 * h4 * t28 + 0.2e1 * t48 * t49 * h8 + 0.2e1 * t1
                     * t49 * h7
                     - 0.1e1 * t56 * t10 - 0.1e1 * t9 * t59 - 0.2e1 * t35 * h1 * t28;
        double t67 = h4 * h7;
        double t104 = h1 * h2;
        double t107 = -0.2e1 * t35 * h2 * t67 * h8 - 0.1e1 * f * t56 * t7 - 0.1e1 * f * t9 * t40
                      - 0.1e1 * f * t59 * t7 - 0.1e1 * f * t10 * t40 + t44 * t59 * t7 + t44 * t10
                      * t40 + t31
                      * t9 * t40 + t31 * t56 * t7 - 0.2e1 * t48 * t10 * h7 - 0.2e1 * t1 * t59 * h8
                      - 0.2e1 * b
                      * t56 * h5 * h8 - 0.2e1 * b * t9 * t67 + 0.2e1 * t104 * t49;
        double t109 = 0.1e1 / (t65 + t107);
        double t110 = (0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10) * t109;
        double t113 = 0.1e1 * h1 + h7 * a;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t123 = t113 * h3 + (0.1e1 * h4 + h7 * b) * h6 + (t48 + t119 + t120) * h9;
        double t131 = (t1 * h7 + t4 * h7 + t119 * h8 + t120 * h8 + t48 * h8 + t104 + t49) * t109;
        double t134 = 0.1e1 * h2 + h8 * a;
        double t143 = t134 * h3 + (0.1e1 * h5 + h8 * b) * h6 + (h8 * f + t1 + t4) * h9;
        double t145 = t110 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t154 = (0.2e1 * t48 * h7 + 0.2e1 * t119 * h7 + f * t40 + t59 + t56) * t109;
        double t156 = -t131 * t123 + t154 * t143 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        dEdh3 = 0.1e1 / t159
                * (t145 * (t110 * t113 - t131 * t134) + t156 * (-t131 * t113 + t154 * t134));
    }
    {// h4
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t11 = 0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10;
        double t12 = h1 * a;
        double t16 = h4 * h4;
        double t20 = h1 * h1;
        double t22 = h5 * h8;
        double t25 = b * t9;
        double t26 = h4 * h7;
        double t29 = h1 * h2;
        double t30 = h4 * h5;
        double t33 = a * b;
        double t35 = h5 * h7;
        double t36 = h8 * t35;
        double t47 = b * h1;
        double t52 = h2 * h5;
        double t58 = h2 * h7 * h8;
        double t61 = f * h4;
        double t64 = -0.2e1 * t12 * t10 * h7 - 0.2e1 * t1 * t16 * h8 - 0.2e1 * b * t20 * t22
                     - 0.2e1 * t25 * t26 + 0.2e1 * t29 * t30 - 0.2e1 * t33 * h1 * t36 - 0.2e1
                     * t33 * h2 * t26
                     * h8 - 0.1e1 * t20 * t10 - 0.1e1 * t9 * t16 + 0.2e1 * t47 * h2 * h4 * h8
                     + 0.2e1 * t47
                     * t52 * h7 + 0.2e1 * f * h1 * t58 + 0.2e1 * t61 * t36;
        double t65 = a * a;
        double t73 = h7 * h7;
        double t77 = b * b;
        double t78 = t77 * h4;
        double t107 = -0.2e1 * t65 * h1 * t58 + 0.2e1 * t33 * h1 * h4 * t7 + 0.2e1 * t33 * t52
                      * t73 - 0.2e1 * t78 * t36 + 0.2e1 * t12 * t30 * h8 + 0.2e1 * t1 * t30 * h7
                      - 0.1e1 * f
                      * t20 * t7 - 0.1e1 * f * t9 * t73 - 0.1e1 * f * t16 * t7 - 0.1e1 * f * t10
                      * t73 + t77
                      * t16 * t7 + t77 * t10 * t73 + t65 * t9 * t73 + t65 * t20 * t7;
        double t108 = t64 + t107;
        double t109 = 0.1e1 / t108;
        double t110 = t11 * t109;
        double t116 = h7 * b;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t123 = (0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + t116) * h6 + (t12 + t119 + t120)
                      * h9;
        double t130 = t1 * h7 + t4 * h7 + t119 * h8 + t12 * h8 + t120 * h8 + t29 + t30;
        double t131 = t130 * t109;
        double t137 = h8 * b;
        double t143 = (0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + t137) * h6 + (h8 * f + t1 + t4)
                      * h9;
        double t145 = t110 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t153 = 0.2e1 * t12 * h7 + 0.2e1 * t119 * h7 + f * t73 + t20 + t16;
        double t156 = t153 * t109 * t143 - t131 * t123 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        double t161 = t108 * t108;
        double t162 = 0.1e1 / t161;
        double t181 = h7 * h8;
        double t196 = -0.4e1 * t1 * h4 * h8 - 0.2e1 * t25 * h7 + 0.2e1 * t29 * h5 - 0.2e1 * t61
                      * t7 + 0.2e1 * t78 * t7 - 0.2e1 * t9 * h4 + 0.2e1 * t47 * h2 * h8 + 0.2e1
                      * f * h5 * t181
                      + 0.2e1 * t33 * h1 * t7 - 0.2e1 * t77 * h5 * t181 + 0.2e1 * t12 * t22
                      + 0.2e1 * t1 * t35
                      - 0.2e1 * t33 * t58;
        double t197 = t123 * t196;
        double t201 = 0.1e1 * h6 + h9 * b;
        double t204 = (t137 + h5) * t109;
        double t206 = t130 * t162;
        double t207 = t143 * t196;
        dEdh4 = 0.1e1 / t159
                * (t145 * (-t11 * t162 * t197 + t110 * t201 - t204 * t143 + t206 * t207) + t156
                   * (-t204 * t123 + t206 * t197 - t131 * t201 + (0.2e1 * t116 + 0.2e1 * h4)
                      * t109 * t143
                      - t153 * t162 * t207));
    }
    {// h5
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t11 = 0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10;
        double t12 = h1 * h1;
        double t15 = h4 * h4;
        double t19 = h4 * h7;
        double t22 = h1 * h2;
        double t23 = h4 * h5;
        double t26 = a * b;
        double t28 = h5 * h7;
        double t29 = t28 * h8;
        double t36 = h1 * a;
        double t43 = b * t12;
        double t51 = h7 * h7;
        double t60 = -0.1e1 * t12 * t10 - 0.1e1 * t9 * t15 - 0.2e1 * b * t9 * t19 + 0.2e1 * t22
                     * t23 - 0.2e1 * t26 * h1 * t29 - 0.2e1 * t26 * h2 * t19 * h8 - 0.2e1 * t36
                     * t10 * h7
                     - 0.2e1 * t1 * t15 * h8 - 0.2e1 * t43 * h5 * h8 - 0.1e1 * f * t12 * t7
                     - 0.1e1 * f * t9
                     * t51 - 0.1e1 * f * t7 * t15 - 0.1e1 * f * t10 * t51;
        double t61 = b * b;
        double t66 = a * a;
        double t71 = b * h1;
        double t76 = h2 * h5;
        double t81 = h2 * h7;
        double t82 = t81 * h8;
        double t85 = f * h4;
        double t98 = t61 * h4;
        double t107 = t61 * t15 * t7 + t61 * t10 * t51 + t66 * t9 * t51 + t66 * t12 * t7 + 0.2e1
                      * t71 * h2 * h4 * h8 + 0.2e1 * t71 * t76 * h7 + 0.2e1 * f * h1 * t82 + 0.2e1
                      * t85 * t29
                      - 0.2e1 * t66 * h1 * t82 + 0.2e1 * t26 * h1 * h4 * t7 + 0.2e1 * t26 * t76
                      * t51 - 0.2e1
                      * t98 * t29 + 0.2e1 * t36 * t23 * h8 + 0.2e1 * t1 * t23 * h7;
        double t108 = t60 + t107;
        double t109 = 0.1e1 / t108;
        double t116 = h7 * b;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t123 = (0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + t116) * h6 + (t36 + t119 + t120)
                      * h9;
        double t130 = t1 * h7 + t4 * h7 + t119 * h8 + t120 * h8 + t36 * h8 + t22 + t23;
        double t131 = t130 * t109;
        double t137 = h8 * b;
        double t143 = (0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + t137) * h6 + (h8 * f + t1 + t4)
                      * h9;
        double t145 = t11 * t109 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t153 = 0.2e1 * t36 * h7 + 0.2e1 * t119 * h7 + f * t51 + t12 + t15;
        double t154 = t153 * t109;
        double t156 = -t131 * t123 + t154 * t143 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        double t166 = t108 * t108;
        double t167 = 0.1e1 / t166;
        double t185 = h7 * h8;
        double t202 = -0.4e1 * t36 * t28 - 0.2e1 * t43 * h8 + 0.2e1 * t22 * h4 - 0.2e1 * f * h5
                      * t51 + 0.2e1 * t61 * h5 * t51 - 0.2e1 * t12 * h5 + 0.2e1 * t71 * t81
                      + 0.2e1 * t85 * t185
                      + 0.2e1 * t26 * h2 * t51 - 0.2e1 * t98 * t185 + 0.2e1 * t36 * h4 * h8
                      + 0.2e1 * t1 * t19
                      - 0.2e1 * t26 * h1 * h7 * h8;
        double t203 = t123 * t202;
        double t206 = (t116 + h4) * t109;
        double t208 = t130 * t167;
        double t209 = t143 * t202;
        double t213 = 0.1e1 * h6 + h9 * b;
        dEdh5 = 0.1e1 / t159
                * (t145
                   * ((0.2e1 * t137 + 0.2e1 * h5) * t109 * t123 - t11 * t167 * t203 - t206
                      * t143 + t208
                      * t209 - t131 * t213) + t156
                   * (-t153 * t167 * t209 - t206 * t123 + t154 * t213 + t208 * t203));
    }
    {// h6
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t12 = h1 * h1;
        double t15 = h4 * h4;
        double t18 = a * b;
        double t21 = h5 * h7 * h8;
        double t25 = h4 * h7;
        double t29 = h1 * a;
        double t43 = h1 * h2;
        double t44 = h4 * h5;
        double t47 = b * h1;
        double t48 = h2 * h5;
        double t54 = h2 * h7 * h8;
        double t60 = a * a;
        double t64 = -0.1e1 * t12 * t10 - 0.1e1 * t9 * t15 - 0.2e1 * t18 * h1 * t21 - 0.2e1 * t18
                     * h2 * t25 * h8 - 0.2e1 * t29 * t10 * h7 - 0.2e1 * t1 * t15 * h8 - 0.2e1 * b
                     * t12 * h5
                     * h8 - 0.2e1 * b * t9 * t25 + 0.2e1 * t43 * t44 + 0.2e1 * t47 * t48 * h7
                     + 0.2e1 * f * h1
                     * t54 + 0.2e1 * f * h4 * t21 - 0.2e1 * t60 * h1 * t54;
        double t69 = h7 * h7;
        double t73 = b * b;
        double t107 = 0.2e1 * t18 * h1 * h4 * t7 + 0.2e1 * t18 * t48 * t69 - 0.2e1 * t73 * h4
                      * t21 + 0.2e1 * t29 * t44 * h8 + 0.2e1 * t1 * t44 * h7 + 0.2e1 * t47 * h2
                      * h4 * h8
                      - 0.1e1 * f * t12 * t7 - 0.1e1 * f * t9 * t69 - 0.1e1 * f * t7 * t15 - 0.1e1
                      * f * t10
                      * t69 + t73 * t15 * t7 + t73 * t10 * t69 + t60 * t9 * t69 + t60 * t12 * t7;
        double t109 = 0.1e1 / (t64 + t107);
        double t110 = (0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10) * t109;
        double t117 = 0.1e1 * h4 + h7 * b;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t123 = (0.1e1 * h1 + h7 * a) * h3 + t117 * h6 + (t29 + t119 + t120) * h9;
        double t131 = (t1 * h7 + t4 * h7 + t119 * h8 + t120 * h8 + t29 * h8 + t43 + t44) * t109;
        double t138 = 0.1e1 * h5 + h8 * b;
        double t143 = (0.1e1 * h2 + h8 * a) * h3 + t138 * h6 + (h8 * f + t1 + t4) * h9;
        double t145 = t110 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t154 = (0.2e1 * t29 * h7 + 0.2e1 * t119 * h7 + f * t69 + t12 + t15) * t109;
        double t156 = -t131 * t123 + t154 * t143 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        dEdh6 = 0.1e1 / t159
                * (t145 * (t110 * t117 - t131 * t138) + t156 * (-t131 * t117 + t154 * t138));
    }
    {// h7
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t11 = 0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10;
        double t12 = h1 * a;
        double t16 = h4 * h4;
        double t20 = h1 * h1;
        double t22 = h5 * h8;
        double t25 = b * t9;
        double t26 = h4 * h7;
        double t29 = h1 * h2;
        double t30 = h4 * h5;
        double t37 = a * b;
        double t40 = h5 * h7 * h8;
        double t47 = b * h1;
        double t49 = h2 * h4 * h8;
        double t52 = h2 * h5;
        double t53 = t52 * h7;
        double t56 = f * h1;
        double t58 = h2 * h7 * h8;
        double t61 = f * h4;
        double t64 = -0.2e1 * t12 * t10 * h7 - 0.2e1 * t1 * t16 * h8 - 0.2e1 * b * t20 * t22
                     - 0.2e1 * t25 * t26 + 0.2e1 * t29 * t30 - 0.1e1 * t20 * t10 - 0.1e1 * t9
                     * t16 - 0.2e1
                     * t37 * h1 * t40 - 0.2e1 * t37 * h2 * t26 * h8 + 0.2e1 * t47 * t49 + 0.2e1
                     * t47 * t53
                     + 0.2e1 * t56 * t58 + 0.2e1 * t61 * t40;
        double t65 = a * a;
        double t66 = t65 * h1;
        double t73 = h7 * h7;
        double t77 = b * b;
        double t78 = t77 * h4;
        double t90 = f * t9;
        double t96 = f * t10;
        double t101 = t77 * t10;
        double t103 = t65 * t9;
        double t107 = -0.2e1 * t66 * t58 + 0.2e1 * t37 * h1 * h4 * t7 + 0.2e1 * t37 * t52 * t73
                      - 0.2e1 * t78 * t40 + 0.2e1 * t12 * t30 * h8 + 0.2e1 * t1 * t30 * h7 - 0.1e1
                      * f * t20
                      * t7 - 0.1e1 * t90 * t73 - 0.1e1 * f * t16 * t7 - 0.1e1 * t96 * t73 + t77
                      * t16 * t7
                      + t101 * t73 + t103 * t73 + t65 * t20 * t7;
        double t108 = t64 + t107;
        double t109 = 0.1e1 / t108;
        double t110 = t11 * t109;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t123 = (0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6
                      + (t12 + t119 + t120) * h9;
        double t130 = t1 * h7 + t4 * h7 + t119 * h8 + t12 * h8 + t120 * h8 + t29 + t30;
        double t131 = t130 * t109;
        double t141 = h8 * f + t1 + t4;
        double t143 = (0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6 + t141 * h9;
        double t145 = t110 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t153 = 0.2e1 * t12 * h7 + 0.2e1 * t119 * h7 + f * t73 + t20 + t16;
        double t156 = t153 * t109 * t143 - t131 * t123 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        double t161 = t108 * t108;
        double t162 = 0.1e1 / t161;
        double t178 = h2 * h8;
        double t197 = -0.2e1 * t12 * t10 - 0.2e1 * t25 * h4 - 0.2e1 * t90 * h7 - 0.2e1 * t96 * h7
                      + 0.2e1 * t101 * h7 + 0.2e1 * t103 * h7 + 0.2e1 * t47 * t52 + 0.2e1 * t56
                      * t178 + 0.2e1
                      * t61 * t22 - 0.2e1 * t66 * t178 + 0.4e1 * t37 * t53 - 0.2e1 * t78 * t22
                      + 0.2e1 * t1
                      * t30 - 0.2e1 * t37 * h1 * h5 * h8 - 0.2e1 * t37 * t49;
        double t198 = t123 * t197;
        double t203 = a * h3 + b * h6 + f * h9;
        double t205 = t141 * t109;
        double t207 = t130 * t162;
        double t208 = t143 * t197;
        dEdh7 = 0.1e1 / t159
                * (t145 * (-t11 * t162 * t198 + t110 * t203 - t205 * t143 + t207 * t208) + t156
                   * (-t205 * t123 + t207 * t198 - t131 * t203
                      + (0.2e1 * t12 + 0.2e1 * t119 + 0.2e1 * t120)
                      * t109 * t143 - t153 * t162 * t208));
    }
    {// h8
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t11 = 0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10;
        double t12 = a * b;
        double t14 = h5 * h7;
        double t15 = t14 * h8;
        double t19 = h4 * h7;
        double t23 = h1 * h1;
        double t26 = h4 * h4;
        double t29 = h1 * a;
        double t36 = b * t23;
        double t43 = h1 * h2;
        double t44 = h4 * h5;
        double t47 = b * h1;
        double t48 = h2 * h4;
        double t52 = h2 * h5;
        double t56 = f * h1;
        double t57 = h2 * h7;
        double t58 = t57 * h8;
        double t61 = f * h4;
        double t64 = -0.2e1 * t12 * h1 * t15 - 0.2e1 * t12 * h2 * t19 * h8 - 0.1e1 * t23 * t10
                     - 0.1e1 * t9 * t26 - 0.2e1 * t29 * t10 * h7 - 0.2e1 * t1 * t26 * h8 - 0.2e1
                     * t36 * h5
                     * h8 - 0.2e1 * b * t9 * t19 + 0.2e1 * t43 * t44 + 0.2e1 * t47 * t48 * h8
                     + 0.2e1 * t47
                     * t52 * h7 + 0.2e1 * t56 * t58 + 0.2e1 * t61 * t15;
        double t65 = a * a;
        double t66 = t65 * h1;
        double t69 = h1 * h4;
        double t73 = h7 * h7;
        double t77 = b * b;
        double t78 = t77 * h4;
        double t87 = f * t23;
        double t93 = f * t26;
        double t99 = t77 * t26;
        double t105 = t65 * t23;
        double t107 = -0.2e1 * t66 * t58 + 0.2e1 * t12 * t69 * t7 + 0.2e1 * t12 * t52 * t73
                      - 0.2e1 * t78 * t15 + 0.2e1 * t29 * t44 * h8 + 0.2e1 * t1 * t44 * h7 - 0.1e1
                      * t87 * t7
                      - 0.1e1 * f * t9 * t73 - 0.1e1 * t93 * t7 - 0.1e1 * f * t10 * t73 + t99 * t7
                      + t77 * t10
                      * t73 + t65 * t9 * t73 + t105 * t7;
        double t108 = t64 + t107;
        double t109 = 0.1e1 / t108;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t121 = t29 + t119 + t120;
        double t123 = (0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6 + t121 * h9;
        double t130 = t1 * h7 + t4 * h7 + t119 * h8 + t120 * h8 + t29 * h8 + t43 + t44;
        double t131 = t130 * t109;
        double t140 = h8 * f;
        double t143 = (0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6 + (t1 + t4 + t140)
                      * h9;
        double t145 = t11 * t109 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t153 = 0.2e1 * t29 * h7 + 0.2e1 * t119 * h7 + f * t73 + t23 + t26;
        double t154 = t153 * t109;
        double t156 = -t131 * t123 + t154 * t143 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        double t167 = t108 * t108;
        double t168 = 0.1e1 / t167;
        double t204 = -0.2e1 * t1 * t26 - 0.2e1 * t36 * h5 - 0.2e1 * t87 * h8 - 0.2e1 * t93 * h8
                      + 0.2e1 * t99 * h8 + 0.2e1 * t105 * h8 + 0.2e1 * t47 * t48 + 0.2e1 * t56
                      * t57 + 0.2e1
                      * t61 * t14 - 0.2e1 * t66 * t57 + 0.4e1 * t12 * t69 * h8 - 0.2e1 * t78 * t14
                      + 0.2e1 * t29
                      * t44 - 0.2e1 * t12 * h1 * h5 * h7 - 0.2e1 * t12 * t48 * h7;
        double t205 = t204 * t123;
        double t207 = t121 * t109;
        double t209 = t130 * t168;
        double t210 = t204 * t143;
        double t215 = a * h3 + b * h6 + f * h9;
        dEdh8 = 0.1e1 / t159
                * (t145
                   * ((0.2e1 * t1 + 0.2e1 * t4 + 0.2e1 * t140) * t109 * t123 - t11 * t168 * t205
                      - t207
                      * t143 + t209 * t210 - t131 * t215) + t156
                   * (-t153 * t168 * t210 - t207 * t123 + t154 * t215 + t209 * t205));
    }
    {// h9
        double t1 = h2 * a;
        double t4 = h5 * b;
        double t7 = h8 * h8;
        double t9 = h2 * h2;
        double t10 = h5 * h5;
        double t12 = a * b;
        double t15 = h5 * h7 * h8;
        double t19 = h4 * h7;
        double t23 = h1 * h1;
        double t26 = h4 * h4;
        double t29 = h1 * a;
        double t43 = h1 * h2;
        double t44 = h4 * h5;
        double t47 = h2 * h5;
        double t48 = h7 * h7;
        double t52 = b * b;
        double t62 = -0.2e1 * t12 * h1 * t15 - 0.2e1 * t12 * h2 * t19 * h8 - 0.1e1 * t23 * t10
                     - 0.1e1 * t9 * t26 - 0.2e1 * t29 * t10 * h7 - 0.2e1 * t1 * t26 * h8 - 0.2e1
                     * b * t23 * h5
                     * h8 - 0.2e1 * b * t9 * t19 + 0.2e1 * t43 * t44 + 0.2e1 * t12 * t47 * t48
                     - 0.2e1 * t52
                     * h4 * t15 + 0.2e1 * t29 * t44 * h8 + 0.2e1 * t1 * t44 * h7;
        double t63 = b * h1;
        double t73 = h2 * h7 * h8;
        double t79 = a * a;
        double t107 = 0.2e1 * t63 * h2 * h4 * h8 + 0.2e1 * t63 * t47 * h7 + 0.2e1 * f * h1 * t73
                      + 0.2e1 * f * h4 * t15 - 0.2e1 * t79 * h1 * t73 + 0.2e1 * t12 * h1 * h4 * t7
                      + t79 * t9
                      * t48 + t79 * t23 * t7 - 0.1e1 * f * t23 * t7 - 0.1e1 * f * t9 * t48 - 0.1e1
                      * f * t26
                      * t7 - 0.1e1 * f * t10 * t48 + t52 * t26 * t7 + t52 * t10 * t48;
        double t109 = 0.1e1 / (t62 + t107);
        double t110 = (0.2e1 * t1 * h8 + 0.2e1 * t4 * h8 + f * t7 + t9 + t10) * t109;
        double t119 = h4 * b;
        double t120 = h7 * f;
        double t121 = t29 + t119 + t120;
        double t123 = (0.1e1 * h1 + h7 * a) * h3 + (0.1e1 * h4 + h7 * b) * h6 + t121 * h9;
        double t131 = (t1 * h7 + t4 * h7 + t119 * h8 + t120 * h8 + t29 * h8 + t43 + t44) * t109;
        double t141 = h8 * f + t1 + t4;
        double t143 = (0.1e1 * h2 + h8 * a) * h3 + (0.1e1 * h5 + h8 * b) * h6 + t141 * h9;
        double t145 = t110 * t123 - t131 * t143 - u;
        double t146 = t145 * t145;
        double t154 = (0.2e1 * t29 * h7 + 0.2e1 * t119 * h7 + f * t48 + t23 + t26) * t109;
        double t156 = -t131 * t123 + t154 * t143 - v;
        double t157 = t156 * t156;
        double t159 = sqrt(t146 + t157);
        dEdh9 = 0.1e1 / t159
                * (t145 * (t110 * t121 - t131 * t141) + t156 * (-t131 * t121 + t154 * t141));
    }
}

// jacobian formulas for H^{-1}
template<typename T>
void jac_inv_equations(const libNumerics::vector<T> &P, const libNumerics::matrix<T> &s, T u, T v, T &dEdh1, T &dEdh2,
                       T &dEdh3, T &dEdh4, T &dEdh5, T &dEdh6, T &dEdh7, T &dEdh8, T &dEdh9)
{
    T h1 = P[0], h2 = P[1], h3 = P[2];
    T h4 = P[3], h5 = P[4], h6 = P[5];
    T h7 = P[6], h8 = P[7], h9 = P[8];
    T a = s(0, 2), b = s(1, 2), f = s(2, 2);
    dEdh1 = (2*(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))*(h3 + a*h9))
                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                +((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(-((h2 + a*h8)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8))
                    -(h2 + a*h8)
                    *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)) + (2*h1 + 2*a*h7)
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                            *(h1
                              *(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                          +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                          *(h2
                            *(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)),
                          2))*(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                  *(
                                      h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                     *(
                                         h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                   *(
                                       h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - u) + 2
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))*(h3 + a*h9))
                 /(
                     -((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                     +(
                         h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
               +((
                     -(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                 *(-((h2 + a*h8)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8))
                   -(
                       h2 + a*h8)*(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                   + (2*h1 + 2*a*h7)
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
                 *(
                     h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
               /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                           *(
                               h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                         + (h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                         *(
                             h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)),
                         2)
               - ((-h2 - a*h8)*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
               /(
                   -((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(
                       h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh2 = (2*(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                 *((h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))*(2*h2 + 2*a*h8)
                   -(h1 + a*h7)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                   - (h1 + a*h7)*(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                   )*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                            *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                          +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                          *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
                -((2*h2 + 2*a*h8)*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                    *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                  +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                  *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u)
             +2*(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *((h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))*(2*h2 + 2*a*h8)
                    -(h1 + a*h7)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                    - (h1 + a*h7)*(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                    )*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                             *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                           +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                           *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
                 -((-h1 - a*h7)*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh3 = ((-2*(h1 + a*h7)*(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
              *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u))
             /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                 *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
               +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
               *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
             -(2*(h1 + a*h7)*(-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
               *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
             /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                 *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
               +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
               *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh4 = (2*(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))*(h6 + b*h9))
                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                +((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(-((h5 + b*h8)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8))
                    -(h5 + b*h8)*(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                    +(2*h4 + 2*b*h7)*(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                            *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                          +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                          *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2))
             *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u)
             +2*(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))*(h6 + b*h9))
                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                 +((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                   *(-((h5 + b*h8)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8))
                     -(h5 + b*h8)*(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                     +(2*h4 + 2*b*h7)*(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                             *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                           +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                           *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
                 -((-h5 - b*h8)*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh5 = (2*(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                 *((h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))*(2*h5 + 2*b*h8)
                   -(h4 + b*h7)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                   - (h4 + b*h7)*(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                   )*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                            *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                          +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                          *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
                -((2*h5 + 2*b*h8)*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                    *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                  +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                  *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u)
             +2*(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *((h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))*(2*h5 + 2*b*h8)
                    -(h4 + b*h7)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                    - (h4 + b*h7)*(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                    )*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                             *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                           +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                           *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
                 -((-h4 - b*h7)*(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh6 = ((-2*(h4 + b*h7)*(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
              *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u))
             /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                 *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
               +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
               *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
             -(2*(h4 + b*h7)*(-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
               *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
             /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                 *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
               +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
               *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh7 = (2*(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))*(a*h3 + b*h6 + f*h9))
                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                +((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(-((a*h2 + b*h5 + f*h8)
                      *(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8))
                    -(a*h2 + b*h5 + f*h8)
                    *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                    +(2*a*h1 + 2*b*h4 + 2*f*h7)
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                            *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                          +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                          *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2))
             *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u)
             +2
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *(a*h3 + b*h6 + f*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
               +((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                 *(-((a*h2 + b*h5 + f*h8)
                     *(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8))
                   -(a*h2 + b*h5 + f*h8)
                   *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8))
                   +(2*a*h1 + 2*b*h4 + 2*f*h7)
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
                 *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
               /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                           *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                         +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                         *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
               -((-(a*h2) - b*h5 - f*h8)
                 *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
               /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                   *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                 +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                 *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh8 = (2*(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                 *((h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(2*a*h2 + 2*b*h5 + 2*f*h8)
                   -(a*h1 + b*h4 + f*h7)*(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                   -(a*h1 + b*h4 + f*h7)
                   *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                 *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                            *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                          +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                          *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
                -((2*a*h2 + 2*b*h5 + 2*f*h8)
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                    *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                  +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                  *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u)
             +2*(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *((h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                    *(2*a*h2 + 2*b*h5 + 2*f*h8)
                    -(a*h1 + b*h4 + f*h7)
                    *(h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                    -(a*h1 + b*h4 + f*h7)
                    *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /Power<T>(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                             *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                           +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                           *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)), 2)
                 -((-(a*h1) - b*h4 - f*h7)
                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
             *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                  *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                 /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                     *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                   +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                   *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));

    dEdh9 = ((-2*(a*h1 + b*h4 + f*h7)*(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
              *(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - u))
             /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                 *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
               +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
               *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))
             -(2*(a*h1 + b*h4 + f*h7)*(-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
               *(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7*(a*h2 + b*h5 + f*h8))
                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8)))) - v))
             /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                 *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
               +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
               *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
            /(2.
              *Sqrt<T>(Power<T>(-(((h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))
                                   *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                  /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h8)
                                      *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                    +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                    *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8*(a*h2 + b*h5 + f*h8))))
                                - u, 2)
                       +Power<T>(-(((-(h1*(h2 + a*h8)) - h4*(h5 + b*h8) - h7
                                     *(a*h2 + b*h5 + f*h8))
                                    *(h3*(h1 + a*h7) + h6*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)*h9))
                                   /(-((h2*(h1 + a*h7) + h5*(h4 + b*h7) + (a*h1 + b*h4 + f*h7)
                                        *h8)
                                       *(h1*(h2 + a*h8) + h4*(h5 + b*h8) + h7*(a*h2 + b*h5 + f*h8)))
                                     +(h1*(h1 + a*h7) + h4*(h4 + b*h7) + h7*(a*h1 + b*h4 + f*h7))
                                     *(h2*(h2 + a*h8) + h5*(h5 + b*h8) + h8
                                       *(a*h2 + b*h5 + f*h8)))) - v, 2)));
}

#endif
