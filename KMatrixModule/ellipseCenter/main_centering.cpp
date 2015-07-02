#include "main_centering.h"

// #include <cstring>
// #include <cstdio>
// #include <cstdlib>

// #include <fstream>
// #include <sstream>
#include <iostream>
#include <cmath>

#include "messager.h"
#include "matrix.h"
#include "centers.h"
#include "abberation.h"

using namespace libNumerics;
void average_image(const ImageGray<double> &img, ImageGray<double> &img_avg)
{
    int w = img.xsize();
    int h = img.ysize();
    img_avg.resize(img.xsize(), img.ysize());
    for (int v = 1; v < h-1; v++) {
        for (int u = 1; u < w-1; u++) {
            double pix = img.pixel(u-1, v-1) + img.pixel(u, v-1) + img.pixel(u+1, v-1)
                         +img.pixel(u-1, v) + img.pixel(u, v) + img.pixel(u+1, v)
                         +img.pixel(u-1, v+1) + img.pixel(u, v+1) + img.pixel(u+1, v+1);
            img_avg.pixel(u, v) = pix/9;
        }
    }
}

template<typename T>
bool initial_tache(const ImageGray<double> &I, vector<T> &h, T &rayon, bool color, T x, T y)
{
    int COL_IMA = I.xsize();
    int LIG_IMA = I.ysize();
    int j = x;
    int i = y;
    int d = 2*rayon;
    if (2*d+1 > LIG_IMA)
        d = (LIG_IMA-1)/2;
    if (2*d+1 > COL_IMA)
        d = (COL_IMA-1)/2;
    if (i < d)
        i = d+1;
    if (i > LIG_IMA-1-d)
        i = LIG_IMA-2-d;
    if (j < d)
        j = d+1;
    if (j > COL_IMA-1-d)
        j = COL_IMA-2-d;
    int val_haut = 0;
    int val_bas = 255;
    for (int k = -d; k <= d; k++) {
        for (int l = -d; l <= d; l++) {
            T lum = I.pixel(j+l, i+k);
            if (lum > val_haut)
                val_haut = lum;
            else if (lum < val_bas)
                val_bas = lum;
        }
    }
    T seuil = 0;
    if (!color)
        seuil = val_bas + (val_haut - val_bas)/3 * 2;
    else if (color)
        seuil = val_bas + (val_haut - val_bas)/3;

    matrix<T> tab = matrix<T>::zeros(2*d+1, 2*d+1);
    int label = 1;
    // Leman:
    // tab:
    // 0000000000
    // 0000450000
    // 0003456000
    // 0023456700
    // 0123456780
    // 0123456780
    // 0023456700
    // 0003456000
    // 0000450000
    // 0000000000
    for (int k = -d+1; k <= d; k++) {
        for (int l = -d+1; l <= d-1; l++) {
            T lum = I.pixel(j+l, i+k);
            if (lum < seuil) {
                int imin = l;
                int imax = l+1;
                while ((I.pixel(j+imax, i+k) <= seuil) && (imax <= d-1))
                    imax++;
                int vallab = 0;
                for (int m = imin; m <= imax; m++) {
                    if (tab(k+d-1, m+d) != 0)
                        vallab = tab(k+d-1, m+d);
                }
                if (vallab == 0) {
                    vallab = label;
                    label++;
                }
                for (int m = imin; m <= imax; m++)
                    tab(k+d, m+d) = vallab;
                l = imax;
            }
        }
    }
    matrix<T> bary = matrix<T>::zeros(label, 4);
    for (int k = -d; k <= d; k++) {
        for (int l = -d; l <= d; l++) {
            if (tab(k+d, l+d) != 0) {
                T lum = I.pixel(j+l, i+k);
                bary(tab(k+d, l+d), 0) += (255-lum)*(j+l);
                bary(tab(k+d, l+d), 1) += (255-lum)*(i+k);
                bary(tab(k+d, l+d), 2) += (255-lum);
                bary(tab(k+d, l+d), 3)++;
            }
        }
    }
    int distmin = 100;
    int labelmin = 0;
    for (int k = 1; k < label; k++) {
        T dist = std::sqrt((bary(k, 0)/bary(k, 2)-x) * (bary(k, 0)/bary(k, 2)-x)
                           +(bary(k, 1)/bary(k, 2)-y) * (bary(k, 1)/bary(k, 2)-y));
        if (dist < distmin && bary(k, 3) > 25) { /* 25 =  surface min*/
            distmin = dist;
            labelmin = k;
        }
    }
    if (labelmin == 0) {
        libMsg::cout<<"region too small (<=25 pixels)\n"<<libMsg::endl;
        return false;
    }
    x = bary(labelmin, 0)/bary(labelmin, 2);
    y = bary(labelmin, 1)/bary(labelmin, 2);
    T sx2 = 0, sy2 = 0, sxy = 0, ss = 0;
    for (int k = -d; k <= d; k++) {
        for (int l = -d; l <= d; l++) {
            if (tab(k+d, l+d) == labelmin) {
                sx2 += (j+l-x)*(j+l-x);
                sy2 += (i+k-y)*(i+k-y);
                sxy += (i+k-y)*(j+l-x);
                ss++;
            }
        }
    }
    T lambda1 = ((sx2+sy2)/ss + std::sqrt(((sx2+sy2)*(sx2+sy2)+4*(sxy*sxy-sx2*sy2)))/ss)/2.0;
    T lambda2 = ((sx2*sy2-sxy*sxy)/(ss*ss))/lambda1;

    rayon = std::sqrt(lambda1)*2;
    h[0] = 1.0/rayon;                           /* lambda1      */
    h[1] = (std::sqrt(lambda1/lambda2))/rayon;  /* lambda2		*/
    h[2] = std::atan2(sx2/ss-lambda1, -sxy/ss);     /* alpha        */
    h[3] = x;           /* tu           */
    h[4] = y;           /* tv           */
    h[5] = 0.25;        /* rayon cercle 1       */
    h[6] = -2.0;        /* pente            */
    h[7] = 0.25;        /* rayon cercle 2       */
    h[8] = val_haut;    /* val_haut         */
    h[9] = val_bas;     /* val_bas          */
    h[10] = 1.0;    /* position step    */

    return true;
}

