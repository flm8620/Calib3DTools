#include "abberation.h"

#include <iostream>

#include "messager.h"
int white_neighbors(const Pixel &p, const ImageGray<BYTE> &img)
{
    int nn = 0;
    Pixel p1(p.x-1, p.y);
    if (p1.x >= 0 && p1.x < img.xsize() && p1.y >= 0 && p1.y < img.ysize()) {
        if (img.pixel(p1.x, p1.y) == 255)
            nn++;
    } else {
        nn++;
    }

    Pixel p2(p.x+1, p.y);
    if (p2.x >= 0 && p2.x < img.xsize() && p2.y >= 0 && p2.y < img.ysize()) {
        if (img.pixel(p2.x, p2.y) == 255)
            nn++;
    } else {
        nn++;
    }

    Pixel p3(p.x, p.y-1);
    if (p3.x >= 0 && p3.x < img.xsize() && p3.y >= 0 && p3.y < img.ysize()) {
        if (img.pixel(p3.x, p3.y) == 255)
            nn++;
    } else {
        nn++;
    }

    Pixel p4(p.x, p.y+1);
    if (p4.x >= 0 && p4.x < img.xsize() && p4.y >= 0 && p4.y < img.ysize()) {
        if (img.pixel(p4.x, p4.y) == 255)
            nn++;
    } else {
        nn++;
    }

    if (nn > 0) nn = 1;
    return nn;
}

void extract_CCStats(std::vector<Pixel> &cc, CCStats &stats, const ImageGray<BYTE> &img)
{
    stats.nPoints = cc.size();
    stats.perimeter = 0;
    double meanX = 0, meanY = 0;
    double minX = img.xsize(), minY = img.ysize(), maxX = 0, maxY = 0;
    for (int i = 0; i < cc.size(); i++) {
        meanX += cc[i].x;
        meanY += cc[i].y;
        if (cc[i].x > maxX) maxX = cc[i].x;
        if (cc[i].x < minX) minX = cc[i].x;
        if (cc[i].y > maxY) maxY = cc[i].y;
        if (cc[i].y < minY) minY = cc[i].y;
        stats.perimeter += white_neighbors(Pixel(cc[i].x, cc[i].y), img);
    }
    stats.centerX = meanX / cc.size();
    stats.centerY = meanY / cc.size();
    stats.radius1 = 0.5 * (maxX - minX);
    stats.radius2 = 0.5 * (maxY - minY);
}

int extract_cc_(Pixel p, std::vector<Pixel> &cc, ImageGray<BYTE> &img,int i,int j)
{
    std::stack<Pixel> s;
    BYTE *pColor;
    if (img.pixelInside(p.x, p.y))
        pColor = &img.pixel(p.x, p.y);
    else
        return 0;
    //std::cout<<i<<' '<<j<<"in"<<std::endl;
    while (*pColor == 0 || !s.empty())
    {

        if (*pColor == 0) {
            cc.push_back(p);
            *pColor = 255;
            s.push(Pixel(p.x+1, p.y));
            s.push(Pixel(p.x-1, p.y));
            s.push(Pixel(p.x, p.y+1));
            s.push(Pixel(p.x, p.y-1));
        }
        p = s.top();
        s.pop();
        if (img.pixelInside(p.x, p.y))
            pColor = &img.pixel(p.x, p.y);
        else
            *pColor = 255;
    }
    //std::cout<<"out"<<std::endl;
    return cc.size();
}

