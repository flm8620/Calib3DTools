/*----------------------------------------------------------------------------

  Image data type and basic functions.

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
/*----------------------------- Image Data Types -----------------------------*/
/*----------------------------------------------------------------------------*/
/** @file image.c
    Image data types.
    @author rafael grompone von gioi (grompone@gmail.com)
 */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "messager.h"
#include "spline.h"

/*----------------------------------------------------------------------------*/
/** Free memory used in image_char 'i'.
 */
void free_image_char(image_char i)
{
    if (i == NULL || i->data == NULL)
        libMsg::error("free_image_char: invalid input image.");
    free((void *)i->data);
    free((void *)i);
}

/*----------------------------------------------------------------------------*/
/** Create a new image_char of size 'xsize' times 'ysize'.
 */
image_char new_image_char(unsigned int xsize, unsigned int ysize)
{
    image_char image;

    /* check parameters */
    if (xsize == 0 || ysize == 0) libMsg::error("new_image_char: invalid image size.");

    /* get memory */
    image = (image_char)malloc(sizeof(struct image_char_s));
    if (image == NULL) libMsg::error("not enough memory.");
    image->data = (unsigned char *)calloc((size_t)(xsize*ysize),
                                          sizeof(unsigned char));
    if (image->data == NULL) libMsg::error("not enough memory.");

    /* set image size */
    image->xsize = xsize;
    image->ysize = ysize;

    return image;
}

/*----------------------------------------------------------------------------*/
/** Create a new image_char of size 'xsize' times 'ysize',
    initialized to the value 'fill_value'.
 */
image_char new_image_char_ini(unsigned int xsize, unsigned int ysize, unsigned char fill_value)
{
    image_char image = new_image_char(xsize, ysize); /* create image */
    unsigned int N = xsize*ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) image->data[i] = fill_value;

    return image;
}

/*----------------------------------------------------------------------------*/
/** Create a new image_char, copy of image 'in'.
 */
image_char new_image_char_copy(image_char in)
{
    image_char image = new_image_char(in->xsize, in->ysize); /* create image */
    unsigned int N = in->xsize * in->ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) image->data[i] = in->data[i];

    return image;
}

/*----------------------------------------------------------------------------*/
/** Free memory used in image_int 'i'.
 */
void free_image_int(image_int i)
{
    if (i == NULL || i->data == NULL)
        libMsg::error("free_image_int: invalid input image.");
    free((void *)i->data);
    free((void *)i);
}

/*----------------------------------------------------------------------------*/
/** Create a new image_int of size 'xsize' times 'ysize'.
 */
image_int new_image_int(unsigned int xsize, unsigned int ysize)
{
    image_int image;

    /* check parameters */
    if (xsize == 0 || ysize == 0) libMsg::error("new_image_int: invalid image size.");

    /* get memory */
    image = (image_int)malloc(sizeof(struct image_int_s));
    if (image == NULL) libMsg::error("not enough memory.");
    image->data = (int *)calloc((size_t)(xsize*ysize), sizeof(int));
    if (image->data == NULL) libMsg::error("not enough memory.");

    /* set image size */
    image->xsize = xsize;
    image->ysize = ysize;

    return image;
}

/*----------------------------------------------------------------------------*/
/** Create a new image_int of size 'xsize' times 'ysize',
    initialized to the value 'fill_value'.
 */
image_int new_image_int_ini(unsigned int xsize, unsigned int ysize, int fill_value)
{
    image_int image = new_image_int(xsize, ysize); /* create image */
    unsigned int N = xsize*ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) image->data[i] = fill_value;

    return image;
}

/*----------------------------------------------------------------------------*/
/** Create a new image_int, copy of image 'in'.
 */
image_int new_image_int_copy(image_int in)
{
    image_int image = new_image_int(in->xsize, in->ysize); /* create image */
    unsigned int N = in->xsize * in->ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) image->data[i] = in->data[i];

    return image;
}

/*----------------------------------------------------------------------------*/
/** Free memory used in image_double 'i'.
 */
void free_image_double(image_double i)
{
    if (i == NULL || i->data == NULL)
        libMsg::error("free_image_double: invalid input image.");
    free((void *)i->data);
    free((void *)i);
}

/*----------------------------------------------------------------------------*/
/** Create a new image_double of size 'xsize' times 'ysize'.
 */
image_double new_image_double(unsigned int xsize, unsigned int ysize)
{
    image_double image;

    /* check parameters */
    if (xsize == 0 || ysize == 0) libMsg::error("new_image_double: invalid image size.");

    /* get memory */
    image = (image_double)malloc(sizeof(struct image_double_s));
    if (image == NULL) libMsg::error("not enough memory.");
    image->data = (double *)calloc((size_t)(xsize*ysize), sizeof(double));
    if (image->data == NULL) libMsg::error("not enough memory.");

    /* set image size */
    image->xsize = xsize;
    image->ysize = ysize;

    return image;
}