template<typename T>
vector<T> trgtDataCalc(ImageGray<double> &img_avg, T cx, T cy, T delta)
{
    int xbegin = cx+0.5-delta;
    int xend = cx+0.5+delta;
    int ybegin = cy+0.5-delta;
    int yend = cy+0.5+delta;
    int nerr = (yend-ybegin+1)*(xend-xbegin+1);
    vector<T> trgData = vector<T>::zeros(nerr);
    int wi = img_avg.xsize();
    int he = img_avg.ysize();
    int idx = 0;
    for (int v = ybegin; v <= yend; v++) {
        for (int u = xbegin; u <= xend; u++) {
            if (u >= 1 && u <= wi-2 && v >= 1 && v <= he-2)
                trgData[idx] = img_avg.pixel(u, v);
            else
                trgData[idx] = 255; // for 'tache noire'
            idx++;
        }
    }
    return trgData;
}

template<typename T>
bool centerLMA(const ImageGray<double> &sub_img, bool clr, T &centerX, T &centerY, vector<T> &Pout)
{
    ImageGray<double> img_avg;
    average_image(sub_img, img_avg);
    int w = sub_img.xsize();
    int h = sub_img.ysize();
    T cx = w/2, cy = h/2, radi = 0.4*w;
    vector<T> P(11);
    if (!initial_tache(sub_img, P, radi, clr, cx, cy)) return false;
    vector<T> trgData = trgtDataCalc<T>(img_avg, P[3], P[4], radi*2);
    LMTacheC<T> ellipseLMA(img_avg, P[3], P[4], radi*2, clr, w, h);
    T rmse = ellipseLMA.minimize(P, trgData, 0.001);
    T lambda1 = P[0];
    T lambda2 = P[1];
    T theta = P[2];
    centerX = P[3];
    centerY = P[4];
    Pout = P;
    return true;
}

template<typename T>
void takeSubImg(const ImageGray<double> &IMG, T cx, T cy, T radi, int &x0, int &y0,
                ImageGray<double> &img)
{
    int size = 2.5 * radi;
    int x1 = cx - 0.5*size, x2 = cx + 0.5*size;
    int y1 = cy - 0.5*size, y2 = cy + 0.5*size;
    x0 = x1;
    y0 = y1;
    if (y2-y1 != x2-x1)
        y2 = y1+x2-x1;
    img.resize(x2-x1, y2-y1);
    for (int i = 0; i < img.xsize(); i++) {
        for (int j = 0; j < img.ysize(); j++)
            if (IMG.pixelInside(x1+i, y1+j))
                img.pixel(i, j) = IMG.pixel(x1+i, y1+j);
            else
                img.pixel(i, j) = 255;
    }
}

