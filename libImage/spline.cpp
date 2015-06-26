/* Spline interpolation.
    Copyright (C) 2007 Lionel Moisan <Lionel.Moisan@parisdescartes.fr>
    Copyright (C) 2010 Pascal Monasse <monasse@imagine.enpc.fr>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "spline.h"
// #include "libIO/nan.h"
#include <cmath>
#include <cfloat>
#include <cstring>
#include <assert.h>

const static unsigned int MAX_ORDER = 11;
const static int INIT_SPLINE_N_ARRARY_START = 4;
const static double INIT_SPLINE_N[][MAX_ORDER+2] = {
    #define _ INIT_SPLINE_N
   /* order= 4 */  {1./2./3./ 4., -_[0][0]* 5., -_[0][1]* 4./2., -_[0][2]* 3./3., -_[0][3]*2./4., -_[0][4]*1./5. },
   /* order= 5 */  { _[0][0]/ 5., -_[1][0]* 6., -_[1][1]* 5./2., -_[1][2]* 4./3., -_[1][3]*3./4., -_[1][4]*2./5., -_[1][5]*1./6. },
   /* order= 6 */  { _[1][0]/ 6., -_[2][0]* 7., -_[2][1]* 6./2., -_[2][2]* 5./3., -_[2][3]*4./4., -_[2][4]*3./5., -_[2][5]*2./6., -_[2][6]*1./7. },
   /* order= 7 */  { _[2][0]/ 7., -_[3][0]* 8., -_[3][1]* 7./2., -_[3][2]* 6./3., -_[3][3]*5./4., -_[3][4]*4./5., -_[3][5]*3./6., -_[3][6]*2./7., -_[3][7]*1./8. },
   /* order= 8 */  { _[3][0]/ 8., -_[4][0]* 9., -_[4][1]* 8./2., -_[4][2]* 7./3., -_[4][3]*6./4., -_[4][4]*5./5., -_[4][5]*4./6., -_[4][6]*3./7., -_[4][7]*2./8., -_[4][8]*1./9. },
   /* order= 9 */  { _[4][0]/ 9., -_[5][0]*10., -_[5][1]* 9./2., -_[5][2]* 8./3., -_[5][3]*7./4., -_[5][4]*6./5., -_[5][5]*5./6., -_[5][6]*4./7., -_[5][7]*3./8., -_[5][8]*2./9., -_[5][9]*1./10. },
   /* order=10 */  { _[5][0]/10., -_[6][0]*11., -_[6][1]*10./2., -_[6][2]* 9./3., -_[6][3]*8./4., -_[6][4]*7./5., -_[6][5]*6./6., -_[6][6]*5./7., -_[6][7]*4./8., -_[6][8]*3./9., -_[6][9]*2./10., -_[6][10]*1./11. },
   /* order=11 */  { _[6][0]/11., -_[7][0]*12., -_[7][1]*11./2., -_[7][2]*10./3., -_[7][3]*9./4., -_[7][4]*8./5., -_[7][5]*7./6., -_[7][6]*6./7., -_[7][7]*5./8., -_[7][8]*4./9., -_[7][9]*3./10., -_[7][10]*2./11., -_[7][11]*1./12. }
    #undef _
};

//z-filters for order == 2 to MAX_ORDER
const static int Z_FILTERS_ARRARY_START = 2;
const static double Z_FILTERS[][5] = {
   /* order= 2 */  { -0.17157288/* sqrt(8)-3 */},
   /* order= 3 */  { -0.26794919/* sqrt(3)-2 */},
   /* order= 4 */  { -0.361341,     -0.0137254 },
   /* order= 5 */  { -0.430575,     -0.0430963 },
   /* order= 6 */  { -0.488295,     -0.0816793,   -0.00141415 },
   /* order= 7 */  { -0.53528,      -0.122555,    -0.00914869 },
   /* order= 8 */  { -0.574687,     -0.163035,    -0.0236323,    -0.000153821 },
   /* order= 9 */  { -0.607997,     -0.201751,    -0.0432226,    -0.00212131  },
   /* order=10 */  { -0.636551,     -0.238183,    -0.065727,     -0.00752819,   -0.0000169828 },
   /* order=11 */  { -0.661266,     -0.27218,     -0.0897596,    -0.0166696,    -0.000510558  }
};

