/*----------------------------------------------------------------------------

  Implementation of Devernay's sub-pixel edge detector.

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
/*
   Implementation of the algorithm described in
   "A Non-Maxima Suppression Method for Edge Detection with Sub-Pixel Accuracy"
   by Frederic Devernay. Rapport de recherche INRIA No.2724, November 1995.
*/
/*----------------------------------------------------------------------------*/
#include "devernay.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

#include "image.h"
#include "messager.h"

#include "ntuple.h"
#include "gauss.h"

/*----------------------------------------------------------------------------*/
/** Add a 2-tuple to an 2-tuple list.
 */
static void add_2tuple(ntuple_list out, double v1, double v2)
{
    /* check parameters */
    if (out == NULL) libMsg::error("add_2tuple: invalid n-tuple input.");
    if (out->dim != 2) libMsg::error("add_2tuple: the n-tuple must be a 2-tuple.");

    /* if needed, alloc more tuples to 'out' */
    if (out->size == out->max_size) enlarge_ntuple_list(out);
    if (out->values == NULL) libMsg::error("add_2tuple: invalid n-tuple input.");

    /* add new 2-tuple */
    out->values[ out->size * out->dim + 0 ] = v1;
    out->values[ out->size * out->dim + 1 ] = v2;

    /* update number of tuples counter */
    out->size++;
}

/*----------------------------------------------------------------------------*/
/** Devernay sub-pixel edge detector.
 */
ntuple_list devernay(ImageGray<double> &image, double sigma, double th_low, double th_hi)
{
    ntuple_list out = new_ntuple_list(2);

    double mod, mod_up_grad, mod_down_grad, dx, dy, Dx, Dy, weight, off;
    unsigned int x, y, xx, yy, xsize, ysize, i;
    int i_up, j_up, i_down, j_down;

    /* check input */
    if (!image.isValid())
        libMsg::error("devernay: invalid input image.");
    if (sigma <= 0.0) libMsg::error("devernay: sigma must be positive.");
    xsize = image.xsize();
    ysize = image.ysize();

    /* get memory */
    ImageGray<double> gradx(xsize, ysize, 0.0),
    grady(xsize, ysize, 0.0),
    modgrad(xsize, ysize, 0.0),
    offset(xsize, ysize, -1000.0);
    ImageGray<BYTE> canny(xsize, ysize, 0);

    /* Gaussian filter */
    gaussian_filter(image, sigma);
    /* compute gradient */
    for (x = 1; x < (xsize-1); x++)
        for (y = 1; y < (ysize-1); y++) {
            gradx.pixel(x, y) = 0.5*(image.pixel(x+1, y)-image.pixel(x-1, y));
            grady.pixel(x, y) = 0.5*(image.pixel(x, y+1)-image.pixel(x, y-1));
            modgrad.pixel(x, y) = sqrt(gradx.pixel(x, y)*gradx.pixel(x, y)
                                       +grady.pixel(x, y)*grady.pixel(x, y));
        }

    /* select local maxima */
    for (x = 2; x < (xsize-2); x++)
        for (y = 2; y < (ysize-2); y++) {
            dx = gradx.pixel(x, y);
            dy = grady.pixel(x, y);
            i_up = dx > 0.0 ? 1 : -1;
            i_down = dx > 0.0 ? -1 : 1;
            j_up = dy > 0.0 ? 1 : -1;
            j_down = dy > 0.0 ? -1 : 1;

            /* compute grandient values in gradient direction */
            mod = modgrad.pixel(x, y);
            if (fabs(dx) > fabs(dy)) {/* roughly vertical edge */
                weight = fabs(dy) / fabs(dx);
                mod_up_grad
                    = weight
                      * modgrad.pixel(x+i_up, y)+(1.0-weight)*modgrad.pixel(x+i_up, y+j_up);
                mod_down_grad
                    = weight* modgrad.pixel(x + i_down, y)
                      + (1.0-weight) * modgrad.pixel(x + i_down, y+j_down);
            } else {/* roughly horizontal edge */
                weight = fabs(dx) / fabs(dy);
                mod_up_grad
                    = weight    * modgrad.pixel(x, y+j_up)
                      + (1.0-weight) * modgrad.pixel(x +  i_up, y+j_up);
                mod_down_grad
                    = weight    * modgrad.pixel(x, y+j_down)
                      + (1.0-weight) * modgrad.pixel(x + i_down, y+j_down);
            }

            /* keep local maxima of gradient along gradient direction */
            if (mod > mod_down_grad && mod >= mod_up_grad) {
                /* offset value in [-0.5,0.5] also means local maxima */
                offset.pixel(x, y) = (mod_up_grad - mod_down_grad)
                                     / (mod + mod - mod_up_grad - mod_down_grad)
                                     / 2.0;
                /* Hi Canny threshold on gradient */
                if (mod > th_hi) { /* a Canny point found */
                    canny.pixel(x, y) = 255;
                    add_2tuple(out, (double)x, (double)y);
                }
            }
        }

    /* Canny hysteresis, second threshold: Low threshold:
       local maxima are accepted as Canny points if,
       they are connected to an already accepted Canny point,
       and the gradient is larger than th_low (hysteresis). */
    for (i = 0; i < out->size; i++) {
        x = (unsigned int)out->values[ i * out->dim + 0 ];
        y = (unsigned int)out->values[ i * out->dim + 1 ];

        /* check all 8-connected neightbors */
        for (xx = x-1; xx <= x+1; xx++)
            for (yy = y-1; yy <= y+1; yy++)
                if (canny.pixel(xx, yy) == 0   /* not marked as Canny P. */
                    && offset.pixel(xx, yy) > -1.0 /* local maxima */
                    && modgrad.pixel(xx, yy) >= th_low) {
                    canny.pixel(xx, yy) = 255;
                    add_2tuple(out, (double)xx, (double)yy);
                }
    }

    /* Devernay Sub-pixel refinement */
    for (i = 0; i < out->size; i++) {
        x = (unsigned int)out->values[ i * out->dim + 0 ];
        y = (unsigned int)out->values[ i * out->dim + 1 ];
        off = offset.pixel(x,y);

        /* normalize gradient */
        dx = gradx.pixel(x,y);
        dy = grady.pixel(x,y);
        if (fabs(dx) < fabs(dy)) {
            Dx = dx/fabs(dy);
            Dy = (dy >= 0.0) ? 1.0 : -1.0;
        } else {
            Dx = (dx >= 0.0) ? 1.0 : -1.0;
            Dy = dy/fabs(dx);
        }

        /* apply sub-pixel correcting term */
        out->values[ i * out->dim + 0 ] += off * Dx;
        out->values[ i * out->dim + 1 ] += off * Dy;
    }

    return out;
}

/*----------------------------------------------------------------------------*/