/*----------------------------------------------------------------------------*/
/** Create a new image_double of size 'xsize' times 'ysize',
    initialized to the value 'fill_value'.
 */
image_double new_image_double_ini(unsigned int xsize, unsigned int ysize, double fill_value)
{
    image_double image = new_image_double(xsize, ysize); /* create image */
    unsigned int N = xsize*ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) image->data[i] = fill_value;

    return image;
}

/*----------------------------------------------------------------------------*/
/** Create a new image_double, copy of image 'in'.
 */
image_double new_image_double_copy(image_double in)
{
    image_double image = new_image_double(in->xsize, in->ysize); /* create image */
    unsigned int N = in->xsize * in->ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) image->data[i] = in->data[i];

    return image;
}

/*----------------------------------------------------------------------------*/
/** Linear Interpolation.
 */
double interpolate_image_double(image_double &in, int order, double u, double v)
{
    double color;
    if (!interpolate_spline(in, order, u, v, color))
        color = 0;
    return color;
}

/*----------------------------------------------------------------------------*/
/** Is pixel inside image?
 */
bool valid_image_double(image_double &in, int x, int y)
{
    return 0 <= x && x < in->xsize && 0 <= y && y < in->ysize;
}

/*----------------------------------------------------------------------------*/

image_double new_image_double_from_image_char(image_char in)
{
    image_double image = new_image_double(in->xsize, in->ysize);
    unsigned int N = in->xsize * in->ysize;
    for (int i = 0; i < N; i++) image->data[i] = double(in->data[i]);
    return image;
}

void free_image_double_RGB(image_double_RGB i)
{
    if (i == NULL || i->Rdata == NULL || i->Gdata == NULL || i->Bdata == NULL)
        libMsg::error("free_image_double: invalid input image.");
    free((void *)i->Rdata);
    free((void *)i->Gdata);
    free((void *)i->Bdata);
    free((void *)i);
}

image_double_RGB new_image_double_RGB(unsigned int xsize, unsigned int ysize)
{
    image_double_RGB image;

    /* check parameters */
    if (xsize == 0 || ysize == 0) libMsg::error("new_image_double: invalid image size.");

    /* get memory */
    image = (image_double_RGB)malloc(sizeof(struct image_double_RGB_s));
    if (image == NULL)libMsg:: error("not enough memory.");
    image->Rdata = (double *)calloc((size_t)(xsize*ysize), sizeof(double));
    if (image->Rdata == NULL) libMsg::error("not enough memory.");
    image->Gdata = (double *)calloc((size_t)(xsize*ysize), sizeof(double));
    if (image->Gdata == NULL) libMsg::error("not enough memory.");
    image->Bdata = (double *)calloc((size_t)(xsize*ysize), sizeof(double));
    if (image->Bdata == NULL) libMsg::error("not enough memory.");

    /* set image size */
    image->xsize = xsize;
    image->ysize = ysize;

    return image;
}

image_double_RGB new_image_double_RGB_ini(unsigned int xsize, unsigned int ysize,
                                          pixel_double_RGB fill_value)
{
    image_double_RGB image = new_image_double_RGB(xsize, ysize); /* create image */
    unsigned int N = xsize*ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) {
        image->Rdata[i] = fill_value.R;
        image->Gdata[i] = fill_value.G;
        image->Bdata[i] = fill_value.B;
    }
    return image;
}

image_double_RGB new_image_double_RGB_copy(image_double_RGB in)
{
    image_double_RGB image = new_image_double_RGB(in->xsize, in->ysize); /* create image */
    unsigned int N = in->xsize * in->ysize;
    unsigned int i;

    /* initialize */
    for (i = 0; i < N; i++) {
        image->Rdata[i] = in->Rdata[i];
        image->Gdata[i] = in->Gdata[i];
        image->Bdata[i] = in->Bdata[i];
    }

    return image;
}

pixel_double_RGB interpolate_image_double_RGB(image_double_RGB &in, int order, double u, double v)
{
    pixel_double_RGB color;
    if (!interpolate_spline_RGB(in, order, u, v, color)) {
        color.R = 0.0;
        color.G = 0.0;
        color.B = 0.0;
    }

    return color;
}

bool valid_image_double_RGB(image_double_RGB &in, int x, int y)
{
    return 0 <= x && x < in->xsize && 0 <= y && y < in->ysize;
}
