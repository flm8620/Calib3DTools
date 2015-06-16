/*----------------------------------------------------------------------------

  Measure the straightness of a set of points grouped into groups
  that should correspond to aligned points.

  Copyright 2011 rafael grompone von gioi (grompone@gmail.com),
                 Zhongwei Tang (tang@cmla.ens-cachan.fr).

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
#include "distCorrection.h"
#include "matrix.h"
#include "correction.h"
#include "pgm_io.h"
#include "misc.h"
#include "spline.h"

#include "distortion.h"
#include "gaussian_convol_on_curve.h"
#include "straight_edge_points.h"
#include "ntuple_ll.h"
#include "pgm_io.h"

#include <algorithm>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

/*----------------------------------------------------------------------------*/
/* Static parameters.
 */
static const double sigma = 1.0;
static const double th_low = 1.0;
static const double th_hi = 10.0;
static const double min_length = 100.0;

/* Static parameters for Gaussian convolution along the lines */
static const double unit_sigma = 0.8;
static const double Nsigma = 0.8;
static const bool resampling = true;
static const bool eliminate_border = false;
static const double up_factor = 1.0;

using namespace libNumerics;

/*----------------------------------------------------------------------------*/
/*                                    Funcs                                    */
/*----------------------------------------------------------------------------*/
/* Measure RMSE of lines on the given image */
template<typename T>
T image_RMSE(int length_thresh, double down_factor, image_double image)
{
    printf("\n Measuring RMSE of lines on the image... \n");
    DistortedLines<T> distLines;
    int w, h;
    ntuple_ll point_set, p;
    double x, y;
    int total_nb_lines, total_threshed_nb_lines, threshed_nb_lines;
    ntuple_list convolved_pts;
    point_set = new_ntuple_ll(1);
    total_nb_lines = 0;
    total_threshed_nb_lines = 0;
    threshed_nb_lines = 0;

    p = straight_edge_points(image, sigma, th_low, th_hi, min_length);
    w = image->xsize;
    h = image->ysize;
    /* copy the points set in the new image to the global set of points */
    for (int j = 0; j < (int)p->size; j++) {
        if ((int)p->list[j]->size > length_thresh) {
            add_ntuple_list(point_set, p->list[j]);
            p->list[j] = 0;
        } else {
            threshed_nb_lines += 1;
        }
    }
    printf("For image there are totally %d lines detected and %d of them are eliminated.\n",
           p->size, threshed_nb_lines);
    free_ntuple_ll(p);

    distLines.pushMemGroup((int)point_set->size);
    int countL = 0;
    for (unsigned int i = 0; i < point_set->size; i++) {
        /* Gaussian convolution and sub-sampling */
        convolved_pts = gaussian_convol_on_curve(unit_sigma, Nsigma, resampling, eliminate_border,
                                                 up_factor, down_factor, point_set->list[i]);
        countL++;
        /* Save points to DistortionLines structure */
        for (unsigned int j = 0; j < convolved_pts->size; j++) {
            x = convolved_pts->values[j*convolved_pts->dim];
            y = convolved_pts->values[j*convolved_pts->dim+1];
            distLines.pushPoint(countL-1, x, y);
        }
    }
    free_ntuple_ll(point_set);
    free_ntuple_list(convolved_pts);

    int order = 3;
    T xp = (T)w/2+0.2, yp = (T)h/2+0.2;
    int sizexy = (order + 1) * (order + 2) / 2;
    vector<T> paramsX = vector<T>::zeros(sizexy);
    paramsX[sizexy-3] = 1;
    vector<T> paramsY = vector<T>::zeros(sizexy);
    paramsY[sizexy-2] = 1;
    T rmse = distLines.RMSE(paramsX, paramsY, order, order, xp, xp);
    T rmse_max = distLines.RMSE_max(paramsX, paramsY, order, order, xp, yp);
    printf("RMSE / maximum RMSE: %12.6g / %12.6g \n", rmse, rmse_max);
    return rmse;
}

/* Given an image and a correction polynomial. Apply it to every pixel and save result to output folder */
template<typename T>
void correct_image(image_double in, image_double &out, int spline_order,
                   const vector<T> &poly_params_inv, const int degX, const int degY)
{
    /* read the data */
    int sizex = (degX + 1) * (degX + 2) / 2;
    int sizey = (degY + 1) * (degY + 2) / 2;
    vector<T> paramsX = poly_params_inv.copyRef(0, sizex-1);
    vector<T> paramsY = poly_params_inv.copyRef(sizex, sizex+sizey-1);
    std::cout<<"\n Undistorted image is being calculated... \n"<<std::endl;
    int wi = in->xsize, he = in->ysize;
    T xp = (T)wi/2+0.2, yp = (T)he/2+0.2;
    out = new_image_double(wi, he);
    std::cout << "[" << std::flush;
    prepare_spline(in, spline_order);
    for (int y = 0; y < he; y++) {
        for (int x = 0; x < wi; x++) {
            /* do the correction for every pixel */
            T p1 = 0, p2 = 0;
            undistortPixel(p1, p2, paramsX, paramsY, x, y, xp, yp, degX, degY);
            double clrR = interpolate_image_double(in, spline_order, p1, p2);
            clrR = std::min(std::max(clrR, 0.), 255.);
            out->data[x+y*wi] = clrR;
        }
        /* output progress */
        T percent = ((T)y / (T)he)*100;
        if (!(y % (int)(0.2*he))) std::cout << (int)percent+1 << "%" << std::flush;
        else if (!(y % (int)(0.04*he))) std::cout << "." << std::flush;
    }
    std::cout << "] " << std::flush;
    std::cout<<" done \n"<<std::endl;
}

