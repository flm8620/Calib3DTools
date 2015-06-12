#ifndef DISTRORTION_H
#define DISTRORTION_H
#include <QtCore>
#include <QList>
#include <cmath>
class Distortion : public QList<double>
{
public:
    int getMaxOrder(){return this->maxOrder;}
    void setMaxOrder(int maxOrder){
        this->maxOrder=maxOrder;
        this->numTotal=(2+maxOrder)*(1+maxOrder)/2;
        this->clear();
        for(int i=0;i<numTotal;++i)this->append(0.0);
    }
    int getTotalNum(){return numTotal;}
    void XYfromIdx(int idx,int &degX,int &degY)const{
        int n=numTotal-idx-1;
        int j=std::ceil((std::sqrt(9+8*n)-1)/2)-1;
        degX=n-(j+1)*j/2;
        degY=j-degX;
        //XYfromIndex:
        //for example, idx=6, a6 -> x^0*y^2, so x=0 y=0
    }

private:
    int maxOrder;
    int numTotal;
    //for example maxOrder=3:
    //QList<double>:
    // a0 * x^3*y^0
    // a1 * x^2*y^1
    // a2 * x^1*y^2
    // a3 * x^0*y^3
    //
    // a4 * x^2*y^0
    // a5 * x^1*y^1
    // a6 * x^0*y^2
    //
    // a7 * x^1*y^0
    // a8 * x^0*y^1
    //
    // a9 * x^0*y^0
    // numTotal = 10 = (2+maxOrder) * (1+maxOrder) / 2
};
Q_DECLARE_METATYPE(Distortion)

class DistortionContainer
{
public:
    virtual Distortion getDistortion_threadSafe() =0;
    virtual void saveDistortion_threadSafe(const Distortion& value) =0;
    virtual bool isEmpty() =0;
};

#endif // DISTRORTION_H



