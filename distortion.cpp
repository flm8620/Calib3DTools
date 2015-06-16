#include "distortion.h"
#include <cmath>
Distortion::Distortion(QObject *parent) : QObject(parent)
{
}

bool Distortion::isEmpty()
{
    return this->value._size == 0;
}

int Distortion::maxOrder() const
{
    QReadLocker locker(&this->rwLock);
    return this->value._maxOrder;
}

void Distortion::setMaxOrder(int maxOrder)
{
    {
        QWriteLocker locker(&this->rwLock);
        this->value.setMaxOrder(maxOrder);
    }
    emit dataChanged();
}

int Distortion::size() const
{
    QReadLocker locker(&this->rwLock);
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
    QReadLocker locker(&this->rwLock);
    return this->value;
}

bool Distortion::setValue(const DistortionValue &value)
{
    if (value.isValid()) {
        this->rwLock.lockForWrite();
        this->value = value;
        this->rwLock.unlock();
        emit dataChanged();
        return true;
    }
    return false;
}

bool Distortion::setXParamVector(const std::vector<double> &xVector)
{
    {
        QWriteLocker locker(&this->rwLock);
        if (xVector.size() != this->value._size) return false;
        for (int i = 0; i < value._size; ++i)
            this->value._XYData.at(i).first = xVector[i];
    }
    emit dataChanged();
    return true;
}

bool Distortion::setYParamVector(const std::vector<double> &yVector)
{
    {
        QWriteLocker locker(&rwLock);
        if (yVector.size() != this->value._size) return false;
        for (int i = 0; i < value._size; ++i)
            this->value._XYData.at(i).second = yVector[i];
    }
    emit dataChanged();
    return true;
}

void Distortion::setXParam(double value, int degX, int degY)
{
    {
        QWriteLocker locker(&rwLock);
        this->value._XYData[idxFromXY(degX, degY)].first = value;
    }
    emit dataChanged();
}

void Distortion::setYParam(double value, int degX, int degY)
{
    {
        QWriteLocker locker(&rwLock);
        this->value._XYData[idxFromXY(degX, degY)].second = value;
    }
    emit dataChanged();
}

void Distortion::setXParam(double value, int idx)
{
    {
        QWriteLocker locker(&rwLock);
        this->value._XYData[idx].first = value;
    }
    emit dataChanged();
}

void Distortion::setYParam(double value, int idx)
{
    {
        QWriteLocker locker(&rwLock);
        this->value._XYData[idx].second = value;
    }
    emit dataChanged();
}

int Distortion::xParam(int degX, int degY) const
{
    QReadLocker locker(&rwLock);
    return this->value._XYData[idxFromXY(degX, degY)].first;
}

int Distortion::yParam(int degX, int degY) const
{
    QReadLocker locker(&rwLock);
    return this->value._XYData[idxFromXY(degX, degY)].second;
}

double Distortion::xParam(int idx) const
{
    QReadLocker locker(&rwLock);
    return this->value._XYData[idx].first;
}

double Distortion::yParam(int idx) const
{
    QReadLocker locker(&rwLock);
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
