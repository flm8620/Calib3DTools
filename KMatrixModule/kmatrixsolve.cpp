#ifndef KMATRIXSOLVE_CPP
#define KMATRIXSOLVE_CPP
#include "kmatrixsolve.h"
#include "main_centering.h"
#include "kmatrix_main.h"

#include "messager.h"
#include "image.h"
#include "matrix.h"
#include "Hmatrix.h"
#include "ellipse_operations.h"
#include "qimageconvert.h"
#include <QImage>
#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>
using namespace libNumerics;
static double cross2D(vector<double> v1, vector<double> v2)
{
    return v1(0)*v2(1)-v2(0)*v1(1);
}

static convexHull(matrix<double>&circles,
                  std::vector<vector<double> >&hullPoints, std::vector<int> &hullIndex){
    // convex hull
    // Gift wrapping algorithm with collinear case
    hullPoints.clear();
    hullIndex.clear();
    int nCircle = circles.ncol();
    double minX = 1e15;
    int minIdx = -1;
    // find the most left point
    for (int i = 0; i < nCircle; ++i) {
        if (circles(0, i) < minX) {
            minX = circles(0, i);
            minIdx = i;
        }
    }
    vector<double> p1, p2;
    int idxP1 = minIdx;
    p1 = circles.col(idxP1);
    hullPoints.push_back(p1);
    hullIndex.push_back(idxP1);
    double maxDot = -1e15;
    int idxP2;
    for (int j = 0; j < nCircle; ++j) {
        vector<double> p = circles.col(j);
        double dotValue = dot((p-p1)/std::sqrt((p-p1).qnorm()), vector<double>(0.0, -1.0));
        if (dotValue > maxDot) {
            maxDot = dotValue;
            idxP2 = j;
        }
    }
    p2 = circles.col(idxP2);

    int endIndex;

    vector<double> endPoint;
    do {
        hullPoints.push_back(p2);
        hullIndex.push_back(idxP2);
        vector<double> p1p2 = (p2-p1)/std::sqrt((p2-p1).qnorm());
        maxDot = -1e15;
        int idxNext = -1;
        for (int j = 0; j < nCircle; ++j) {
            vector<double> Sj = circles.col(j);
            double dotValue = dot((Sj-p2)/std::sqrt((Sj-p2).qnorm()), p1p2);
            if (dotValue > maxDot) {
                maxDot = dotValue;
                idxNext = j;
            }
        }
        p1 = p2;
        idxP1 = idxP2;
        idxP2 = idxNext;
        p2 = circles.col(idxNext);
    } while (idxP2 != minIdx);
}

static bool findCorner(matrix<double> &circles, int &idx1, int &idx2, int &idx3, int &idx4)
{
    std::vector<vector<double> > hullPoints;
    std::vector<int> hullIndex;
    convexHull(circles, hullPoints, hullIndex);
    if (hullPoints.size() < 4) {
        std::cout<<"hullPoint < 4. Something is wrong."<<std::endl;
        return false;
    }
    vector<double> p0, p1, p2, v1, v2;
    std::vector<std::pair<double, int> > maxFour(4, std::make_pair(-1.0e15, -1));
    p0 = hullPoints.back();
    p1 = hullPoints[0];
    p2 = hullPoints[1];
    for (int i = 0; i < hullPoints.size(); ++i) {
        v1 = p1-p0;
        v1 = v1/std::sqrt(v1*v1);
        v2 = p2-p1;
        v2 = v2/std::sqrt(v2*v2);
        double sineOfTurn = -cross2D(v2, v1);
        if (sineOfTurn > maxFour[0].first) {
            maxFour[0] = std::make_pair(sineOfTurn, i);
            std::sort(maxFour.begin(), maxFour.end());
        }
        p0 = p1;
        p1 = p2;
        if (i < hullPoints.size()-2)
            p2 = hullPoints[i+2];
        else
            p2 = hullPoints[0];
    }
    std::vector<int > maxFourIndex;
    for (int i = 0; i < 4; ++i)
        maxFourIndex.push_back(maxFour[i].second);
    std::sort(maxFourIndex.begin(), maxFourIndex.end());
    idx1 = hullIndex[maxFourIndex[0]];
    idx2 = hullIndex[maxFourIndex[1]];
    idx3 = hullIndex[maxFourIndex[2]];
    idx4 = hullIndex[maxFourIndex[3]];
    return true;
}

