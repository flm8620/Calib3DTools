#include "qimageconvert.h"
QImage ImageDoubleToQGrayImage(image_double in)
{
    int w = in->xsize, h = in->ysize;
    QImage image(w, h, QImage::Format_RGB32);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int color = in->data[x+y*w];
            image.setPixel(x, y, qRgb(color, color, color));
        }
    }
    return image;
}

image_double qimage_to_image_double(const QImage &qimage)
{
    int w = qimage.width(), h = qimage.height();
    image_double image = new_image_double(w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            image->data[ x + y * w ] = qGray(qimage.pixel(x, y));
    return image;
}



image_char qimage_to_image_char(const QImage &qimage)
{
    int w = qimage.width(), h = qimage.height();
    image_char image = new_image_char(w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            image->data[ x + y * w ] = qGray(qimage.pixel(x, y));
    return image;
}


void QColorImageToImageDoubleRGB(const QImage &qimage, image_double_RGB &out)
{
    Q_ASSERT(!qimage.isNull());
    int w = qimage.width(), h = qimage.height();
    out = new_image_double_RGB(w, h);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            out->Rdata[x+y*w] = qRed(qimage.pixel(x, y));
            out->Gdata[x+y*w] = qGreen(qimage.pixel(x, y));
            out->Bdata[x+y*w] = qBlue(qimage.pixel(x, y));
        }
    }
}


void QGrayImageToImageDouble(const QImage &qimage, image_double &out)
{
    Q_ASSERT(!qimage.isNull());
    int w = qimage.width(), h = qimage.height();
    out = new_image_double(w, h);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++)
            out->data[x+y*w] = qGray(qimage.pixel(x, y));
    }
}


QImage ImageDoubleRGBToQColorImage(image_double_RGB in)
{
    int w = in->xsize, h = in->ysize;
    QImage image(w, h, QImage::Format_RGB32);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int red = in->Rdata[x+y*w];
            int green = in->Gdata[x+y*w];
            int blue = in->Bdata[x+y*w];
            image.setPixel(x, y, qRgb(red, green, blue));
        }
    }
    return image;
}
