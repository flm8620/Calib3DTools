#include "imagelistwithpoint2d.h"

ImageListWithPoint2D::ImageListWithPoint2D(QObject *parent) : ImageList(parent)
{
}

bool ImageListWithPoint2D::clearPoint()
{
    {
        QWriteLocker locker(&this->rwLock);
        for (int i = 0; i < this->_pointData.size(); ++i)
            this->_pointData[i].clear();
    }
    emit dataReset();
}

void ImageListWithPoint2D::clear()
{
    {
        QWriteLocker locker(&this->rwLock);
        ImageList::clear();
        this->_pointData.clear();
    }

    emit dataReset();
}

int ImageListWithPoint2D::pointCount() const
{
    QReadLocker locker(&this->rwLock);
    return this->_pointData.isEmpty() ? 0 : this->_pointData.first().size();
}

void ImageListWithPoint2D::append(const QString &name, const QImage &image)
{
    {
        QWriteLocker locker(&this->rwLock);
        ImageList::append(name, image);
        int pCount = this->_pointData.isEmpty() ? 0 : this->_pointData.first().size();
        QList<QPointF> pointsInImage;
        for (int i = 0; i < pCount; ++i)
            pointsInImage.append(QPointF(0.0, 0.0));
        this->_pointData.append(pointsInImage);
    }
    emit imageAppended();
}

void ImageListWithPoint2D::remove(int indexImg)
{
    {
        QWriteLocker locker(&this->rwLock);
        ImageList::remove(indexImg);
        if (indexImg >= 0 && indexImg < this->_pointData.size())
            this->_pointData.removeAt(indexImg);
    }
    emit dataReset();
}

void ImageListWithPoint2D::setContent(QList<QPair<QString, QImage> > &ImageListIn)
{
    {
        QWriteLocker locker(&this->rwLock);
        ImageList::setContent(ImageListIn);
        this->_pointData.clear();
        for (int i = 0; i < ImageListIn.size(); ++i)
            this->_pointData.append(QList<QPointF>());
    }
    emit dataReset();
}

void ImageListWithPoint2D::moveUp(int index)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        ImageList::moveUp(index);
        if (index >= 1 && index < this->_pointData.size()) {
            qSwap(this->_pointData[index], this->_pointData[index-1]);
            valid = true;
        }
    }
    if (valid) {
        emit imageChanged(index);
        emit imageChanged(index-1);
    }
}

void ImageListWithPoint2D::moveDown(int index)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        ImageList::moveDown(index);
        if (index >= 0 && index < this->_pointData.size()-1) {
            qSwap(this->_pointData[index], this->_pointData[index+1]);
            valid = true;
        }
    }
    if (valid) {
        emit imageChanged(index);
        emit imageChanged(index+1);
    }
}

void ImageListWithPoint2D::movePointUp(int indexPoint)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        for (int i = 0; i < this->_pointData.size(); ++i)
            if (indexPoint >= 1 && indexPoint < this->_pointData[i].size()) {
                qSwap(this->_pointData[i][indexPoint], this->_pointData[i][indexPoint-1]);
                valid = true;
            }
    }
    if (valid)
        emit pointSwaped(indexPoint, indexPoint-1);
}

void ImageListWithPoint2D::movePointDown(int indexPoint)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        for (int i = 0; i < this->_pointData.size(); ++i)
            if (indexPoint >= 0 && indexPoint < this->_pointData[i].size()-1) {
                qSwap(this->_pointData[i][indexPoint], this->_pointData[i][indexPoint+1]);
                valid = true;
            }
    }
    if (valid)
        emit pointSwaped(indexPoint, indexPoint+1);
}

void ImageListWithPoint2D::removePoint(int indexPoint)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        for (int i = 0; i < this->_pointData.size(); ++i) {
            if (indexPoint >= 0 && indexPoint < _pointData[i].size()) {
                this->_pointData[i].removeAt(indexPoint);
                valid = true;
            }
        }
    }
    if (valid)
        emit pointRemoved(indexPoint);
}

QPointF ImageListWithPoint2D::getPoint(int indexImg, int indexPoint) const
{
    QReadLocker locker(&this->rwLock);
    if (indexImg >= 0 && indexImg < this->_pointData.size()) {
        if (indexPoint >= 0 && indexPoint < this->_pointData.first().size())
            return this->_pointData[indexImg][indexPoint];
    }
    return QPointF();
}

void ImageListWithPoint2D::setPoint(int indexImg, int indexPoint, QPointF p)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        if (indexImg >= 0 && indexImg < this->_pointData.size()) {
            if (indexPoint >= 0 && indexPoint < this->_pointData.first().size()) {
                this->_pointData[indexImg][indexPoint] = p;
                valid = true;
            }
        }
    }
    if (valid)
        emit pointChanged(indexImg, indexPoint);
}

void ImageListWithPoint2D::getPointsInImage(int indexImg, QList<QPointF> &list)
{
    QReadLocker locker(&this->rwLock);
    if(indexImg>=0&&indexImg<this->_pointData.size()){
        list=this->_pointData[indexImg];
    }
}

void ImageListWithPoint2D::appendPoint()
{
    {
        QWriteLocker locker(&this->rwLock);
        for (int i = 0; i < this->_pointData.size(); ++i)
            this->_pointData[i].append(QPointF(0.0, 0.0));
    }
    emit pointAppended();
}
