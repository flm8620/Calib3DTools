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
const static double INIT_SPLINE_N[MAX_ORDER-INIT_SPLINE_N_ARRARY_START+1][MAX_ORDER+2] = {
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
   /* order= 2 */  { -0.17157288 },/* sqrt(8)-3 */
   /* order= 3 */  { -0.26794919 },/* sqrt(3)-2 */
   /* order= 4 */  { -0.361341, -0.0137254 },
   /* order= 5 */  { -0.430575, -0.0430963 },
   /* order= 6 */  { -0.488295, -0.0816793, -1.41415e-3 },
   /* order= 7 */  { -0.53528,  -0.122555,  -9.14869e-3 },
   /* order= 8 */  { -0.574687, -0.163035,  -0.0236323, -1.53821e-4 },
   /* order= 9 */  { -0.607997, -0.201751,  -0.0432226, -2.12131e-3  },
   /* order=10 */  { -0.636551, -0.238183,  -0.0657270, -7.52819e-3, -1.69828e-5 },
   /* order=11 */  { -0.661266, -0.27218,   -0.0897596, -0.0166696,  -5.10558e-4 }
};

const static double Z_RECIPROCALS[][5] = {
#define _(o,i) ( 1.0/ Z_FILTERS[o][i] )
   /* order= 2 */  { _(0,0)                             },
   /* order= 3 */  { _(1,0)                             },
   /* order= 4 */  { _(2,0),_(2,1)                      },
   /* order= 5 */  { _(3,0),_(3,1)                      },
   /* order= 6 */  { _(4,0),_(4,1),_(4,2)               },
   /* order= 7 */  { _(5,0),_(5,1),_(5,2)               },
   /* order= 8 */  { _(6,0),_(6,1),_(6,2),_(6,3)        },
   /* order= 9 */  { _(7,0),_(7,1),_(7,2),_(7,3)        },
   /* order=10 */  { _(8,0),_(8,1),_(8,2),_(8,3),_(8,4) },
   /* order=11 */  { _(9,0),_(9,1),_(9,2),_(9,3),_(9,4) }
#undef _
};

const static double Z_LAMBDAS[] = {
#define _(o,i) ( (1.0-Z_FILTERS[o][i]) * (1.0-1.0/Z_FILTERS[o][i]) )
   /* order= 2 */  _(0,0),
   /* order= 3 */  _(1,0),
   /* order= 4 */  _(2,0)*_(2,1),
   /* order= 5 */  _(3,0)*_(3,1),
   /* order= 6 */  _(4,0)*_(4,1)*_(4,2),
   /* order= 7 */  _(5,0)*_(5,1)*_(5,2),
   /* order= 8 */  _(6,0)*_(6,1)*_(6,2)*_(6,3),
   /* order= 9 */  _(7,0)*_(7,1)*_(7,2)*_(7,3),
   /* order=10 */  _(8,0)*_(8,1)*_(8,2)*_(8,3)*_(8,4),
   /* order=11 */  _(9,0)*_(9,1)*_(9,2)*_(9,3)*_(9,4)
#undef _
};

static void invspline1D(double * const c, const int step, const int size, const int order)
{
    double * const lastc = c + step*(size-1);

    /* normalization */
    const double lambda = Z_LAMBDAS[order-Z_FILTERS_ARRARY_START];
    for (double* ck = lastc; ck >=c; ck-=step) *ck *= lambda;

    int npoles = order/2;
    for (int k = 0; k < npoles; k++) { // Loop on poles

        // the z, square z, reciprocal z of pole k.
        const double zk = Z_FILTERS[order-Z_FILTERS_ARRARY_START][k];
        const double zk2 = zk*zk;
        const double zkr = Z_RECIPROCALS[order-Z_FILTERS_ARRARY_START][k]; // 1/zk

        /* forward recursion */
        double zn =zk, z2n =ipow(zk, size-1), sum = *c + *lastc*z2n;
        z2n=z2n*z2n*zkr;
        for (double* cp=c+step; cp<lastc; cp+=step, zn*=zk, z2n*=zkr) sum += *cp*(zn+z2n);
        *c = sum/(1.-zn*zn); //init causal
        for (double last =*c, *cp =c+step; cp<=lastc; cp+=step) last = *cp = *cp + last*zk;

        /* backward recursion */
        *lastc = (*lastc*zk + *(lastc-step)*zk2)/(zk2-1.); // initial anti causal
        for (double last =*lastc, *cp =lastc-step; cp >=c; cp-=step) last = *cp = (last - *cp)*zk;
    }
}

/// Prepare image for cardinal spline interpolation.
bool prepare_spline(ImageGray<double> &image, int order)
{
    if (order > 11)
        return false;

    if(order>=3) {
        for (int y = 0; y < image.ysize(); y++) // Filter on lines
            invspline1D(&image.pixel(0, y), 1, image.xsize(), order);
        for (int x = 0; x < image.xsize(); x++) // Filter on columns
            invspline1D(&image.pixel(x, 0), image.xsize(), image.ysize(), order);
    }
    return true;
}


