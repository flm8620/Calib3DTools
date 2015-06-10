#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <QtCore>
#include <QtGui>

typedef QList<QImage> ImageList;

class ImageListContainer
{
public:
    virtual ImageList getImageList_threadSafe() =0;
    virtual void saveImageList_threadSafe(const ImageList& value) =0;
    virtual bool isEmpty() =0;
};

#endif // IMAGELIST_H

