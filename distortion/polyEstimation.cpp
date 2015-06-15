
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
#include "distortion.h"
#include "gaussian_convol_on_curve.h"
#include "straight_edge_points.h"
#include "ntuple_ll.h"
#include "pgm_io.h"
#include "misc.h"
#include "image.h"
#include "polyEstimation.h"
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
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

/*----------------------------------------------------------------------------*/
/*                                    Funcs                                    */
/*----------------------------------------------------------------------------*/
    using namespace libNumerics;


template <typename T>
static void read_images(DistortedLines<T>& distLines, const std::vector<image_char>& imageList, int length_thresh,int down_factor) {
    int w_tmp = 0, h_tmp = 0;
    ntuple_ll point_set,p;
    image_double image;
    //int length_thresh;
    //double down_factor,
    double x, y;
    int w,h;
    int total_nb_lines, total_threshed_nb_lines, threshed_nb_lines;
    ntuple_list convolved_pts;

    std::cout<<"There are"<<imageList.size()<<" input images. The minimal length of lines is set to "<<length_thresh<<std::endl;

    /* initialize memory */
    point_set = new_ntuple_ll(1);
    total_nb_lines = 0;
    total_threshed_nb_lines = 0;

    /* process each of the input images */
    for(int i = 0; i < imageList.size(); ++i){
        threshed_nb_lines = 0;

        /* open image, compute edge points, close it */
        std::cout<<"start convert "<<i<<"..."<<std::endl;
        image = new_image_double_from_image_char(imageList[i]);
        std::cout<<"done."<<std::endl;
        p = straight_edge_points(image,sigma,th_low,th_hi,min_length);
        std::cout<<"straightedgepoints"<<std::endl;
        w = image->xsize; h = image->ysize;
        if (i == 0) {w_tmp = w; h_tmp = h;}
        else assert(w == w_tmp && h == h_tmp);
        free_image_double(image);


        /* copy the points set in the new image to the global set of points */
        int count=0;
        for(int j=0; j<(int)p->size; j++) {
            if((int)p->list[j]->size > length_thresh) {
                add_ntuple_list(point_set, p->list[j]);
                p->list[j] = 0;
                count++;
            }
            else
                threshed_nb_lines += 1;
        }

        distLines.pushMemGroup(count);

        std::cout<<"For image"<<i<<", there are totally "<<p->size<<"lines detected and "<<threshed_nb_lines<<" of them are eliminated.\n"<<std::endl;
        total_nb_lines += p->size;
        total_threshed_nb_lines += threshed_nb_lines;
        free_ntuple_ll(p);
    }
    //distLines.pushMemGroup((int)point_set->size);
    int countL = 0;
    for(unsigned int i=0; i<point_set->size; i++) {
        /* Gaussian convolution and sub-sampling */
        std::cout<<"gaussian"<<std::endl;
        convolved_pts = gaussian_convol_on_curve(unit_sigma, Nsigma, resampling, eliminate_border, up_factor, down_factor, point_set->list[i]);

        /* Save points to DistortionLines structure */
        for(unsigned int j = 0; j < convolved_pts->size; j++) {
            x = convolved_pts->values[j*convolved_pts->dim];
            y = convolved_pts->values[j*convolved_pts->dim+1];
            distLines.pushPoint(countL,x,y); }
        countL++;
    }
    std::cout<<"Totally there are"<<total_nb_lines<<"lines detected and"<<total_threshed_nb_lines<< "of them are eliminated.\n"<<std::endl;
    /* free memory */
    free_ntuple_ll(point_set);
    free_ntuple_list(convolved_pts);
}

