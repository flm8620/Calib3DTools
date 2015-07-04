/*----------------------------------------------------------------------------

  Image Gaussian filtering functions.

  Copyright 2010-2011 rafael grompone von gioi (grompone@gmail.com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.

  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----------------------------- Gaussian filter ------------------------------*/
/*----------------------------------------------------------------------------*/
/** @file gauss.c
    Image Gaussian filtering and subsampling.
    @author rafael grompone von gioi (grompone@gmail.com)
 */
/*----------------------------------------------------------------------------*/
#include "gauss.h"

#include <iostream>
#include <cmath>
#include "image.h"
#include "messager.h"

#include "ntuple.h"

#ifndef UINT_MAX
#include <limits>
const static unsigned UINT_MAX = std::numeric_limits<unsigned>::max();
#endif

/**
 * @brief Compute Gaussian function value where a=c=1 and b=0
 * @param x
 * @return
 */
static inline double gaussian(double x) { return exp(-.5*x*x);}

/*----------------------------------------------------------------------------*/
/** Compute a Gaussian kernel of length 'kernel->dim',
    standard deviation 'sigma', and centered at value 'mean'.

    For example, if mean=0.5, the Gaussian will be centered
    in the middle point between values 'kernel->values[0]'
    and 'kernel->values[1]'.
 */
void gaussian_kernel(ntuple_list kernel, const double sigma, const double mean)
{

    /* check parameters */
    if (kernel == NULL || kernel->values == NULL)
        libMsg::error("gaussian_kernel: invalid n-tuple 'kernel'.");
    if (sigma <= 0.0) libMsg::error("gaussian_kernel: 'sigma' must be positive.");

    if (kernel->max_size < 1) enlarge_ntuple_list(kernel);
    kernel->size = 1;

    /* compute Gaussian kernel */
    unsigned int i;
    const double inv_sigma = 1./sigma;
    double x, sum;
    for (i =0, sum =0., x = -mean*inv_sigma; i < kernel->dim; i++, x+=inv_sigma)
        sum += kernel->values[i] =  gaussian(x);

    /* normalization */
    if (sum >= 0.0) {
        const double inv_sum = 1./sum;
        for (i = 0; i < kernel->dim; i++) kernel->values[i] *= inv_sum;
    }
}


/*
   The size of the kernel is selected to guarantee that the
   the first discarted term is at least 10^PREC times smaller
   than the central value. For that, h should be larger than x, with
     e^(-x^2/2sigma^2) = 1/10^PREC.
   Then,
     OFFSET = sqrt( 2 * prec * ln(10) )
     x = sigma * OFFSET.
 */
const static double PREC = 3.;
const static double OFFSET = sqrt(2.0 * PREC * log(10.0));

/*----------------------------------------------------------------------------*/
void gaussian_filter(ImageGray<double> &out, double sigma, const ImageGray<double> &in)
{
    const int width = in.xsize(), height = in.ysize(), double_width =2*width, double_height = 2*height;
    unsigned int x, y;
    int offset, i, j, kernelSize;
    ntuple_list kernel;

    /* check parameters */
    if (sigma <= 0.0)
        libMsg::error("gaussian_filter: 'sigma; must be positive.");
    if (!in.isValid())
        libMsg::error("gaussian_filter: invalid image.");
    if (out.xsize()!=width || out.ysize()!=height)
        out.resize( width, height );

    /* create temporary pixel buffer */
    double * const tmp = (double*)malloc(width*height*sizeof(double)), *ptmp;

    /* compute gaussian kernel */
    offset = ceil(sigma * OFFSET);
    kernelSize = 2*offset + 1;
    kernel = new_ntuple_list(kernelSize);
    gaussian_kernel(kernel, sigma, (double)offset);

    /* x axis convolution */
    for (x = 0; x < width; x++)
        for (y = 0, ptmp = tmp+x; y < height; y++, ptmp+=width) {
            *ptmp = 0.;
            for (i = 0; i < kernelSize; i++) {
                j = x - offset + i;

                /* symmetry boundary condition */
                while (j < 0) j += double_width;
                while (j >= double_width) j -= double_width;
                if (j >= (int)width) j = double_width-1-j;

                *ptmp += in.pixel(j, y) * kernel->values[i];
            }
        }

    /* y axis convolution */
    for (x = 0; x < width; x++)
        for (y = 0; y < height; y++) {
            double &pixel = out.pixel(x, y) = 0.;
            for (i = 0; i < kernelSize; i++) {
                j = y - offset + i;

                /* symmetry boundary condition */
                while (j < 0) j += double_height;
                while (j >= double_height) j -= double_height;
                if (j >= (int)height) j = double_height-1-j;

                pixel += tmp[x + j*width] * kernel->values[i];
            }
        }

    /* free memory */
    free(tmp);
    free_ntuple_list(kernel);
}

