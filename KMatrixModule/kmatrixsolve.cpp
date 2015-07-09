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
#include <QPainter>
#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>
using namespace libNumerics;
static double cross2D(vector<double> v1, vector<double> v2)
{
    return v1(0)*v2(1)-v2(0)*v1(1);
}

static bool convexHull(matrix<double> &circles, std::vector<vector<double> > &hullPoints,
                       std::vector<int> &hullIndex)
{
    // convex hull
    // Gift wrapping algorithm with collinear case
    hullPoints.clear();
    hullIndex.clear();
    int nCircle = circles.ncol();
    if (nCircle <= 0) return false;
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
    return true;
}

static bool findCorner(matrix<double> &circles, int &idx1, int &idx2, int &idx3, int &idx4)
{
    std::vector<vector<double> > hullPoints;
    std::vector<int> hullIndex;
    if (!convexHull(circles, hullPoints, hullIndex)) return false;
    if (hullPoints.size() < 4) {
        libMsg::cout<<"hullPoint < 4. Something is wrong."<<libMsg::endl;
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

    matrix<double> H;
    if (!solveHomography(XY_corner, UV_corner, H))
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

bool KMatrixSolve::KMatrixSolver(std::vector<QImage> &imageList, std::vector<QImage> &feedbackList,
                                 double &alpha, double &beta, double &u0, double &v0, double &gamma,
                                 double seperation, double radius)
{
    int nImage = imageList.size();
    std::vector<matrix<double> > Ellipse_centers;
    int nCircleOf1stImage;
    int nRow, nCol;
    feedbackList.clear();
    // go through all image to check validity
    libMsg::cout<<"Step 1: check all images to know whether they all have the same circle points"
                <<libMsg::endl;
    libMsg::cout
        <<
        "For the feedback images:\n"
        "\tBlack region : detected circle\n"
        "\tRed region : not a circle\n"
        "\tGreen region : too small"
        "\tBlue region : filtered\n"
        "Number beside circle:\n\t\tindex\n\t\tindex after sort\n\t\terror RMSE"
        <<libMsg::endl<<libMsg::endl;
    for (int i = 0; i < nImage; ++i) {
        libMsg::cout<<"Image "<<i+1<<'/'<<nImage<<libMsg::endl;
        vector<double> x, y, r;
        ImageRGB<BYTE> imgFeedback;
        {
            ImageGray<double> imageDouble;
            QImage2ImageDouble(imageList[i], imageDouble);
            if (!detectEllipseCenters_noRefine(imageDouble, imgFeedback, x, y, r)) return false;
        }
        matrix<double> centers(2, x.size());
        for (int j = 0; j < x.size(); ++j) {
            centers(0, j) = x(j);
            centers(1, j) = y(j);
        }
        // feedback img
        QImage image;
        ImageByteRGB2QColorImage(imgFeedback, image);
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        for (int j = 0; j < x.size(); j++) {
            double xx = x(j);
            double yy = y(j);
            painter.setPen(Qt::red);
            painter.resetTransform();
            painter.translate(xx, yy);
            painter.drawText(QRectF(5, 5, 30, 30), QString::number(j));
        }
        feedbackList.push_back(image);
        if (i == 0) {
            nCircleOf1stImage = x.size();
        } else if (x.size() != nCircleOf1stImage) {
            libMsg::cout<<"The number of circles detected in Image_"<<i<<" is "<<x.size()
                        <<
                " , which is different from last image! Please check. Algorithm terminates"
                        <<libMsg::endl;
            return false;
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
                }
            }
        }
    }
    // refine the circle centers
    libMsg::cout<<"\n\nStep 2: refine circle centers"<<libMsg::endl<<libMsg::endl;
    feedbackList.clear();
    for (int i = 0; i < nImage; ++i) {
        libMsg::cout<<"\nImage "<<i+1<<'/'<<nImage<<libMsg::endl;
        vector<double> x, y, r;
        ImageRGB<BYTE> imgFeedback;
        std::vector<vector<double> > P;
        {
            ImageGray<double> imageDouble;
            QImage2ImageDouble(imageList[i], imageDouble);
            if (!detectEllipseCenters(imageDouble, imgFeedback, x, y, r, P, 1.0)) return false;
        }
        //P[0] = 1.0/rayon;                            lambda1
        //P[1] = (std::sqrt(lambda1/lambda2))/rayon;   lambda2
        //P[2] = std::atan2(sx2/ss-lambda1, -sxy/ss);  alpha
        //P[3] = x;            tu
        //P[4] = y;            tv
        //P[5] = 0.25;         rayon cercle 1
        //P[6] = -2.0;         pente
        //P[7] = 0.25;         rayon cercle 2
        //P[8] = val_haut;     val_haut
        //P[9] = val_bas;      val_bas
        //P[10] = 1.0;         position step
        //P[11] = RMSE         error
        Ellipse_centers.push_back(matrix<double>::zeros(2, x.size()));
        matrix<double> &centers = Ellipse_centers.back();
        for (int j = 0; j < x.size(); ++j) {
            centers(0, j) = x(j);
            centers(1, j) = y(j);
        }
        // draw feedback
        QImage image;
        ImageByteRGB2QColorImage(imgFeedback, image);
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        for (int j = 0; j < x.size(); j++) {
            double xx = x(j);
            double yy = y(j);
            double r1 = 1/P[j](0);
            double r2 = 1/P[j](1);
            double alpha = P[j](2);
            double rmse = P[j](11);
            painter.setPen(Qt::blue);
            painter.resetTransform();
            painter.translate(xx, yy);
            painter.drawText(QRectF(5, 5, 30, 30), QString::number(j));
            if(rmse>4.0)
                painter.setPen(Qt::red);
            painter.drawText(QRectF(5, 25, 50, 30),QString::number(rmse));

            painter.rotate(-alpha/3.14159265358979323*180);
            painter.setPen(Qt::red);
            painter.drawLine(QPointF(-r1, 0), QPointF(r1, 0));
            painter.setPen(Qt::green);
            painter.drawLine(QPointF(0, -r2), QPointF(0, r2));
        }
        feedbackList.push_back(image);
        // end draw feedback
        if (i == 0) {
            nCircleOf1stImage = x.size();
        } else if (x.size() != nCircleOf1stImage) {
            libMsg::cout<<"The number of circles detected in Image_"<<i<<" is "<<x.size()
                        <<
                " , which is different from last image! Please check. Algorithm terminates"
                        <<libMsg::endl;
            return false;
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
    // draw feedback for sorted index
    for (int i = 0; i < nImage; ++i) {
        QPainter painter(&feedbackList[i]);
        painter.setRenderHint(QPainter::Antialiasing);
        for (int j = 0; j < Ellipse_centers[i].ncol(); j++) {
            double xx = Ellipse_centers[i](0, j);
            double yy = Ellipse_centers[i](1, j);
            painter.setPen(Qt::green);
            painter.resetTransform();
            painter.translate(xx, yy+10);
            painter.drawText(QRectF(5, 5, 30, 30), QString::number(j));
        }
    }
    libMsg::cout<<"nRow="<<nRow<<" nCol="<<nCol<<libMsg::endl;
    std::vector<matrix<double> > S(nCircleOf1stImage);
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
    u0 = K(0, 2);
    v0 = K(1, 2);
    gamma = K(0, 1);
    return true;
}

#endif // KMATRIXSOLVE_CPP
