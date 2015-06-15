#ifndef DISTRORTION_H
#define DISTRORTION_H
#include <QtCore>
#include <QList>
#include <cmath>


/* class Distortion */
/*
  for example maxOrder=3:
  QList<QPair<double,double> >:
  xParam           yParam

  a0 * x^0*y^0    b0 * x^0*y^0

  a1 * x^1*y^0    b1 * x^1*y^0
  a2 * x^0*y^1    b2 * x^0*y^1

  a3 * x^2*y^0    b3 * x^2*y^0
  a4 * x^1*y^1    b4 * x^1*y^1
  a5 * x^0*y^2    b5 * x^0*y^2

  a6 * x^3*y^0    b6 * x^3*y^0
  a7 * x^2*y^1    b7 * x^2*y^1
  a8 * x^1*y^2    b8 * x^1*y^2
  a9 * x^0*y^3    b9 * x^0*y^3

  numTotal = 10 = (2+maxOrder) * (1+maxOrder) / 2
 */
class Distortion
{
public:
    Distortion(){_size=0;_maxOrder=-1;}

    int maxOrder()const{return this->_maxOrder;}
    void setMaxOrder(int maxOrder){
        _data.clear();
        if(maxOrder<0){this->_maxOrder=-1;return;}
        this->_maxOrder=maxOrder;
        this->_size=(2+maxOrder)*(1+maxOrder)/2;
        for(int i=0;i<_size;++i)_data.append(QPair<double,double>(0,0));
    }
    int size()const{return _size;}
    // degX degY and index
    /*     X 0 1 2 3
     *   Y
     *   0   0 1 3 6
     *   1   2 4 7
     *   2   5 8  idx
     *   3   9
     */
    void XYfromIdx(int idx,int &degX,int &degY)const{
        int j=std::ceil((std::sqrt(9+8*idx)-1)/2);
        degY=idx-(j-1)*j/2;
        degX=j-1-degY;
        //e.g. idx=6, a6 -> x^3*y^0, so x=3 y=0
    }
    int idxFromXY(int degX,int degY)const{
        return (1+degX+degY)*(degX+degY)/2+degY;
        //e.g. x=3,y=0, x^3*y^0 -> a6, so idx=6
    }
    void setXParam(double value,int degX,int degY){
        _data[idxFromXY(degX,degY)].first=value;
    }
    void setYParam(double value,int degX,int degY){
        _data[idxFromXY(degX,degY)].second=value;
    }
    void setXParam(double value,int idx){
        _data[idx].first=value;
    }
    void setYParam(double value,int idx){
        _data[idx].second=value;
    }
    int getXParam(int degX,int degY)const{
        return _data[idxFromXY(degX,degY)].first;
    }
    int getYParam(int degX,int degY)const{
        return _data[idxFromXY(degX,degY)].second;
    }
    double getXParam(int idx)const{
        return _data[idx].first;
    }
    double getYParam(int idx)const{
        return _data[idx].second;
    }
    void clear(){
        _data.clear();
        _maxOrder=-1;
    }

private:
    QList<QPair<double,double> > _data;
    int _maxOrder;
    int _size;
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



