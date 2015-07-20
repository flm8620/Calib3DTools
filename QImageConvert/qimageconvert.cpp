#include "qimageconvert.h"
void ImageDouble2QImage(const ImageGray<double> &in, QImage &out)
{
    int w = in.xsize(), h = in.ysize();
    out = QImage(w, h, QImage::Format_RGB32);
    checkQImageMemory(out);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int color = pixel::byteTruncate(in.pixel(x, y));
            out.setPixel(x, y, qRgb(color, color, color));
        }
    }
}

void QImage2ImageDouble(const QImage &in, ImageGray<double> &out)
{
    checkQImageMemory(in);
    int w = in.width(), h = in.height();
    out.resize(w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            out.pixel(x, y) = qGray(in.pixel(x, y));
}

void ImageByte2QImage(ImageGray<pixel::Byte> &in, QImage &out)
{
    int w = in.xsize(), h = in.ysize();
    out = QImage(w, h, QImage::Format_RGB32);
    checkQImageMemory(out);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            int color = pixel::byteTruncate(in.pixel(x, y));
            out.setPixel(x, y, qRgb(color, color, color));
        }
    }
}

void QImage2ImageByte(const QImage &in, ImageGray<pixel::Byte> &out)
{
    checkQImageMemory(in);
    int w = in.width(), h = in.height();
    out.resize(w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            out.pixel(x, y) = qGray(in.pixel(x, y));
}

void QColorImage2ImageDoubleRGB(const QImage &in, ImageRGB<double> &out)
{
    checkQImageMemory(in);
    int w = in.width(), h = in.height();
    out.resize(w, h);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++)
            out.pixel(x, y) = { static_cast<double>(qRed(in.pixel(x, y))),
                                static_cast<double>(qGreen(in.pixel(x, y))),
                                static_cast<double>(qBlue(in.pixel(x, y))) };
    }
}

using pixel::RGBValue;
using pixel::Byte;
void ImageDoubleRGB2QColorImage(const ImageRGB<double> &in, QImage &out)
{
    int w = in.xsize(), h = in.ysize();
    out = QImage(w, h, QImage::Format_RGB32);
    checkQImageMemory(out);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            RGBValue<Byte> color = static_cast<RGBValue<Byte>>(in.pixel(x,y));
            out.setPixel(x, y, qRgb(color.r, color.g, color.b));
        }
    }
}


void ImageByteRGB2QColorImage(const ImageRGB<pixel::Byte> &in, QImage &out)
{
    int w = in.xsize(), h = in.ysize();
    out = QImage(w, h, QImage::Format_RGB32);
    checkQImageMemory(out);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; y++) {
            RGBValue<Byte> color = static_cast<RGBValue<Byte>>(in.pixel(x,y));
            out.setPixel(x, y, qRgb(color.r, color.g, color.b));
        }
    }
}

void checkQImageMemory(const QImage &image)
{
    if(image.isNull())
        throw MyException("Not enough memory for QImage");
}
