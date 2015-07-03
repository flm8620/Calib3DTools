#include "point3d.h"


Point3D::Point3D(QObject *parent): QObject(parent)
{

}

void Point3D::clear()
{
    {
        QWriteLocker locker(&this->rwLock);
        this->_data.clear();
    }
    emit dataChanged();
}

void Point3D::append()
{
    {
        QWriteLocker locker(&this->rwLock);
        this->_data.append(QVector3D(0.0,0.0,0.0));
    }
    emit dataChanged();
}

void Point3D::remove(int index)
{
    {
        QWriteLocker locker(&this->rwLock);
        if(index>=0&&index<this->_data.size())
            this->_data.removeAt(index);
    }
    emit dataChanged();
}

void Point3D::moveUp(int index)
{
    {
        QWriteLocker locker(&this->rwLock);
        if(index>=1&&index<this->_data.size())
            qSwap(this->_data[index],this->_data[index-1]);
    }
    emit dataChanged();
}

void Point3D::moveDown(int index)
{
    {
        QWriteLocker locker(&this->rwLock);
        if(index>=0&&index<this->_data.size()-1)
            qSwap(this->_data[index],this->_data[index+1]);
    }
    emit dataChanged();
}

QVector3D Point3D::getPoint(int index)const
{
    QReadLocker locker(&this->rwLock);
    if(index>=0&&index<this->_data.size())
        return this->_data[index];
    return QVector3D();
}

void Point3D::setPoint(int index, QVector3D point)
{
    {
        QWriteLocker locker(&this->rwLock);
        if(index>=0&&index<this->_data.size())
            this->_data[index]=point;
    }
    emit dataChanged();
}

void Point3D::getContent(QList<QVector3D> &out)
{
    QReadLocker locker(&this->rwLock);
    out=this->_data;
}

void Point3D::setContent(QList<QVector3D> &in)
{
    {
        QWriteLocker locker(&this->rwLock);
        this->_data=in;
    }
    emit dataChanged();
}