template <typename T>
static libNumerics::vector<T> incLMA(DistortedLines<T>& distLines, const int order, const int inc_order, T xp, T yp) {

    int sizexy = (order + 1) * (order + 2) / 2;
    vector<T> paramsX = vector<T>::zeros(sizexy); paramsX[sizexy-3] = 1;
    vector<T> paramsY = vector<T>::zeros(sizexy); paramsY[sizexy-2] = 1;
    T rmse = distLines.RMSE(paramsX, paramsY, order, order, xp, xp);
    T rmse_max = distLines.RMSE_max(paramsX, paramsY, order, order, xp, yp);
    std::cout<<"initial RMSE / maximum RMSE: "<<rmse<<" / "<<rmse_max<<" \n"<<std::endl;
    const int beginOrder = 3;
    vector<T> midParams(1);
    for (int i = beginOrder; i <= order; i=i+inc_order) {
        int sizebc = (i+1) * (i+2) / 2;
        vector<T> b = vector<T>::zeros(sizebc);
        vector<T> c = vector<T>::zeros(sizebc);
        vector<int> flagX = vector<int>::ones(sizebc);
        vector<int> flagY = vector<int>::ones(sizebc);
        flagX[sizebc-3] = flagX[sizebc-2] = flagX[sizebc-1] = 0;
        flagY[sizebc-2] = flagY[sizebc-3] = flagY[sizebc-1] = 0;
        if (i == beginOrder) {
            b[sizebc-3] = 1;
            c[sizebc-2] = 1;  }
        else {
            int sizebcOld = (i-inc_order+1) * (i-inc_order+2) / 2;
            for (int k = 0; k < sizebcOld; k++) {
                b[sizebc-sizebcOld+k] = midParams[k];
                c[sizebc-sizebcOld+k] = midParams[sizebcOld+k]; }
        }
        midParams = distLines.correctionLMA(b, c, flagX, flagY, i, i, xp, yp);
        rmse = distLines.RMSE(midParams.copy(0, sizebc-1), midParams.copyRef(sizebc, sizebc+sizebc-1), i, i, xp, yp);
        rmse_max = distLines.RMSE_max(midParams.copyRef(0, sizebc-1), midParams.copyRef(sizebc, sizebc+sizebc-1), i, i, xp, yp);
        std::cout<<"initial RMSE / maximum RMSE: "<<rmse<<" / "<<rmse_max<<" \n"<<std::endl;
    }
    std::cout<<"\n Iterative linear minimization step: \n"<<std::endl;
    T diff = 100;
    T prevRmse = 1e+16; /* infinity */
    vector<int> flagX = vector<int>::ones(sizexy);
    vector<int> flagY = vector<int>::ones(sizexy);
    flagX[sizexy-3] = flagX[sizexy-1] = flagX[sizexy-2] = 0;
    flagY[sizexy-2] = flagY[sizexy-1] = flagY[sizexy-3] = 0;
    vector<T> estParams(sizexy+sizexy);
    int iter = 0;
    while (diff > 0.001) {
        estParams = distLines.verification(midParams.copy(0, sizexy-1), midParams.copy(sizexy, sizexy+sizexy-1), flagX, flagY, order, order, xp, yp);
        midParams = estParams;
        rmse = distLines.RMSE(estParams.copy(0, sizexy-1), estParams.copyRef(sizexy, sizexy+sizexy-1), order, order, xp, yp);
        rmse_max = distLines.RMSE_max(estParams.copyRef(0, sizexy-1), estParams.copyRef(sizexy, sizexy+sizexy-1), order, order, xp, yp);
        std::cout<<"initial RMSE / maximum RMSE: "<<rmse<<" / "<<rmse_max<<" \n"<<std::endl;

        diff = fabs(prevRmse - rmse);
        prevRmse = rmse;
        iter++;
    }
    return estParams;
}

template <typename T>
static vector<T> polyInv(const vector<T>& poly_params, const int degX, const int degY, int wi, int he, T xp, T yp) {
    int sizex = (degX + 1) * (degX + 2) / 2;
    int sizey = (degY + 1) * (degY + 2) / 2;
    return getParamsInv(poly_params.copyRef(0, sizex-1), poly_params.copyRef(sizex, sizex+sizey-1), degX, degY, wi, he, xp, yp);;
}




bool PolyEstimation::polyEstime(const std::vector<image_char>& list,std::vector<double>& polynome,int order){
    unsigned int w,h;
    //check: same size for all image
    for(int i=0;i<list.size();++i){
        if(i==0){
            w=list[0]->xsize;
            h=list[0]->ysize;
        }else{
            if(w!=list[i]->xsize||h!=list[i]->ysize)
                return false;
        }
    }
    DistortedLines<double> distLines;
    read_images<double>(distLines, list, 700,60);

    /*int count=0;
     * for(int i=0;i<num;++i){
        QPainter painter(&list[i]);




        for(int j=0;j<distLines.nlines4Group[i];++j){
            double x1,y1,x2,y2;
            x1=distLines._line.at(count+j).x(0);
            y1=distLines._line.at(count+j).y(0);
            for(int k=1;k<distLines._line.at(count+j).sizeLine();++k){
                x2=distLines._line.at(count+j).x(k);
                y2=distLines._line.at(count+j).y(k);
                painter.setPen(Qt::green);
                painter.drawLine(x1,y1,x2,y2);
                painter.setPen(Qt::red);
                painter.drawPoint(x2,y2);
                x1=x2;y1=y2;
            }

        }
        count+=distLines.nlines4Group[i];
    }*/

    double xp = (double)w/2+0.2, yp = (double)h/2+0.2; /* +0.2 - to avoid integers */
    const int inc = 2; /* increment; only odd orders will be taken */
    vector<double> poly_params = incLMA <double> (distLines, order, inc, xp, yp);
    std::cout<<"incLMA"<<std::endl;
    /* Get an inverse polynomial */
    vector<double> poly_params_inv = polyInv<double>(poly_params, order, order, w, h, xp, yp);
    std::vector<double> polynomeBackward;
    polynome.clear();
    for(int i=0;i<poly_params_inv.size();++i){
        polynomeBackward.push_back(poly_params_inv[i]);
    }
    for(int i=polynomeBackward.size()-1;i>=0;--i){
        polynome.push_back(polynomeBackward[i]);
    }
    std::cout<<"polyInv"<<std::endl;
    return true;
}
