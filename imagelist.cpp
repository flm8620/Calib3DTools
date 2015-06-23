#include "imagelist.h"

ImageList::ImageList(QObject *parent) : QObject(parent)
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
        this->imageData.append(qMakePair(name,image));
    }
    emit dataChanged();
}

void ImageList::setImage(int index, const QImage &image)
{
    if(this->indexValid(index))
    {
        QWriteLocker locker(&this->rwLock);
        this->imageData[index].second=image;
    }
    emit dataChanged();
}

void ImageList::setName(int index, const QString &name)
{
    if(this->indexValid(index))
    {
        QWriteLocker locker(&this->rwLock);
        this->imageData[index].first=name;
    }
    emit dataChanged();
}

void ImageList::remove(int index)
{
    if (this->indexValid(index)) {
        QWriteLocker locker(&this->rwLock);
        imageData.removeAt(index);
    }
    emit dataChanged();
}

QImage ImageList::getImage(int index) const
{
    QReadLocker locker(&this->rwLock);
    if (this->indexValid(index))
        return this->imageData.at(index).second;
    return QImage();
}

QString ImageList::getName(int index) const
{
    QReadLocker locker(&this->rwLock);
    if (this->indexValid(index))
        return this->imageData.at(index).first;
    return QString();
}

void ImageList::getContent(QList<QPair<QString, QImage> > &listOut)const
{
    QReadLocker locker(&this->rwLock);
    listOut=this->imageData;
}

void ImageList::setContent(QList<QPair<QString, QImage> > &listIn)
{
    {
    QWriteLocker locker(&this->rwLock);
    this->imageData=listIn;
    }
    emit dataChanged();
}

void ImageList::moveUp(int index)
{
    if(index>=1&&index<imageData.size()){
        {
        QWriteLocker locker(&this->rwLock);
        this->imageData.swap(index,index-1);
        }
        emit dataChanged();
    }
}

void ImageList::moveDown(int index)
{
    if(index>=0&&index<imageData.size()-1){
        {
        QWriteLocker locker(&this->rwLock);
        this->imageData.swap(index,index+1);
        }
        emit dataChanged();
    }
}

bool ImageList::indexValid(int index)const
{
    QReadLocker locker(&this->rwLock);
    return index>=0&&index<imageData.size();
}