static double initcausal(double *c, int step, int n, double z)
{
    double zk, z2k, iz, sum;

    zk = z;
    iz = 1./z;
    z2k = pow(z, (double)n-1.);
    sum = c[0] + z2k * c[step*(n-1)];
    z2k = z2k*z2k*iz;
    for (int k = 1; k <= n-2; k++) {
        sum += (zk+z2k)*c[step*k];
        zk *= z;
        z2k *= iz;
    }
    return sum/(1.-zk*zk);
}

static double initanticausal(double *c, int step, int n, double z)
{
    return (z/(z*z-1.)) * (z*c[step*(n-2)]+c[step*(n-1)]);
}

static void invspline1D(double *c, int step, int size, const double *z, int npoles)
{
    /* normalization */
    double lambda = 1.0;
    for (int k = npoles-1; k >= 0; k--)
        lambda *= (1.-z[k])*(1.-1./z[k]);
    for (int n = size-1; n >= 0; n--)
        c[step*n] *= static_cast<double>(lambda);

    for (int k = 0; k < npoles; k++) { // Loop on poles
        /* forward recursion */
        c[0] = static_cast<double>(initcausal(c, step, size, z[k]));
        for (int n = 1; n < size; n++)
            c[step*n] += static_cast<double>(z[k]*c[step*(n-1)]);
        /* backward recursion */
        c[step*(size-1)] = static_cast<double>(initanticausal(c, step, size, z[k]));
        for (int n = size-2; n >= 0; n--)
            c[step*n] = static_cast<double>(z[k]*(c[step*(n+1)]-c[step*n]));
    }
}

/*
/// Put in array \a z the poles of the spline of given \a order.
static bool fill_poles(double *z, int order)
{
    switch (order) {
    case 1:
        break;
    // case 2: z[0]=-0.17157288;  // sqrt(8)-3
    // break;
    case 3:
        z[0] = -0.26794919;    // sqrt(3)-2
        break;
    // case 4: z[0]=-0.361341; z[1]=-0.0137254;
    // break;
    case 5:
        z[0] = -0.430575;
        z[1] = -0.0430963;
        break;
    // case 6: z[0]=-0.488295; z[1]=-0.0816793; z[2]=-0.00141415;
    // break;
    case 7:
        z[0] = -0.53528;
        z[1] = -0.122555;
        z[2] = -0.00914869;
        break;
    // case 8: z[0]=-0.574687; z[1]=-0.163035; z[2]=-0.0236323;
    // z[3]=-0.000153821;
    // break;
    case 9:
        z[0] = -0.607997;
        z[1] = -0.201751;
        z[2] = -0.0432226;
        z[3] = -0.00212131;
        break;
    // case 10: z[0]=-0.636551; z[1]=-0.238183; z[2]=-0.065727;
    // z[3]=-0.00752819; z[4]=-0.0000169828;
    // break;
    case 11:
        z[0] = -0.661266;
        z[1] = -0.27218;
        z[2] = -0.0897596;
        z[3] = -0.0166696;
        z[4] = -0.000510558;
        break;
    default:
        return false;
    }
    return true;
} */

/// Prepare image for cardinal spline interpolation.
bool prepare_spline(ImageGray<double> &im, int order)
{
    if (order < 3)
        return true;

    // Init poles of associated z-filter
    const double *z = Z_FILTERS[order-Z_FILTERS_ARRARY_START];
//    if (!fill_poles(z, order))
//        return false;
    int npoles = order/2;

    for (int y = 0; y < im.ysize(); y++) // Filter on lines
        invspline1D(&im.pixel(0, y), 1, im.xsize(), z, npoles);
    for (int x = 0; x < im.xsize(); x++) // Filter on columns
        invspline1D(&im.pixel(x, 0), im.xsize(), im.ysize(), z, npoles);
    return true;
}
bool prepare_spline_RGB(ImageRGB<double> &im, int order)
{
    if (order < 3)
        return true;

    // Init poles of associated z-filter
    const double *z = Z_FILTERS[order-Z_FILTERS_ARRARY_START];
//    if (!fill_poles(z, order))
//        return false;
    int npoles = order/2;

    for (int y = 0; y < im.ysize(); y++) {     // Filter on lines
        invspline1D(&im.pixel_R(0, y), 1, im.xsize(), z, npoles);
        invspline1D(&im.pixel_G(0, y), 1, im.xsize(), z, npoles);
        invspline1D(&im.pixel_B(0, y), 1, im.xsize(), z, npoles);
    }
    for (int x = 0; x < im.xsize(); x++) {     // Filter on columns
        invspline1D(&im.pixel_R(x, 0), im.xsize(), im.ysize(), z, npoles);
        invspline1D(&im.pixel_G(x, 0), im.xsize(), im.ysize(), z, npoles);
        invspline1D(&im.pixel_B(x, 0), im.xsize(), im.ysize(), z, npoles);
    }
    return true;
}

