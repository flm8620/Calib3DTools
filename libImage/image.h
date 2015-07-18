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
protected:


private:
    const struct {
        int typeindex;
        size_t size;
    } valuetype;
    void * _dataptr = nullptr;
    void * _lastData = nullptr;
    size_t _width =0, _height =0;
    size_t rowDistance, imageDistance;
protected:
    inline void * data() { return this->_dataptr; }
    inline const void * data() const { return this->_dataptr; }
    inline const void * last() const { return this->_lastData; }

    template<typename T, class=pixel::ValidValuetype<T>>
    inline T * dataptr()
    {
        return pixel::ValidValuetype<T>::typeindex==valuetype.typeindex ?
                    reinterpret_cast<T*>(_dataptr) : nullptr;
    }

    template<typename T, class=pixel::ValidValuetype<T>>
    inline const T * dataptr() const
    {
        return pixel::ValidValuetype<T>::typeindex==valuetype.typeindex ?
                    reinterpret_cast<const T*>(_dataptr) : nullptr;
    }

public:
    template<typename T, class=pixel::ValidValuetype<T>>
    ImageBase(const T * valueP, size_t xsize=0, size_t ysize=0)
        : valuetype({pixel::ValidValuetype<T>::typeindex, pixel::ValidValuetype<T>::size})
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
        if(resultTypeIndex!=valuetype.typeindex)
            throw new std::bad_cast();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
        return *reinterpret_cast<T*>(_dataptr+(y*_width + x)*valuetype.size);
#pragma GCC diagnostic pop
    }

    template<typename T>
    const typename pixel::ValidValuetype<T>::type& pixel(int x, int y) const
    {
        const static int resultTypeIndex = pixel::ValuetypeIndex<T>::value;
        if(resultTypeIndex!=valuetype.typeindex)
            throw new std::bad_cast();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
        return *reinterpret_cast<const T*>(_dataptr+(y*_width + x)*valuetype.size);
#pragma GCC diagnostic push
    }

    inline size_t width() const { return this->_width; }
    inline size_t height() const { return this->_height; }
};

template<typename T, class= pixel::ValidValuetype<T>>
class Image : public ImageBase
{
    typedef ImageBase SUPER;
public:
    inline T * rawData() { return reinterpret_cast<T*>(this->SUPER::data()); }
    inline const T * rawData() const { return reinterpret_cast<const T*>(this->SUPER::data()); }
    inline const T * lastData() const { return reinterpret_cast<const T*>(this->last()); }

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
using ImageRGB = Image<pixel::RGB<T>>;

//template<typename T, class = pixel::ValidValuetype<pixel::RGB<T>>>
//class ImageRGB : public Image<pixel::RGB<T>>
//{
//    typedef Image<pixel::RGB<T>> SUPER;
//public:
//    ImageRGB(size_t xsize=0, size_t ysize=0) : SUPER(xsize,ysize)
//    { }

//    ImageRGB(unsigned int xsize, unsigned int ysize, T RfillValue, T GfillValue, T BfillValue)
//        :SUPER(xsize, ysize, {RfillValue,GfillValue,BfillValue})
//    { }

//};

void imageDoubleFromImageBYTE(const ImageGray<pixel::BYTE> &in, ImageGray<double> &out);
#endif
