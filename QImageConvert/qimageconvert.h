#ifndef QIMAGECONVERT_H
#define QIMAGECONVERT_H
#include <QImage>
#include "image.h"
void ImageDouble2QImage(const ImageGray<double> &in, QImage &out);
void QImage2ImageDouble(const QImage &in, ImageGray<double> &out);
void ImageByte2QImage(ImageGray<pixel::Byte> &in, QImage &out);
void QImage2ImageByte(const QImage &in, ImageGray<pixel::Byte> &out);
void QColorImage2ImageDoubleRGB(const QImage &in, ImageRGB<double> &out);
void ImageDoubleRGB2QColorImage(const ImageRGB<double>& in,QImage& out);
void ImageByteRGB2QColorImage(const ImageRGB<pixel::Byte>& in,QImage& out);
void checkQImageMemory(const QImage& image);

#endif // QIMAGECONVERT_H