static bool sortCircles(matrix<double> &circles, int &nRow, int &nCol /*, QImage &qimage*/)
{
    int idx1, idx2, idx3, idx4;
    if (!findCorner(circles, idx1, idx2, idx3, idx4)) return false;
    /*  1 ---- 2
     *  |      |
     *  4 ---- 3
     */
    vector<double> corner1 = circles.col(idx1);
    vector<double> corner2 = circles.col(idx2);
    vector<double> corner3 = circles.col(idx3);
    vector<double> corner4 = circles.col(idx4);
    vector<double> line12 = corner2-corner1;
    vector<double> line23 = corner3-corner2;
    vector<double> line34 = corner4-corner3;
    vector<double> line41 = corner1-corner4;
    double l12 = std::sqrt(line12*line12);
    double l23 = std::sqrt(line23*line23);
    double l34 = std::sqrt(line34*line34);
    double l41 = std::sqrt(line41*line41);
    double tolerance = std::min(std::min(l12, l23), std::min(l34, l41))/50;
    line12 = line12/l12;
    line23 = line23/l23;
    line34 = line34/l34;
    line41 = line41/l41;
    int n12, n23, n34, n41;
    n12 = n23 = n34 = n41 = 0;
    int nCircle = circles.ncol();
    for (int i = 0; i < nCircle; ++i) {
        vector<double> p = circles.col(i);
        if (std::abs(cross2D(line12, p-corner1)) < tolerance) n12++;
        if (std::abs(cross2D(line23, p-corner2)) < tolerance) n23++;
        if (std::abs(cross2D(line34, p-corner3)) < tolerance) n34++;
        if (std::abs(cross2D(line41, p-corner4)) < tolerance) n41++;
    }
    if (n12 != n34 || n23 != n41) {
        libMsg::cout<<"Can't detect same number of circles for the opposite side,check the image"
                    <<libMsg::endl;
        return false;
    }
    if (n12*n23 != nCircle) {
        libMsg::cout<<"Total number of circle != nRow * nCol, check the image."<<libMsg::endl;
        return false;
    }
    nRow = n23;
    nCol = n12;
    int k = 0;
    matrix<double> XY_1(3, nCircle), XY_corner(2, 4), UV_corner(2, 4);
    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j) {
            XY_1(0, k) = j;
            XY_1(1, k) = i;
            XY_1(2, k) = 1;
            k++;
        }
    }
    // four points of corner
    XY_corner(0, 0) = 0;
    XY_corner(1, 0) = 0;
    XY_corner(0, 1) = nCol-1;
    XY_corner(1, 1) = 0;
    XY_corner(0, 2) = nCol-1;
    XY_corner(1, 2) = nRow-1;
    XY_corner(0, 3) = 0;
    XY_corner(1, 3) = nRow-1;
    // four corner observed
    UV_corner(0, 0) = corner1[0];
    UV_corner(1, 0) = corner1[1];
    UV_corner(0, 1) = corner2[0];
    UV_corner(1, 1) = corner2[1];
    UV_corner(0, 2) = corner3[0];
    UV_corner(1, 2) = corner3[1];
    UV_corner(0, 3) = corner4[0];
    UV_corner(1, 3) = corner4[1];

    matrix<double> H ;
    if(!solveHomography(XY_corner, UV_corner,H))
        return false;
    matrix<double> UV_1 = H * XY_1;
    matrix<double> UV(2, nCircle);
    for (int i = 0; i < nCircle; ++i) {
        UV(0, i) = UV_1(0, i)/UV_1(2, i);
        UV(1, i) = UV_1(1, i)/UV_1(2, i);
    }
