#ifndef CAMCOMPARE_H
#define CAMCOMPARE_H


#include <vector>
typedef std::vector<std::pair<std::vector<double>,std::vector<double> > > CamSet;
namespace CamSolver {
    bool camCompare(const CamSet& camSet1,const CamSet& camSet2);
}
#endif // CAMCOMPARE_H
