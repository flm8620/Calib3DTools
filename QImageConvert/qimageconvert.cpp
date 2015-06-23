#include "qimageconvert.h"
void ImageDouble2QImage(ImageGray<double> in, QImage &out)
{
    int w = in.xsize(), h = in.ysize();
    out = QImage(w, h, QImage::Format_RGB32);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int color = roundColor(in.pixel(x, y));
            out.setPixel(x, y, qRgb(color, color, color));
        }
    }
}

void QImage2ImageDouble(const QImage &in, ImageGray<double> &out)
{
    int w = in.width(), h = in.height();
    out.resize(w,h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            out.pixel(x, y) = qGray(in.pixel(x, y));
}

void QImage2ImageByte(const QImage &in, ImageGray<BYTE> &out)
{
    int w = in.width(), h = in.height();
    out.resize(w,h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            out.pixel(x, y) = qGray(in.pixel(x, y));
}

void QColorImage2ImageDoubleRGB(const QImage &qimage, ImageRGB<double> &out)
{
    int w = qimage.width(), h = qimage.height();
    out.resize(w,h);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            out.pixel_R(x,y) = qRed(qimage.pixel(x, y));
            out.pixel_G(x,y) = qGreen(qimage.pixel(x, y));
            out.pixel_B(x,y) = qBlue(qimage.pixel(x, y));
        }
    }
}

void ImageDoubleRGB2QColorImage(const ImageRGB<double> &in, QImage &out)
{
    int w = in.xsize(), h = in.ysize();
    out = QImage(w, h, QImage::Format_RGB32);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int red = in.pixel_R(x, y);
            int green = in.pixel_G(x, y);
            int blue = in.pixel_B(x, y);
            out.setPixel(x, y, qRgb(red, green, blue));
        }
    }
}
