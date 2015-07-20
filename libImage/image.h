#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#include "pixelvalue.h"

#include "messager.h"
#include <vector>
#include <cmath>
#include <limits>
#include <assert.h>

typedef enum { Stop=0, Mirror, Loop, Exceed } BoundaryAction;

class ImageBase
{
public:
    const int pixelType;
    const size_t pixelSize;
private:
    void * _dataptr = nullptr;
    void * _lastData = nullptr;
    size_t _width =0, _height =0;
    size_t rowDistance, imageDistance;
protected:
    template<typename T, class=pixel::ValidValuetype<T>>
    inline T * dataptr()
    {
        return pixel::ValidValuetype<T>::typeindex==pixelType ?
                    reinterpret_cast<T*>(_dataptr) : nullptr;
    }

    template<typename T, class=pixel::ValidValuetype<T>>
    inline const T * dataptr() const
    {
        return pixel::ValidValuetype<T>::typeindex==this->pixelType ?
                    reinterpret_cast<const T*>(_dataptr) : nullptr;
    }

public:
    template<typename T, class=pixel::ValidValuetype<T>>
    ImageBase(const T * valueP, size_t xsize=0, size_t ysize=0)
        : pixelType(pixel::ValidValuetype<T>::typeindex), pixelSize(pixel::ValidValuetype<T>::size)
    {
        if(xsize!=0 && ysize!=0)
            this->resize(xsize, ysize);
    }

    virtual ~ImageBase();

    void resize(size_t width, size_t height);

    template<typename T, class=pixel::ValidValuetype<T>>
    inline bool isNull() const { return this->dataptr<T>()==nullptr; }
    inline bool isNull() const { return this->_dataptr==nullptr; }
    inline bool pixelInside(int x, int y) const
    { return x>=0 && y>=0 && x<this->_width && y<this->_height; }

    template<typename T>
    typename pixel::ValidValuetype<T>::type& pixel(int x, int y)
    {
        const static int resultTypeIndex = pixel::ValuetypeIndex<T>::value;
        if(resultTypeIndex!=this->pixelType)
            throw new std::bad_cast();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
        return *reinterpret_cast<T*>(_dataptr+(y*_width + x)*this->pixelSize);
#pragma GCC diagnostic pop
    }

    template<typename T>
    const typename pixel::ValidValuetype<T>::type& pixel(int x, int y) const
    {
        const static int resultTypeIndex = pixel::ValuetypeIndex<T>::value;
        if(resultTypeIndex!=this->pixelType)
            throw new std::bad_cast();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
        return *reinterpret_cast<const T*>(_dataptr+(y*_width + x)*this->pixelSize);
#pragma GCC diagnostic push
    }

    inline void * rawData() { return this->_dataptr; }
    inline const void * rawData() const { return this->_dataptr; }
    inline const void * lastData() const { return this->_lastData; }
    inline size_t width() const { return this->_width; }
    inline size_t height() const { return this->_height; }
};

template<typename T, class= pixel::ValidValuetype<T>>
class Image : public ImageBase
{
    typedef ImageBase SUPER;
public:
    inline T * rawData() { return reinterpret_cast<T*>(this->SUPER::rawData()); }
    inline const T * rawData() const { return reinterpret_cast<const T*>(this->SUPER::rawData()); }
    inline const T * lastData() const { return reinterpret_cast<const T*>(this->SUPER::lastData()); }

    Image(size_t width=0, size_t height=0)
        : SUPER(reinterpret_cast<const T*>(0), width, height) {}

    Image(size_t width, size_t height, T fillValue)
        : SUPER(reinterpret_cast<const T*>(0)) {
        assert(width!=0 && height!=0);
        this->resize(width,height,fillValue);
    }

    using SUPER::resize;
    void resize(size_t width, size_t height, T fillValue)
    {
        assert(width>0 && height>0);
        this->resize(width, height);
        for(T* p = this->rawData(); p<=this->lastData(); p++) *p=fillValue;
    }

//    inline T& pixel(int x, int y) { return SUPER::pixel<T>(x,y); }
//    inline const T& pixel(int x, int y) const { return SUPER::pixel<T>(x,y); }


    T& pixel(int x, int y)
    {
        return this->rawData()[y*width() + x];
    }
    const T& pixel(int x, int y) const
    {
        return this->rawData()[y*width() + x];
    }

    /**
     * @brief data, Deprecated, use "rawData" instead.
     */
    T &data(int index) { return this->rawData()[index]; }
    /**
     * @brief data, Deprecated, use "rawData" instead.
     */
    const T &data(int index) const { return this->rawData()[index]; }

    /**
     * @brief xsize, Deprecated, use "width()" instead.
     */
    inline size_t xsize() const { return this->width(); }

