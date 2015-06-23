#ifndef QIMAGECONVERT_H
#define QIMAGECONVERT_H
#include <QImage>
#include "image.h"
void ImageDouble2QImage(ImageGray<double> in, QImage &out);
void QImage2ImageDouble(const QImage &in, ImageGray<double> &out);
void QImage2ImageByte(const QImage &in, ImageGray<BYTE> &out);
void QColorImage2ImageDoubleRGB(const QImage &qimage, ImageRGB<double> &out);
void ImageDoubleRGB2QColorImage(const ImageRGB<double>& in,QImage& out);

#endif // QIMAGECONVERT_H