bool prepare_spline_RGB(ImageRGB<double> &image, int order)
{
    if (order>11)
        return false;

    if(order>=3) {
        for (int y = 0; y < image.ysize(); y++) {     // Filter on lines
            invspline1D(&(image.pixel_R(0, y)), 1, image.xsize(), order);
            invspline1D(&(image.pixel_G(0, y)), 1, image.xsize(), order);
            invspline1D(&(image.pixel_B(0, y)), 1, image.xsize(), order);
        }

        for (int x = 0; x < image.xsize(); x++) {     // Filter on columns
            invspline1D(&image.pixel_R(x, 0), image.xsize(), image.ysize(), order);
            invspline1D(&image.pixel_G(x, 0), image.xsize(), image.ysize(), order);
            invspline1D(&image.pixel_B(x, 0), image.xsize(), image.ysize(), order);
        }
    }

    return true;
}

/* coefficients[] = values of interpolation function at ...,t-2,t-1,t,t+1,... */
/* coefficients for cubic interpolant (Keys' function) */
static void keys(double coefficients[4], const double t, const double key)
{
    const double c = 1.-t, t2 = t*t, c2 =c*c,
            ct2 =c*t2, tc2 = t*c2, ktc2 =key*tc2, kct2 = key*ct2;

    coefficients[0] = kct2;
    coefficients[1] = ct2 + t2 - ktc2 ;
    coefficients[2] = tc2 + c2 - kct2 ;
    coefficients[3] = ktc2;
}

/* coefficients for cubic spline */
static void spline3(double coefficients[4], const double t)
{
    const static double SIXTH = 1./6., TWOTHIRDS = 2./3., HALF = 1./2.;
    const double c =1.-t, t2 =t*t, t3 =t2*t, c2 =c*c, c3 =c2*c;

    coefficients[0] =  SIXTH*t3;
    coefficients[1] =  -HALF*(t+1.)*c2 + TWOTHIRDS;
    coefficients[2] =  -HALF*(c+1.)*t2 + TWOTHIRDS;
    coefficients[3] =  SIXTH*c3;
}

/* coefficients for spline of order >3 */
static void spline_coefficients(double *coefficients, double t, int order)
{
    assert( order>3 );

    unsigned margin = order+1;
    const double * init = INIT_SPLINE_N[ order-INIT_SPLINE_N_ARRARY_START ];

    for (int k =0; k<=margin; k++) coefficients[k] =0.;
    for (int k =0; k<=margin; k++) {
        const double tko =ipow( t+k, order );
        for (int i=k,j=0; i<margin; i++,j++)
            coefficients[i] += init[j]*tko;
    }
}


/// zero order interpolation (pixel replication)
static bool zero_order_interpolation(const ImageGray<double> &image, int x, int y, double &out) {
    if (!image.pixelInside(x, y)) return false;

    out = image.pixel(x, y);
    return true;
}

/// higher order interpolations
static double do_interpolation( const ImageGray<double> &image, int x, int y, int margin, const double cx[], const double cy[] )
{
    int low_margin = 1-margin;
    if (!image.pixelInside(x+low_margin, y+low_margin)||!image.pixelInside(x+margin, y+margin))
        return 0.0;

    /* this test saves computation time */
    int y_step = image.xsize();
    double color = 0.0;
    for (int dy =low_margin, rowAdr =(y+low_margin)*y_step +x+low_margin;
                 dy <= margin;
                 dy++, rowAdr+=y_step)
        for (int dx = low_margin, adr = rowAdr ; dx <= margin; dx++, adr++)
            color += image.data(adr) * cy[margin-dy] * cx[margin-dx];

    return color;
}

