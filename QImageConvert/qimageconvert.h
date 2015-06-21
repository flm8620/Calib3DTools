#ifndef QIMAGECONVERT_H
#define QIMAGECONVERT_H
#include <QImage>
#include "image.h"
QImage ImageDoubleToQGrayImage(image_double in);
image_double qimage_to_image_double(const QImage &qimage);
image_char qimage_to_image_char(const QImage &qimage);
void QColorImageToImageDoubleRGB(const QImage &qimage, image_double_RGB &out);
void QGrayImageToImageDouble(const QImage &qimage, image_double &out);

QImage ImageDoubleRGBToQColorImage(image_double_RGB in);

#endif // QIMAGECONVERT_H
