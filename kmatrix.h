#ifndef KMATRIX_H
#define KMATRIX_H

#include <QtCore>

class KMatrix
{
public:
    inline KMatrix() {}
    inline KMatrix(double value[5]) { *this = value; }
    inline KMatrix(const KMatrix& value);

    inline KMatrix& operator =(const double value[5]);
    inline bool operator ==(const double value[5]) const;
    inline double fx() const { return this->_fx; }
    inline double fy() const { return this->_fy; }
    inline double x0() const { return this->_x0; }
    inline double y0() const { return this->_y0; }
    inline double s() const { return this->_s; }

private:
    double _fx, _fy, _x0, _y0, _s;
};
Q_DECLARE_METATYPE(KMatrix)

class KMatrixContainer
{
public:
    virtual KMatrix getKMatrix_threadSafe() =0;
    virtual void saveKMatrix_threadSafe(const KMatrix& value) =0;
    virtual bool isEmpty() =0;
};


inline KMatrix::KMatrix(const KMatrix& value) {
    this->_fx = value._fx;
    this->_fy = value._fy;
    this->_x0 = value._x0;
    this->_y0 = value._y0;
    this->_s = value._s;
}

inline KMatrix& KMatrix::operator =(const double value[5]) {
    this->_fx = value[0];
    this->_fy = value[1];
    this->_x0 = value[2];
    this->_y0 = value[3];
    this->_s = value[4];
    return *this;
}

inline bool KMatrix::operator ==(const double value[5]) const {
    return
            this->_fx == value[0] &&
            this->_fy == value[1] &&
            this->_x0 == value[2] &&
            this->_y0 == value[4] &&
            this->_s == value[5];
}

#endif // KMATRIX_H