/// Spline interpolation of given \a order of image \a image at point (x,y).
/// \a out must be an array of size the number of components.
/// Supported orders: 0(replication), 1(bilinear), -3(Keys's bicubic), 3, 5, 7,
/// 9, 11.
/// \a paramKeys is Keys's parameter, only used for order -3.
/// Success means a valid order and pixel in image.
bool interpolate_spline(const ImageGray<double> &image, int order, double x, double y, double &out, double paramKeys)
{
    /* CHECK PARAMETERS */
    if(x<0.0 || x>static_cast<double>(image.xsize()) || y<0.0 || y>static_cast<double>(image.ysize()))
        return false;

    double x_shift = x - 0.5;
    double y_shift = y - 0.5;

    int xi = (x_shift < 0) ? -1 : static_cast<int>(x_shift);
    int yi = (y_shift < 0) ? -1 : static_cast<int>(y_shift);
    double ux = x_shift - static_cast<double>(xi);
    double uy = y_shift - static_cast<double>(yi);

    double coefficients_x[MAX_ORDER+1], coefficients_y[MAX_ORDER+1];
    int radius;

    /* INTERPOLATION */
    switch (order) {
    case 0:  //zero order interpolation (pixel replication)
        return zero_order_interpolation(image, static_cast<int>(floor(x)), static_cast<int>(floor(y)), out);

    case 1: /* first order interpolation (bilinear) */
        coefficients_x[0] = ux;
        coefficients_x[1] = 1.0-ux;
        coefficients_y[0] = uy;
        coefficients_y[1] = 1.0-uy;
        radius = 1;
        break;

    case -3: /* third order interpolation (bicubic Keys' function) */
        keys(coefficients_x, ux, paramKeys);
        keys(coefficients_y, uy, paramKeys);
        radius = 2;
        break;

    case 3: /* spline of order 3 */
        spline3(coefficients_x, ux);
        spline3(coefficients_y, uy);
        radius = 2;
        break;

    case 5:
    case 7:
    case 9:
    case 11:
         /* spline of order >3 */
        spline_coefficients(coefficients_x, ux, order);
        spline_coefficients(coefficients_y, uy, order);
        radius = (order+1)/2;
        break;

    default:
        return false;
    }

    out = do_interpolation( image, xi, yi, radius, coefficients_x, coefficients_y );
    return true;
}

static bool zero_order_interpolation_rgb(const ImageRGB<double> &image, int x, int y,
                                         double &Rout, double &Gout, double &Bout )
{
    if (!image.pixelInside(x, y))
        return false;

    Rout = image.pixel_R(x, y);
    Gout = image.pixel_G(x, y);
    Bout = image.pixel_B(x, y);
    return true;
}

static void do_interpolation_rgb(const ImageRGB<double> &image, int x, int y, int radius,
                                 const double coefficients_x[], const double coefficients_y[],
                                 double &Rout, double &Gout, double &Bout)
{
    int low_margin = 1-radius;
    Rout = Gout = Bout = 0.0;
    /* this test saves computation time */
    if (!image.pixelInside(x+low_margin, y+low_margin) || !image.pixelInside(x+radius, y+radius))
        return ;
    const int y_step = image.xsize();
    for (int dy = low_margin, rowAdrs = (y+low_margin)*y_step + x+low_margin;
         dy <= radius; dy++, rowAdrs+=y_step)
        for (int dx =low_margin, adrs =rowAdrs; dx <= radius; dx++, adrs++) {
            Rout += coefficients_y[radius-dy]*coefficients_x[radius-dx] * image.Rdata(adrs);
            Gout += coefficients_y[radius-dy]*coefficients_x[radius-dx] * image.Gdata(adrs);
            Bout += coefficients_y[radius-dy]*coefficients_x[radius-dx] * image.Bdata(adrs);
        }

}

bool interpolate_spline_RGB(const ImageRGB<double> &image, int order, double x, double y,
                            double &Rout, double &Gout, double &Bout, double paramKeys)
{
    /* CHECK PARAMETERS */
    if(x<0.0 || x>static_cast<double>(image.xsize()) || y<0.0 || y>static_cast<double>(image.ysize()))
        return false;

    double x_shift = x - 0.5;
    double y_shift = y - 0.5;

    int xi = (x_shift < 0.0) ? -1 : static_cast<int>(x_shift);
    int yi = (y_shift < 0.0) ? -1 : static_cast<int>(y_shift);
    double ux = x_shift - static_cast<double>(xi);
    double uy = y_shift - static_cast<double>(yi);

    double coefficients_x[MAX_ORDER+1], coefficients_y[MAX_ORDER+1];
    int radius;

    /* INTERPOLATION */
    switch (order) {
    case 0:      // zero order interpolation (pixel replication)
        return zero_order_interpolation_rgb(image, static_cast<int>(floor(x)), static_cast<int>(floor(y)), Rout, Gout, Bout);

    case 1: /* first order interpolation (bilinear) */
        coefficients_x[0] = ux;
        coefficients_x[1] = 1.0f-ux;
        coefficients_y[0] = uy;
        coefficients_y[1] = 1.0f-uy;
        radius = 1;
        break;
    case -3: /* third order interpolation (bicubic Keys' function) */
        keys(coefficients_x, ux, paramKeys);
        keys(coefficients_y, uy, paramKeys);
        radius = 2;
        break;
    case 3: /* spline of order 3 */
        spline3(coefficients_x, ux);
        spline3(coefficients_y, uy);
        radius = 2;
        break;

    case 5:  /* spline of order >3 */
    case 7:
    case 9:
    case 11:
        spline_coefficients(coefficients_x, ux, order);
        spline_coefficients(coefficients_y, uy, order);
        radius = (order+1)/2;
        break;

    default:
        return false;
    }
    do_interpolation_rgb( image, xi, yi, radius, coefficients_x, coefficients_y, Rout, Gout, Bout );
    return true;
}

