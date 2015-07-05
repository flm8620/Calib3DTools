#include "distortion.h"
#include <cmath>
using concurrent::ReadLock;
using concurrent::WriteLock;


Distortion::Distortion()
{
}

bool Distortion::isEmpty() const
{
    ReadLock locker(this->rwLock);
    return this->value._size == 0;
}

int Distortion::maxOrder() const
{
    ReadLock locker(this->rwLock);
    return this->value._maxOrder;
}

void Distortion::setMaxOrder(int maxOrder)
{
    {
        WriteLock locker(this->rwLock);
        this->value.setMaxOrder(maxOrder);
    }
    this->_dataChangedEvent.trigger();
}

int Distortion::size() const
{
    ReadLock locker(this->rwLock);
    return this->value._size;
}

void Distortion::XYfromIdx(int idx, int &degX, int &degY)
{
    int j = std::ceil((std::sqrt(9+8*idx)-1)/2);
    degY = idx-(j-1)*j/2;
    degX = j-1-degY;
}

int Distortion::idxFromXY(int degX, int degY)
{
    return (1+degX+degY)*(degX+degY)/2+degY;
}

DistortionValue Distortion::getValue() const
{
    ReadLock locker(this->rwLock);
    return this->value;
}

bool Distortion::setValue(const DistortionValue &value)
{
    {
        WriteLock locker(this->rwLock);
        if (!value.isValid())
            return false;
        this->value = value;
    }
    this->_dataChangedEvent.trigger();
    return true;
}

bool Distortion::setXParamVector(const std::vector<double> &xVector)
{
    {
        WriteLock locker(this->rwLock);
        if (xVector.size() != this->value._size) return false;
        for (int i = 0; i < value._size; ++i)
            this->value._XYData.at(i).first = xVector[i];
    }
    this->_dataChangedEvent.trigger();
    return true;
}

bool Distortion::setYParamVector(const std::vector<double> &yVector)
{
    {
        WriteLock locker(rwLock);
        if (yVector.size() != this->value._size) return false;
        for (int i = 0; i < value._size; ++i)
            this->value._XYData.at(i).second = yVector[i];
    }
    this->_dataChangedEvent.trigger();
    return true;
}

void Distortion::setXParam(double value, int degX, int degY)
{
    {
        WriteLock locker(rwLock);
        this->value._XYData[idxFromXY(degX, degY)].first = value;
    }
    this->_dataChangedEvent.trigger();
}

void Distortion::setYParam(double value, int degX, int degY)
{
    {
        WriteLock locker(rwLock);
        this->value._XYData[idxFromXY(degX, degY)].second = value;
    }
    this->_dataChangedEvent.trigger();
}

void Distortion::setXParam(double value, int idx)
{
    {
        WriteLock locker(rwLock);
        this->value._XYData[idx].first = value;
    }
    this->_dataChangedEvent.trigger();
}

void Distortion::setYParam(double value, int idx)
{
    {
        WriteLock locker(rwLock);
        this->value._XYData[idx].second = value;
    }
    this->_dataChangedEvent.trigger();
}

int Distortion::xParam(int degX, int degY) const
{
    ReadLock locker(rwLock);
    return this->value._XYData[idxFromXY(degX, degY)].first;
}

int Distortion::yParam(int degX, int degY) const
{
    ReadLock locker(rwLock);
    return this->value._XYData[idxFromXY(degX, degY)].second;
}

double Distortion::xParam(int idx) const
{
    ReadLock locker(rwLock);
    return this->value._XYData[idx].first;
}

double Distortion::yParam(int idx) const
{
    ReadLock locker(rwLock);
    return this->value._XYData[idx].second;
}

void Distortion::clear()
{
    this->setMaxOrder(-1);
}

DistortionValue::DistortionValue()
{
    this->setMaxOrder(-1);
}

void DistortionValue::setMaxOrder(int maxOrder)
{
    this->_XYData.clear();
    if (maxOrder < 0) {
        this->_maxOrder = -1;
        this->_size = 0;
        return;
    }
    this->_maxOrder = maxOrder;
    this->_size = (2+maxOrder)*(1+maxOrder)/2;
    for (int i = 0; i < this->_size; ++i) this->_XYData.push_back(std::make_pair(0.0, 0.0));
}

bool DistortionValue::isValid() const
{
    return _size == this->sizeFromMaxOrder(_maxOrder) && _XYData.size() == _size;
}