// QPainter painter(&qimage);
// painter.setPen(Qt::red);
// for (int i = 0; i < nCircle; ++i) {
// double x=UV(0, i);
// double y=UV(1, i);
// QRectF rect(x-5, y-5, 11, 11);
// painter.fillRect(rect, Qt::red);
// }
// qimage.save("test.jpg",0,100);
    matrix<double> sortedCircle(2, nCircle);
    k = 0;
    std::vector<bool> picked(nCircle, false);
    for (int i = 0; i < nCircle; ++i) {
        vector<double> p = UV.col(i);
        double minDistance = 1e15;
        int minIdx = -1;
        for (int j = 0; j < nCircle; ++j) {
            if (picked[j]) continue;
            vector<double> q = circles.col(j);
            double squareDist = (q-p).qnorm();
            if (squareDist < minDistance) {
                minIdx = j;
                minDistance = squareDist;
            }
        }
        picked[minIdx] = true;
        sortedCircle(0, i) = circles(0, minIdx);
        sortedCircle(1, i) = circles(1, minIdx);
    }
    circles = sortedCircle;
    return true;
}

static void rotateGridLeft(matrix<double> &grid, int nRow, int nCol)
{
    // transpose the grid of circle
    // 1234  -> 2468
    // 5678     1357
    matrix<double> copy = grid;
    int k = 0;
    for (int x = 0; x < nCol; ++x) {
        for (int y = nRow-1; y >= 0; --y) {
            grid(0, k) = copy(0, x+y*nCol);
            grid(1, k) = copy(1, x+y*nCol);
            k++;
        }
    }
}

static void rotateGridRight(matrix<double> &grid, int nRow, int nCol)
{
    // transpose the grid of circle
    // 1234  -> 7531
    // 5678     8642
    matrix<double> copy = grid;
    int k = 0;
    for (int x = nCol-1; x >= 0; --x) {
        for (int y = 0; y < nRow; ++y) {
            grid(0, k) = copy(0, x+y*nCol);
            grid(1, k) = copy(1, x+y*nCol);
            k++;
        }
    }
}

bool KMatrixSolve::KMatrixSolver(std::vector<QImage> imageList, double &alpha, double &beta,
                                 double &gamma, double &u0, double &v0, double seperation,
                                 double radius)
{
    int nImage = imageList.size();
    std::vector<matrix<double> > Ellipse_centers;
    int nCircle;
    int nRow, nCol;
    for (int i = 0; i < nImage; ++i) {
        vector<double> x, y, r;
        {
            ImageGray<double> imageDouble;
            QImage2ImageDouble(imageList[i], imageDouble);
            detectEllipseCenters(imageDouble, x, y, r, 1.0);
        }
        if (i == 0) {
            nCircle = x.size();
        } else if (x.size() != nCircle) {
            libMsg::cout<<"The number of circles detected in Image_"<<i<<" is "<<x.size()
                        <<
                " , which is different from last image! Please check. Algorithm terminates"
                        <<libMsg::endl;
            return false;
        }
        Ellipse_centers.push_back(matrix<double>::zeros(2, nCircle));
        matrix<double> &centers = Ellipse_centers.back();
        for (int j = 0; j < nCircle; ++j) {
            centers(0, j) = x(j);
            centers(1, j) = y(j);
        }
        int nRow_i, nCol_i;
        if (!sortCircles(centers, nRow_i, nCol_i)) return false;
        if (i == 0) {
            nRow = nRow_i;
            nCol = nCol_i;
        } else {
            if (!(nRow == nRow_i && nCol == nCol_i)) {
                if (!(nCol == nRow_i && nRow == nCol_i)) {
                    libMsg::cout<<"Image_"<<i<<" doesn't have the same nRow and nCol as Image_0 !"
                                <<libMsg::endl;
                    return false;
                } else {
                    rotateGridLeft(centers, nRow_i, nCol_i);
                }
            }
        }
    }
    libMsg::cout<<"nRow="<<nRow<<" nCol="<<nCol<<libMsg::endl;
    std::vector<matrix<double> > S(nCircle);
    int cnt = 0;
    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j) {
            double XCi = (1.5+j*seperation);
            double YCi = (1.5+i*seperation);
            S[cnt] = getCircleMatrix(XCi, YCi, radius);
            cnt++;
        }
    }
    std::vector<matrix<double> > CHSlist;
    matrix<double> K;
    if (!extractK_real_double(S, Ellipse_centers, 0.0000000001, CHSlist, K))
        return false;

    alpha = K(0, 0);
    beta = K(1, 1);
    gamma = K(0, 1);
    u0 = K(0, 2);
    v0 = K(1, 2);
    return true;
}

#endif // KMATRIXSOLVE_CPP