#include "imagelist.h"

ImageList::ImageList(QObject *parent) : QObject(parent),rwLock(QReadWriteLock::Recursive)
{
}

bool ImageList::isEmpty() const
{
    QReadLocker locker(&this->rwLock);
    return this->imageData.size() == 0;
}

void ImageList::clear()
{
    {
        QWriteLocker locker(&rwLock);
        this->imageData.clear();
    }
    emit dataChanged();
}

int ImageList::size() const
{
    QReadLocker locker(&this->rwLock);
    return this->imageData.size();
}

void ImageList::append(const QString &name, const QImage &image)
{
    {
        QWriteLocker locker(&this->rwLock);
        this->imageData.append(qMakePair(name, image));
    }
    emit dataChanged();
}

void ImageList::setImage(int index, const QImage &image)
{
    {
        QWriteLocker locker(&this->rwLock);
        if (this->indexValidNolock(index))
            this->imageData[index].second = image;
    }
    emit dataChanged();
}

void ImageList::setName(int index, const QString &name)
{
    {
        QWriteLocker locker(&this->rwLock);
        if (this->indexValidNolock(index))
            this->imageData[index].first = name;
    }
    emit dataChanged();
}

void ImageList::remove(int index)
{
    {
        QWriteLocker locker(&this->rwLock);
        if (this->indexValidNolock(index))
            imageData.removeAt(index);
    }
    emit dataChanged();
}

QImage ImageList::getImage(int index) const
{
    QReadLocker locker(&this->rwLock);
    if (this->indexValidNolock(index))
        return this->imageData.at(index).second;
    return QImage();
}

QString ImageList::getName(int index) const
{
    QReadLocker locker(&this->rwLock);
    if (this->indexValidNolock(index))
        return this->imageData.at(index).first;
    return QString();
}

void ImageList::getContent(QList<QPair<QString, QImage> > &listOut) const
{
    QReadLocker locker(&this->rwLock);
    listOut = this->imageData;
}

void ImageList::setContent(QList<QPair<QString, QImage> > &listIn)
{
    {
        QWriteLocker locker(&this->rwLock);
        this->imageData = listIn;
    }
    emit dataChanged();
}

void ImageList::moveUp(int index)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        if (index >= 1 && index < imageData.size()) {
            valid = true;
            this->imageData.swap(index, index-1);
        }
    }
    if (valid)
        emit dataChanged();
}

void ImageList::moveDown(int index)
{
    bool valid = false;
    {
        QWriteLocker locker(&this->rwLock);
        if (index >= 0 && index < imageData.size()-1) {
            valid = true;
            this->imageData.swap(index, index+1);
        }
    }
    if (valid)
        emit dataChanged();
}

bool ImageList::indexValidNolock(int index) const
{
    return index >= 0 && index < imageData.size();
}