/* c[] = values of interpolation function at ...,t-2,t-1,t,t+1,... */

/* coefficients for cubic interpolant (Keys' function) */
static void keys(double *c, double t, double a)
{
    double t2 = t*t;
    double at = a*t;
    c[0] = a*t2*(1.0-t);
    c[1] = (2.0*a+3.0 - (a+2.0)*t)*t2 - at;
    c[2] = ((a+2.0)*t - a-3.0)*t2 + 1.0;
    c[3] = a*(t-2.0)*t2 + at;
}

/* coefficients for cubic spline */
static void spline3(double *c, double t)
{
    const static double TWO_THIRDS = 2./3., ONE_SIXTH = 1./6.;
    double t2 = t*t, t3 = t2*t;
    double tmp = 1.0-t, tmp2 = t2-t-t+1.0, tmp3 = tmp*tmp2;
    c[0] = ONE_SIXTH * t3;
    c[1] = TWO_THIRDS - 0.5f*tmp2*(1.0f+t);
    c[2] = TWO_THIRDS - 0.5f*t2*(2.0f-t);
    c[3] = ONE_SIXTH * tmp3;
}

/*
// pre-computation for spline of order >3
static void init_splinen(double *a, int n)
{
    a[0] = 1.;
    for (int k = 2; k <= n; k++)
        a[0] /= (double)k;
    for (int k = 1; k <= n+1; k++)
        a[k] = -a[k-1] *(n+2-k)/k;
} */

/* fast integral power function */
static float ipow(float x, int n)
{
    float res;
    for (res = 1.; n; n >>= 1) {
        if (n&1)
            res *= x;
        x *= x;
    }
    return res;
}

/* coefficients for spline of order >3 */
static void splinen(double *c, double t, const double *a, int n)
{
    memset((void *)c, 0, (n+1)*sizeof(double));
    for (int k = 0; k <= n+1; k++) {
        double xn = ipow(t+(double)k, n);
        for (int i = k; i <= n; i++)
            c[i] += a[i-k]*xn;
    }
}

/// Spline interpolation of given \a order of image \a im at point (x,y).
/// \a out must be an array of size the number of components.
/// Supported orders: 0(replication), 1(bilinear), -3(Keys's bicubic), 3, 5, 7,
/// 9, 11.
/// \a paramKeys is Keys's parameter, only used for order -3.
/// Success means a valid order and pixel in image.
bool interpolate_spline(ImageGray<double> &im, int order, double x, double y, double &out,
                        double paramKeys)
{
    double cx[12], cy[12];

    /* CHECK ORDER */
    if (order != 0 && order != 1 && order != -3
        && order != 3 && order != 5 && order != 7 && order != 9 && order != 11)
        return false;

    const double * ak = INIT_SPLINE_N[order-INIT_SPLINE_N_ARRARY_START];
//    if (order > 3)
//        init_splinen(ak, order);

    bool bInside = false;
    /* INTERPOLATION */
    if (order == 0) { /* zero order interpolation (pixel replication) */
        int xi = (int)floor((double)x);
        int yi = (int)floor((double)y);
        bInside = im.pixelInside(xi, yi);// im.valid(xi, yi);
        if (bInside)
            out = im.pixel(xi, yi);
    } else { /* higher order interpolations */
        bInside = (x >= 0.0f && x <= (double)im.xsize() && y >= 0.0f && y <= (double)im.ysize());
        if (bInside) {
            x -= 0.5f;
            y -= 0.5f;
            int xi = (x < 0) ? -1 : (int)x;
            int yi = (y < 0) ? -1 : (int)y;
            double ux = x - (double)xi;
            double uy = y - (double)yi;
            switch (order) {
            case 1: /* first order interpolation (bilinear) */
                cx[0] = ux;
                cx[1] = 1.0f-ux;
                cy[0] = uy;
                cy[1] = 1.0f-uy;
                break;
            case -3: /* third order interpolation (bicubic Keys' function) */
                keys(cx, ux, paramKeys);
                keys(cy, uy, paramKeys);
                break;
            case 3: /* spline of order 3 */
                spline3(cx, ux);
                spline3(cy, uy);
                break;
            default: /* spline of order >3 */
                splinen(cx, ux, ak, order);
                splinen(cy, uy, ak, order);
                break;
            }
            int n2 = (order == -3) ? 2 : (order+1)/2;
            int n1 = 1-n2;
            /* this test saves computation time */
            if (im.pixelInside(xi+n1, yi+n1)&& im.pixelInside(xi+n2, yi+n2)) {
                double color = 0.0;
                for (int dy = n1; dy <= n2; dy++) {
                    int adrs = (xi+n1) + (yi+dy) * im.xsize();
                    for (int dx = n1; dx <= n2; dx++) {
                        double f = im.data(adrs);
                        color += cy[n2-dy]*cx[n2-dx] * f;
                        adrs++;
                    }
                }
                out = color;
            } else {
                out = 0.0;
            }
        }
    }
    return bInside;
}