/*----------------------------------------------------------------------------*/
/** Scale the input image 'in' by a factor 'scale' by Gaussian sub-sampling.

    For example, scale=0.8 will give a result at 80% of the original size.

    The image is convolved with a Gaussian kernel
    @f[
        G(x,y) = \frac{1}{2\pi\sigma^2} e^{-\frac{x^2+y^2}{2\sigma^2}}
    @f]
    before the sub-sampling to prevent aliasing.

    The standard deviation sigma given by:
    -  sigma = sigma_scale / scale,   if scale <  1.0
    -  sigma = sigma_scale,           if scale >= 1.0

    To be able to sub-sample at non-integer steps, some interpolation
    is needed. In this implementation, the interpolation is done by
    the Gaussian kernel, so both operations (filtering and sampling)
    are done at the same time. The Gaussian kernel is computed
    centered on the coordinates of the required sample. In this way,
    when applied, it gives directly the result of convolving the image
    with the kernel and interpolated to that particular position.

    A fast algorithm is done using the separability of the Gaussian
    kernel. Applying the 2D Gaussian kernel is equivalent to applying
    first a horizontal 1D Gaussian kernel and then a vertical 1D
    Gaussian kernel (or the other way round). The reason is that
    @f[
        G(x,y) = G(x) * G(y)
    @f]
    where
    @f[
        G(x) = \frac{1}{\sqrt{2\pi}\sigma} e^{-\frac{x^2}{2\sigma^2}}.
    @f]
    The algorithm first apply a combined Gaussian kernel and sampling
    in the x axis, and then the combined Gaussian kernel and sampling
    in the y axis.
 */
void gaussian_sampler(ImageGray<double> &out, const double scale,
                      const double sigma_scale, const ImageGray<double> &in)
{
    const int width = in.xsize(), height = in.ysize(),
            double_width =2*width, double_height = 2*height,
            zoomed_width = (int)floor(width * scale),
            zoomed_height = (int)floor(height * scale);
    /* sigma, kernel size and memory for the kernel */
    const double sigma = scale < 1.0 ? sigma_scale / scale : sigma_scale;
    const unsigned int offset = (unsigned int)ceil(sigma * OFFSET);

    ntuple_list kernel;
    int  x, y, i, j, xc, yc;
    double xx, yy, sum;

    /* check parameters */
    if (!in.isValid())
        libMsg::error("gaussian_sampler: invalid image.");
    if (scale <= 0.0)
        libMsg::error("gaussian_sampler: 'scale' must be positive.");
    if (sigma_scale <= 0.0)
        libMsg::error("gaussian_sampler: 'sigma_scale' must be positive.");

    /* get memory for images */
    if (width * scale > (double)UINT_MAX
        || height * scale > (double)UINT_MAX)
        libMsg::error("gaussian_sampler: the output image size exceeds the handled size.");

    double * const tmp =(double*)malloc(zoomed_width * height * sizeof(double)), *ptmp;

    kernel = new_ntuple_list( 2*offset + 1 );

    /* First subsampling: x axis */
    for (x = 0; x < zoomed_width; x++) {
        /*
           x   is the coordinate in the new image.
           xx  is the corresponding x-value in the original size image.
           xc  is the integer value, the pixel coordinate of xx.
         */
        /* pixel (0,0) corresponds to coordinate (0.5,0.5)
           because the pixel goes from 0.0 to 1.0 */
        xx = ((double)x + 0.5) / scale;
        xc = (int)floor(xx);
        gaussian_kernel(kernel, sigma, (double)offset + xx - (double)xc - 0.5);
        /* the kernel must be computed for each x because the fine
           offset xx-xc is different in each case */

        for (y =0, ptmp =tmp+x; y < height; y++, ptmp+=zoomed_width) {
            *ptmp = 0.0;
            for (i = 0; i < kernel->dim; i++) {
                j = xc - offset + i;

                /* symmetry boundary condition */
                while (j < 0) j += double_width;
                while (j >= double_width) j -= double_width;
                if (j >= (int)width) j = double_width-1-j;

                *ptmp += in.pixel(j, y) * kernel->values[i];
            }
        }
    }

    /* Second subsampling: y axis */
    out.resize(zoomed_width, zoomed_height);
    for (y = 0; y < zoomed_height; y++) {
        /*
           y   is the coordinate in the new image.
           yy  is the corresponding x-value in the original size image.
           yc  is the integer value, the pixel coordinate of xx.
         */
        /* pixel (0,0) corresponds to coordinate (0.5,0.5)
           because the pixel goes from 0.0 to 1.0 */
        yy = ((double)y + 0.5) / scale;
        yc = (int)floor(yy);
        gaussian_kernel(kernel, sigma, (double)offset + yy - (double)yc - 0.5);
        /* the kernel must be computed for each y because the fine
           offset yy-yc is different in each case */

        for (x = 0; x < zoomed_width; x++) {
            double &pixel = out.pixel(x, y) = 0.;
            for (i = 0; i < kernel->dim; i++) {
                j = yc - offset + i;

                /* symmetry boundary condition */
                while (j < 0) j += double_height;
                while (j >= double_height) j -= double_height;
                if (j >= (int)height) j = double_height-1-j;

                pixel += tmp[x + j * zoomed_width] * kernel->values[i];
            }
        }
    }

    /* free memory */
    free(tmp);
    free_ntuple_list(kernel);
}

/*----------------------------------------------------------------------------*/