    /**
     * @brief ysize, Deprecated, use "height()" instead.
     */
    inline size_t ysize() const { return this->height(); }

    inline bool isValid() const { return !this->isNull(); }

//    T& skipUp(T& pixel, BoundaryAction boundaryAction=Stop) {
//        T* result = reinterpret_cast<T*>(reinterpret_cast<void*>(&pixel) - rowDistance);
//        if(result>=this->dataptr) {
//            return *result;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            return *result;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            do reinterpret_cast<void*>(result) += imageDistance; while(result<this->dataptr);
//            return *result;
//        }
//        return pixel;
//    }

//    const T& skipUp(const T& pixel, BoundaryAction boundaryAction=Stop) const {
//        const T& last = pixel;
//        const T* result = reinterpret_cast<const T*>(reinterpret_cast<const void*>(&last) - rowDistance);
//        if(result>=this->dataptr) {
//            &pixel = *result;
//            return true;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            pixel = *result;
//            break;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            do reinterpret_cast<void*>(result) += imageDistance; while(result<this->dataptr);
//            pixel = *result;
//            break;
//        }
//        return false;
//    }

//    T& skipDown(T& pixel, BoundaryAction boundaryAction=Stop)  {
//        T& last = pixel;
//        T* result = reinterpret_cast<T*>(reinterpret_cast<void*>(&last) + rowDistance);
//        if(result<=this->lastData) {
//            pixel = *result;
//            return true;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            pixel = *result;
//            break;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            do reinterpret_cast<void*>(result) -= imageDistance; while(result>this->lastData);
//            pixel = *result;
//            break;
//        }
//        return false;
//    }

//    const T& skipDown(const T& pixel, BoundaryAction boundaryAction=Stop) const {
//        const T& last = pixel;
//        const T* result = reinterpret_cast<const T*>(reinterpret_cast<const void*>(&last) + rowDistance);
//        if(result<=this->lastData) {
//            pixel = *result;
//            return true;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            pixel = *result;
//            break;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            do reinterpret_cast<void*>(result) -= imageDistance; while(result>this->lastData);
//            pixel = *result;
//            break;
//        }
//        return false;
//    }

//    T& skipLeft(T& pixel, BoundaryAction boundaryAction=Stop) {
//        T& last = pixel;
//        void* lastp = reinterpret_cast<void*>(&last);
//        if((lastp - this->dataptr)%rowDistance!=0) {
//            pixel = *(reinterpret_cast<T*>(lastp-sizeof(T)));
//            return true;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            pixel = *(reinterpret_cast<T*>(lastp-sizeof(T)));
//            break;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            pixel = *(reinterpret_cast<T*>(lastp+rowDistance-sizeof(T)));
//            break;
//        }
//        return false;
//    }

//    const T& skipLeft(const T& pixel, BoundaryAction boundaryAction=Stop) const {
//        const T& last = pixel;
//        void* lastp = reinterpret_cast<void*>(&last);
//        if((lastp - this->dataptr)%rowDistance!=0) {
//            pixel = *(reinterpret_cast<const T*>(lastp-sizeof(T)));
//            return true;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            pixel = *(reinterpret_cast<const T*>(lastp-sizeof(T)));
//            break;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            pixel = *(reinterpret_cast<const T*>(lastp+rowDistance-sizeof(T)));
//            break;
//        }
//        return false;
//    }

//    T& skipRight(T& pixel, BoundaryAction boundaryAction=Stop) {
//        T& last = pixel;
//        void* result = reinterpret_cast<void*>(&last) + 1;
//        if((result-this->dataptr)%rowDistance!=0) {
//            pixel = *(reinterpret_cast<T*>(result));
//            return true;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            pixel = *(reinterpret_cast<T*>(result));
//            break;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            pixel = *(reinterpret_cast<T*>(result-rowDistance));
//            break;
//        }
//        return false;
//    }

//    const T& skipRight(const T&& pixel, BoundaryAction boundaryAction=Stop) const {
//        const T& last = pixel;
//        void* result = reinterpret_cast<void*>(&last) + 1;
//        if((result-this->dataptr)%rowDistance!=0) {
//            pixel = *(reinterpret_cast<T*>(result));
//            return true;
//        }

//        switch (boundaryAction) {
//        case Exceed:
//            pixel = *(reinterpret_cast<const T*>(result));
//            break;
//        case Mirror: //TODO: not implemented;
//            break;
//        case Loop:
//            pixel = *(reinterpret_cast<const T*>(result-rowDistance));
//            break;
//        }
//        return false;
//    }


};



template<typename T>
using ImageGray = Image<T>;

template<typename T>
using ImageRGB = Image<pixel::RGBValue<T>>;

void imageDoubleFromImageBYTE(const ImageGray<pixel::Byte> &in, ImageGray<double> &out);
#endif
