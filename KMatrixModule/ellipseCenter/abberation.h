#ifndef ABBERATION_H
#define ABBERATION_H

#include <vector>
#include "image.h"
#include "commondefs.h"

typedef Bi<int> Pixel;
//class Pixel
//{
//public: int x, y;
//    Pixel(int X, int Y)
//    {
//        x = X, y = Y;
//    }
//};

class CCStats
{
public:
    int nPoints;
    double centerX, centerY, radius1, radius2;
    int perimeter; // need to calculate compactness measure of shape to eliminate noise
};
// Leman: const Pixel& p
int white_neighbors(const Pixel &p,const ImageGray<pixel::Byte> &img);

void extract_CCStats(std::vector<Pixel> &cc, CCStats &stats, const ImageGray<pixel::Byte> &img);

int extract_cc_(Pixel p, std::vector<Pixel> &cc, ImageGray<pixel::Byte> &img);

bool CC(std::vector<CCStats> &ccstats, const ImageGray<pixel::Byte> &imgbi, ImageRGB<pixel::Byte> &imgFeedback);

// finds corresponding circle center match among two channels
template<typename T>
int findMatch(T xg, T yg, std::vector<CCStats> &trgstats, T scale = 1)
{
    int minidx = -1;
    T mindist = 5; // look for center in radius of 10 pixels
    for (int i = 0; i < trgstats.size(); i++) {
        T eucdist
            = std::sqrt((scale*trgstats[i].centerX - xg)*(scale*trgstats[i].centerX - xg)
                        + (scale*trgstats[i].centerY - yg)*(scale*trgstats[i].centerY - yg));
        if (eucdist <= mindist) {
            mindist = eucdist;
            minidx = i;
        }
    }
    return minidx;
}

#endif
