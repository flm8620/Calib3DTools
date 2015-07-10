#include "camerapos.h"

CameraPos::CameraPos(QObject *parent) : QObject(parent)
{
}

bool CameraPos::isEmpty() const
{
    QReadLocker locker(&this->rwLock);
    return value.data.size() == 0;
}

int CameraPos::size() const
{
    QReadLocker locker(&this->rwLock);
    return this->value.data.size();
}

void CameraPos::clear()
{
    {
        QWriteLocker locker(&rwLock);
        this->value.data.clear();
    }
    emit dataChanged();
}

CameraPosValue CameraPos::getValue() const
{
    QReadLocker locker(&this->rwLock);
    return this->value;
}

bool CameraPos::setValue(const CameraPosValue &value)
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

double CameraPos::RMatrixElement(int index, int i, int j) const
{
    QReadLocker locker(&rwLock);
    if (index < this->value.data.size())
        return this->value.data[index].first[i*3+j];
}

double CameraPos::centerVector(int index, int i) const
{
    QReadLocker locker(&rwLock);
    if (index < this->value.data.size())
        return this->value.data[index].second[i];
}

void CameraPos::setRMatrixElement(int index, int i, int j, double val)
{
    {
        QWriteLocker locker(&rwLock);
        if (index < this->value.data.size())
            this->value.data[index].first[i*3+j] = val;
    }
    emit dataChanged();
}

void CameraPos::setCenterVector(int index, int i, double val)
{
    {
        QWriteLocker locker(&rwLock);
        if (index < this->value.data.size())
            this->value.data[index].second[i] = val;
    }
    emit dataChanged();
}

bool CameraPosValue::isValid() const
{
    bool ok = true;
    if (this->data.size() > 0) {
        for (int i = 0; i < this->data.size(); ++i) {
            if (this->data[i].first.size() != 9) ok = false;
            if (this->data[i].second.size() != 3) ok = false;
        }
    }
    return ok;
}
