#ifndef IMAGE_HEADER
#define IMAGE_HEADER
#include "messager.h"
#include <vector>
#include <cmath>
/** Image data type
 *
 */
typedef unsigned char BYTE;
inline int roundColor(double color)
{
    return std::max(std::min(std::floor(color+0.5), 255.0), 0.0);
}

template<typename T>
class ImageGray
{
public:
    ImageGray(unsigned int xsize, unsigned int ysize)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _data.resize(xsize*ysize);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for new ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    ImageGray(unsigned int xsize, unsigned int ysize, T fillValue)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _data.resize(xsize*ysize, fillValue);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for new ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    ImageGray() : _xsize(0),
        _ysize(0)
    {
    }

    void resize(unsigned int xsize, unsigned int ysize)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _data.resize(xsize*ysize);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for resizing ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    void resize(unsigned int xsize, unsigned int ysize, T fillValue)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _data.resize(xsize*ysize, fillValue);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for resizing ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    bool pixelInside(int x, int y)const
    {
        return 0 <= x && x < this->_xsize && 0 <= y && y < this->_ysize;
    }

    inline T &pixel(int x, int y)
    {
        return _data[x+y*this->_xsize];
    }

    inline const T &pixel(int x, int y) const
    {
        return _data[x+y*this->_xsize];
    }

    inline T &data(int index)
    {
        return _data[index];
    }

    inline const T &data(int index) const
    {
        return _data[index];
    }

    inline int xsize() const
    {
        return _xsize;
    }

    inline int ysize() const
    {
        return _ysize;
    }

    bool isValid()const
    {
        return _xsize != 0 && _ysize != 0;
    }

private:
    std::vector<T> _data;
    unsigned int _xsize, _ysize;
};
template<typename T>
class ImageRGB
{
public:
    ImageRGB(unsigned int xsize, unsigned int ysize)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _Rdata.resize(xsize*ysize);
            _Gdata.resize(xsize*ysize);
            _Bdata.resize(xsize*ysize);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for new ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    ImageRGB(unsigned int xsize, unsigned int ysize, T RfillValue, T GfillValue, T BfillValue)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _Rdata.resize(xsize*ysize, RfillValue);
            _Gdata.resize(xsize*ysize, GfillValue);
            _Bdata.resize(xsize*ysize, BfillValue);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for new ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    ImageRGB() : _xsize(0),
        _ysize(0)
    {
    }

    void resize(unsigned int xsize, unsigned int ysize)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _Rdata.resize(xsize*ysize);
            _Gdata.resize(xsize*ysize);
            _Bdata.resize(xsize*ysize);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for resizing ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    void resize(unsigned int xsize, unsigned int ysize, T RfillValue, T GfillValue, T BfillValue)
    {
        if (xsize == 0 || ysize == 0)
            libMsg::error("Invalid Image Size, xsize==0 or ysize==0");
        try{
            _Rdata.resize(xsize*ysize, RfillValue);
            _Gdata.resize(xsize*ysize, GfillValue);
            _Bdata.resize(xsize*ysize, BfillValue);
        }catch (std::bad_alloc &bad) {
            libMsg::error("Not enough memory for resizing ImageGray");
        }
        this->_xsize = xsize;
        this->_ysize = ysize;
    }

    bool pixelInside(int x, int y)const
    {
        return 0 <= x && x < this->_xsize && 0 <= y && y < this->_ysize;
    }

    inline T &pixel_R(int x, int y)
    {
        return _Rdata[x+y*this->_xsize];
    }

    inline T &pixel_G(int x, int y)
    {
        return _Gdata[x+y*this->_xsize];
    }

    inline T &pixel_B(int x, int y)
    {
        return _Bdata[x+y*this->_xsize];
    }

    inline const T &pixel_R(int x, int y) const
    {
        return _Rdata[x+y*this->_xsize];
    }

    inline const T &pixel_G(int x, int y) const
    {
        return _Gdata[x+y*this->_xsize];
    }

    inline const T &pixel_B(int x, int y) const
    {
        return _Bdata[x+y*this->_xsize];
    }

    inline T &Rdata(int index)
    {
        return _Rdata[index];
    }

    inline T &Gdata(int index)
    {
        return _Gdata[index];
    }

    inline T &Bdata(int index)
    {
        return _Bdata[index];
    }

    inline const T &Rdata(int index) const
    {
        return _Rdata[index];
    }

    inline const T &Gdata(int index) const
    {
        return _Gdata[index];
    }

    inline const T &Bdata(int index) const
    {
        return _Bdata[index];
    }

    inline int xsize() const
    {
        return _xsize;
    }

    inline int ysize() const
    {
        return _ysize;
    }

    bool isValid()const
    {
        return _xsize != 0 && _ysize != 0;
    }

private:
    std::vector<T> _Rdata, _Gdata, _Bdata;
    unsigned int _xsize, _ysize;
};

void imageDoubleFromImageBYTE(const ImageGray<BYTE> &in, ImageGray<double> &out);
#endif
