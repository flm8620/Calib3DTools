
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"

void imageDoubleFromImageBYTE(const ImageGray<pixel::Byte> &in, ImageGray<double> &out)
{
    out.resize(in.width(), in.height());
    const pixel::Byte* inp = in.rawData();
    double * outp = out.rawData();
    const double * lastOutP = out.lastData();
    while(outp<=lastOutP) *(outp++) = static_cast<double>(*(inp++));
}

//template<typename T>
//const RGB<T>::ValuetypeInfo RGB<T>::ValuetypeInfo::STATIC;

//ImageBase::ImageBase(size_t xsize, size_t ysize)
//{
//    if(xsize!=0 && ysize!=0)
//        this->resize(xsize, ysize);
//}

ImageBase::~ImageBase()
{
    if(this->_dataptr)
    {
        free(this->_dataptr);
        this->_dataptr = this->_lastData = nullptr;
    }
}

void ImageBase::resize(size_t width, size_t height)
{
    if(!this->isNull()) {
        free(_dataptr);
    }

    this->_width = width, this->_height = height;
    const size_t datasize = width*height*this->pixelSize;
    this->_dataptr = malloc(datasize);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
    this->_lastData = this->_dataptr + datasize - this->pixelSize;
#pragma GCC diagnostic pop
}