template<typename T>
void correct_image_RGB(image_double_RGB in, image_double_RGB &out, int spline_order,
                       const vector<T> &poly_params_inv, const int degX, const int degY)
{
    /* read the data */
    int sizex = (degX + 1) * (degX + 2) / 2;
    int sizey = (degY + 1) * (degY + 2) / 2;
    vector<T> paramsX = poly_params_inv.copyRef(0, sizex-1);
    vector<T> paramsY = poly_params_inv.copyRef(sizex, sizex+sizey-1);
    std::cout<<"\n Undistorted image is being calculated... \n"<<std::endl;
    int wi = in->xsize, he = in->ysize;
    T xp = (T)wi/2+0.2, yp = (T)he/2+0.2;
    out = new_image_double_RGB(wi, he);
    std::cout << "[" << std::flush;
    prepare_spline_RGB(in, spline_order);
    for (int y = 0; y < he; y++) {
        for (int x = 0; x < wi; x++) {
            /* do the correction for every pixel */
            T p1 = 0, p2 = 0;
            undistortPixel(p1, p2, paramsX, paramsY, x, y, xp, yp, degX, degY);
            pixel_double_RGB clr = interpolate_image_double_RGB(in, spline_order, p1, p2);
            clr.R = std::min(std::max(clr.R, 0.), 255.);
            clr.G = std::min(std::max(clr.G, 0.), 255.);
            clr.B = std::min(std::max(clr.B, 0.), 255.);
            out->Rdata[x+y*wi] = clr.R;
            out->Gdata[x+y*wi] = clr.G;
            out->Bdata[x+y*wi] = clr.B;
        }
        /* output progress */
        T percent = ((T)y / (T)he)*100;
        if (!(y % (int)(0.2*he))) std::cout << (int)percent+1 << "%" << std::flush;
        else if (!(y % (int)(0.04*he))) std::cout << "." << std::flush;
    }
    std::cout << "] " << std::flush;
    std::cout<<" done \n"<<std::endl;
}

/* Pop out one character from char array */
char popchar(char *c, int idx, int size)
{
    char res = c[idx];
    for (int i = idx; i < size; i++)
        if (i > idx) c[i-1] = c[i];
    return res;
}

/* Finds an index of coefTerm[] vector based on given x and y degrees. */
int coefIdx(int degree, int x, int y)
{
    int a1 = degree + 1;
    int n = std::abs(x+y-degree)+1;
    int an = x+y+1;
    int Sn = n * (a1 + an);
    Sn /= 2;
    return Sn-an+y;
}

/*----------------------------------------------------------------------------*/
/*                                    Main                                    */
/*----------------------------------------------------------------------------*/
// int main2(int argc, char **argv)
// {
// printf(
// "INFO parameters use: \nlength_threshold sampling_factor <poly_fname> <input.pgm> <output.pgm> \n");
// printf("=======================\n \n");
// int degX, degY;
// printf(" Reading the correction polynomial from file... \n");
// vector<double> poly_params_inv = read_poly<double>(argv[3], degX, degY);
// printf("done. \n");
// int spline_order = 5;
// image_double img = correct_image<double>(argv[4], argv[5], spline_order, poly_params_inv, degX,
// degY);
// image_RMSE<double>(int(atoi(argv[1])), double(atoi(argv[2])), img);
// free_image_double(img);
// return EXIT_SUCCESS;
// }

/*----------------------------------------------------------------------------*/

bool DistortionModule::distortionCorrect_RGB(image_double_RGB in, image_double_RGB &out,
                                             std::vector<double> &polynome, int order)
{
    if ((order+1)*(order+2)/2*2 != polynome.size()) return false;
    vector<double> poly(polynome.size());
    int size = poly.size();
    for (int i = poly.size()-1; i >= 0; --i)
        poly[i] = polynome[size-1-i];
    int spline_order = 5;
    correct_image_RGB<double>(in, out, spline_order, poly, order, order);
    return true;
}

bool DistortionModule::distortionCorrect(image_double in, image_double &out, std::vector<double> &polynome, int order)
{
    if ((order+1)*(order+2)/2*2 != polynome.size()) return false;
    vector<double> poly(polynome.size());
    int size = poly.size();
    for (int i = poly.size()-1; i >= 0; --i)
        poly[i] = polynome[size-1-i];
    int spline_order = 5;
    correct_image<double>(in, out, spline_order, poly, order, order);
    return true;
}