template<typename T>
void binarization(ImageGray<T> &imgbi, const ImageGray<double> &img, T thre)
{
    int wi = img.xsize();
    int he = img.ysize();
    T color;
    for (int i = 0; i < wi; i++) {
        for (int j = 0; j < he; j++) {
            color = img.pixel(i, j);
            if (color <= thre) imgbi.pixel(i, j) = 0;
        }
    }
}

template<typename T>
void img_extremas(const ImageGray<double> &img, T &min, T &max)
{
    min = 255;
    max = 0;
    for (int i = 4; i < img.xsize()-4; i++) {
        for (int j = 4; j < img.ysize()-4; j++) {
            T clr = img.pixel(i, j);
            if (clr > max) max = clr;
            if (clr < min) min = clr;
        }
    }
}

template<typename T>
bool circle_redefine(const ImageGray<double> &img, vector<T> &x, vector<T> &y, const vector<T> &r,
                     int scale, bool clr, std::vector<vector<T> > &Pout)
{
    libMsg::cout<<"\nLMA center redefinition ... \n"<<libMsg::endl;
    int ntaches = x.size();
    double nextPercent = 0;
    Pout.clear();
    for (int i = 0; i < ntaches; i++) {
        int x0, y0;
        ImageGray<double> sub_img;
        takeSubImg(img, x[i], y[i], r[i], x0, y0, sub_img);
        vector<T> P;
        T cx = 0, cy = 0;
        if (!centerLMA<T>(sub_img, clr, cx, cy, P)) return false;
        // std::cout<<"correction: dx="<<scale*(x0 + cx)-x[i]<<" dy="<<scale*(y0 + cy)-y[i]<<std::endl;
        x[i] = scale*(x0 + cx);
        y[i] = scale*(y0 + cy);
        Pout.push_back(P);
        double percent = ((double)i / (double)ntaches)*100;
        if (percent > nextPercent) {
            libMsg::cout<<(int)nextPercent<<'%'<<libMsg::flush;
            nextPercent = (int(percent/10)+1)*10;
        }
    }
    libMsg::cout<<libMsg::endl;
    return true;
}

template<typename T>
bool keypnts_circle(const ImageGray<double> &img, vector<T> &x, vector<T> &y, vector<T> &r, T scale,
                    std::vector<vector<double> > &P)
{
    int wi = img.xsize(), he = img.ysize();

    T maxColor = 0;
    T minColor = 255;
    img_extremas(img, minColor, maxColor);
    BYTE thre = (BYTE)(0.5*(maxColor-minColor));

    ImageGray<BYTE> imgbi(wi, he, 255);
    binarization(imgbi, img, thre);
    // write_pgm_image_double(imgbiB, "rawdata/b.pgm");

    libMsg::cout<<"finding connected components... "<<libMsg::endl;
    std::vector<CCStats> ccstats;
    CC(ccstats, imgbi);
    libMsg::cout<<"number of connected components: [ "<<static_cast<unsigned>(ccstats.size())<<" ]"<<libMsg::endl;
    libMsg::cout<<"centers initialization is done "<<libMsg::endl;

    int ntaches = ccstats.size();
    x = x.ones(ntaches);
    y = y.ones(ntaches);
    r = r.ones(ntaches);
    for (int i = 0; i < ntaches; i++) {
        x[i] = ccstats[i].centerX;
        y[i] = ccstats[i].centerY;
        r[i] = (ccstats[i].radius1+ccstats[i].radius2)/2;
    }
    bool clr = 0;
    if (!circle_redefine(img, x, y, r, scale, clr, P)) return false;
    return true;
}

bool detectEllipseCenters(const ImageGray<double> &img, vector<double> &x, vector<double> &y,
                          vector<double> &r, std::vector<vector<double> > &P, double scale)
{
    if (!keypnts_circle<double>(img, x, y, r, scale, P)) return false;
    return true;
}