bool interpolate_spline_RGB(ImageRGB<double> &im, int order, double x, double y, double &Rout,
                            double &Gout, double &Bout, double paramKeys)
{
    double cx[12], cy[12];

    /* CHECK ORDER */
    if (order != 0 && order != 1 && order != -3
        && order != 3 && order != 5 && order != 7 && order != 9 && order != 11)
        return false;

    const double * ak = INIT_SPLINE_N[order-INIT_SPLINE_N_ARRARY_START];
//    if (order > 3)
//        init_splinen(ak, order);

    bool bInside = false;
    /* INTERPOLATION */
    if (order == 0) { /* zero order interpolation (pixel replication) */
        int xi = (int)floor((double)x);
        int yi = (int)floor((double)y);
        bInside = im.pixelInside(xi, yi);
        if (bInside) {
            Rout = im.pixel_R(xi, yi);
            Gout = im.pixel_G(xi, yi);
            Bout = im.pixel_B(xi, yi);
        }
    } else { /* higher order interpolations */
        bInside = (x >= 0.0f && x <= (double)im.xsize() && y >= 0.0f && y <= (double)im.ysize());
        if (bInside) {
            x -= 0.5f;
            y -= 0.5f;
            int xi = (x < 0) ? -1 : (int)x;
            int yi = (y < 0) ? -1 : (int)y;
            double ux = x - (double)xi;
            double uy = y - (double)yi;
            switch (order) {
            case 1: /* first order interpolation (bilinear) */
                cx[0] = ux;
                cx[1] = 1.0f-ux;
                cy[0] = uy;
                cy[1] = 1.0f-uy;
                break;
            case -3: /* third order interpolation (bicubic Keys' function) */
                keys(cx, ux, paramKeys);
                keys(cy, uy, paramKeys);
                break;
            case 3: /* spline of order 3 */
                spline3(cx, ux);
                spline3(cy, uy);
                break;
            default: /* spline of order >3 */
                splinen(cx, ux, ak, order);
                splinen(cy, uy, ak, order);
                break;
            }
            int n2 = (order == -3) ? 2 : (order+1)/2;
            int n1 = 1-n2;
            /* this test saves computation time */
            if (im.pixelInside(xi+n1, yi+n1)&&im.pixelInside(xi+n2, yi+n2)) {
                Rout = Gout = Bout = 0.0;
                for (int dy = n1; dy <= n2; dy++) {
                    int adrs = (xi+n1) + (yi+dy) * im.xsize();
                    for (int dx = n1; dx <= n2; dx++) {
                        Rout += cy[n2-dy]*cx[n2-dx] * im.Rdata(adrs);
                        Gout += cy[n2-dy]*cx[n2-dx] * im.Gdata(adrs);
                        Bout += cy[n2-dy]*cx[n2-dx] * im.Bdata(adrs);
                        adrs++;
                    }
                }
            } else {
                Rout = Gout = Bout = 0.0;
            }
        }
    }
    return bInside;
}

