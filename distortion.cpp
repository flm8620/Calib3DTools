#include "distortion.h"
#include <cmath>
Distortion::Distortion(QObject *parent) : QObject(parent),
    _size(0),
    _maxOrder(-1)
{
}

void Distortion::setMaxOrder(int maxOrder)
{
    QWriteLocker(&rwLock);
    _XYData.clear();
    if (maxOrder < 0) {
        this->_maxOrder = -1;
        return;
    }
    this->_maxOrder = maxOrder;
    this->_size = (2+maxOrder)*(1+maxOrder)/2;
    for (int i = 0; i < _size; ++i) _XYData.append(QPair<double, double>(0, 0));
    emit dataChanged();
}

static void Distortion::XYfromIdx(int idx, int &degX, int &degY) const
{
    int j = std::ceil((std::sqrt(9+8*idx)-1)/2);
    degY = idx-(j-1)*j/2;
    degX = j-1-degY;
}

static int Distortion::idxFromXY(int degX, int degY) const
{
    return (1+degX+degY)*(degX+degY)/2+degY;
}

void Distortion::setXParam(double value, int degX, int degY)
{
    QWriteLocker(&rwLock);
    _XYData[idxFromXY(degX, degY)].first = value;
    emit dataChanged();
}

void Distortion::setYParam(double value, int degX, int degY)
{
    QWriteLocker(&rwLock);
    _XYData[idxFromXY(degX, degY)].second = value;
    emit dataChanged();
}

void Distortion::setXParam(double value, int idx)
{
    QWriteLocker(&rwLock);
    _XYData[idx].first = value;
    emit dataChanged();
}

void Distortion::setYParam(double value, int idx)
{
    QWriteLocker(&rwLock);
    _XYData[idx].second = value;
    emit dataChanged();
}

int Distortion::xParam(int degX, int degY) const
{
    QReadLocker(&rwLock);
    return _XYData[idxFromXY(degX, degY)].first;
    emit dataChanged();
}

int Distortion::yParam(int degX, int degY) const
{
    QReadLocker(&rwLock);
    return _XYData[idxFromXY(degX, degY)].second;
    emit dataChanged();
}

double Distortion::xParam(int idx) const
{
    QReadLocker(&rwLock);
    return _XYData[idx].first;
    emit dataChanged();
}

double Distortion::yParam(int idx) const
{
    QReadLocker(&rwLock);
    return _XYData[idx].second;
    emit dataChanged();
}

void Distortion::clear()
{
    QWriteLocker(&rwLock);
    _XYData.clear();
    _maxOrder = -1;
    emit dataChanged();
}