bool CC(std::vector<CCStats> &ccstats, const ImageGray<BYTE> &imgbi, ImageRGB<BYTE> &imgFeedback)
{
    ImageGray<BYTE> img_copy(imgbi);
    std::vector<Pixel> firstPixels;
    double meansize = 0;
    std::cout<<img_copy.xsize()<<' '<<img_copy.ysize()<<std::endl;
    for (int i = 0; i < imgbi.xsize(); i++) {

        for (int j = 0; j < imgbi.ysize(); j++) {
            std::vector<Pixel> ccC;
            CCStats stats;

            int npix = extract_cc_(Pixel(i, j), ccC, img_copy,i,j);

            if (npix > 180) {
                extract_CCStats(ccC, stats, imgbi);
                double compactness = 4*PI*stats.nPoints / (stats.perimeter*stats.perimeter);
                // !!compactness < 1.3 is not a good limit! I changed to 1.5 -Leman
                if (std::min(stats.radius1,
                             stats.radius2) > 8 && compactness < 1.5 && compactness > 0.7) {
                    ccstats.push_back(stats);
                    firstPixels.push_back(Pixel(i, j));
                    meansize += stats.nPoints;
                    // draw Feedback
                    for (int k = 0; k < ccC.size(); ++k) {
                        Pixel p = ccC[k];
                        // black means detected
                        imgFeedback.pixel_R(p.x, p.y) = 0;
                        imgFeedback.pixel_G(p.x, p.y) = 0;
                        imgFeedback.pixel_B(p.x, p.y) = 0;
                    }
                } else {
                    // draw Feedback
                    for (int k = 0; k < ccC.size(); ++k) {
                        Pixel p = ccC[k];
                        // red means it's not a circle
                        imgFeedback.pixel_R(p.x, p.y) = 150;
                        imgFeedback.pixel_G(p.x, p.y) = 0;
                        imgFeedback.pixel_B(p.x, p.y) = 0;
                    }
                }
            } else {
                // draw Feedback
                for (int k = 0; k < ccC.size(); ++k) {
                    Pixel p = ccC[k];
                    // green means it's too small
                    imgFeedback.pixel_R(p.x, p.y) = 0;
                    imgFeedback.pixel_G(p.x, p.y) = 150;
                    imgFeedback.pixel_B(p.x, p.y) = 0;
                }
            }
        }
        double percent = ((double)i / (double)imgbi.xsize())*100;
        if (!(i % (int)(0.2*imgbi.xsize()+1)))
            libMsg::cout<<(int)(percent+1)<<'%'<<libMsg::flush;
        else if (!(i % (int)(0.04*imgbi.xsize()+1)))
            libMsg::cout<<'.'<<libMsg::flush;
    }
    libMsg::cout<<libMsg::endl;

    if (ccstats.size() == 0) {
        libMsg::cout<<"Nothing interesting found in this image. Please check.";
        return false;
    }
    // retrieve min_size and max_size to build a size histogram
    int max_val = 0;
    int rad_thre = 7;
    for (int i = 0; i < ccstats.size(); i++) {
        if (ccstats[i].nPoints > max_val)
            max_val = ccstats[i].nPoints;
    }

    std::vector<int> hist(max_val);
    std::vector<std::stack<int> > hist_stack(max_val); // to keep indeces of all the circles for given size
    // run through all the sizes and build frequency histogram
    for (int i = 0; i < ccstats.size(); i++) {
        int val = ccstats[i].nPoints-1;
        hist[val]++;
        hist_stack[val].push(i);
    }

    meansize /= ccstats.size();
    int commonsize = meansize;
    libMsg::cout<<"Average area of region: "<<meansize<<" pixels"<<libMsg::endl;
    libMsg::cout<<"Max area of region: "<<max_val<<" pixels"<<libMsg::endl;
    libMsg::cout<<"Region found before filter: [ "<<ccstats.size()<<" ]"<<libMsg::endl;
    /*
     *  frequency
     *   ^
     *   |
     *   |
     *   |               |
     *   |               | |           larger than zerogap
     *   |               | |           so we ignore A and B
     *   |   <--->  | ||||| |   |    <--------------->
     *   |  A     | | ||||| ||  |   |                 B
     *   ----------------------------------------------------> size
     *   0               ^                                10000
     *                   |
     *              average size
     *   negative   <---- ---->  positive
     *   direction               direction
     */
    // collect the inliers in positive direction from commonsize idx

    int zerosgap = meansize/5;
    int count = 0;
    int flag = zerosgap;
    std::vector<int> inliers(ccstats.size());
    while (flag != 0 && commonsize+count < hist.size()) {
        int hist_idx = commonsize + count;
        int onesizecircles = hist[hist_idx];
        if (onesizecircles == 0) {
            flag--;
        } else {
            while (!hist_stack[hist_idx].empty()) {
                inliers[hist_stack[hist_idx].top()] = 1;
                // inliers.push(hist_stack[hist_idx].top());
                hist_stack[hist_idx].pop();
            }
            flag = zerosgap;
        }
        count++;
    }

    // collect the inliers in negative direction from commonsize idx
    count = -1;
    flag = zerosgap;
    while (flag != 0 && commonsize+count >= 0) {
        int hist_idx = commonsize + count;
        int onesizecircles = hist[hist_idx];
        if (onesizecircles == 0) {
            flag--;
        } else {
            while (!hist_stack[hist_idx].empty()) {
                inliers[hist_stack[hist_idx].top()] = 1;
                hist_stack[hist_idx].pop();
            }
            flag = zerosgap;
        }
        count--;
    }

    std::vector<CCStats> erasedCCStats;
    std::vector<int> outliersIdx;
    int idx = 0;
    while (idx < ccstats.size()) {
        if (inliers[idx] == 0) {
            erasedCCStats.push_back(ccstats[idx]);
            outliersIdx.push_back(idx);
            ccstats.erase(ccstats.begin() + idx);
            inliers.erase(inliers.begin() + idx);
        } else {
            idx++;
        }
    }
    libMsg::cout<<"Region found after filter: [ "<<ccstats.size()<<" ]"<<libMsg::endl;
    if (erasedCCStats.size() > 0) {
        libMsg::cout<<"Erased circles:"<<libMsg::endl;
        ImageGray<BYTE> img_copy2(imgbi);
        for (int i = 0; i < erasedCCStats.size(); ++i) {
            CCStats &stats = erasedCCStats[i];
            libMsg::cout<<"circle "<<i<<libMsg::endl;
            libMsg::cout<<"\tarea: "<<stats.nPoints<<libMsg::endl;
            libMsg::cout<<"\tcenter: "<<stats.centerX<<", "<<stats.centerY<<libMsg::endl;
            int index = outliersIdx[i];
            Pixel first = firstPixels[index];
            std::vector<Pixel> ccC;
            extract_cc_(first, ccC, img_copy2,-1,-1);
            for (int k = 0; k < ccC.size(); ++k) {
                Pixel p = ccC[k];
                // blue means filtered
                imgFeedback.pixel_R(p.x, p.y) = 0;
                imgFeedback.pixel_G(p.x, p.y) = 0;
                imgFeedback.pixel_B(p.x, p.y) = 150;
            }
        }
    }
    return true;
}
