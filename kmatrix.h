#ifndef KMATRIX_H
#define KMATRIX_H

#include "Concurrent/readwritelock.h"
#include "Event/eventhandler.h"

using concurrent::ReadWriteLock;
using event::NotifyEventHandler;
typedef struct { double fx, fy, x0, y0, s; } KValue;
typedef struct { double x, y; } Vector2D;

inline bool operator ==(const KValue& l, const KValue& r)
{
    return l.fx==r.fx && l.fy==r.fy && l.x0==r.x0 && l.y0==r.y0 && l.s==r.s ;
}

/**
 * @brief The KMatrix
 * The KMatrix is the intrinsic matrix of a pinhole camera
 * whose components are:
 *
 *    fx   s  x0
 *     0  fy  y0
 *     0   0   1
 * fx, fy - Focal length in x and y direction, they have
 *          the same value in a true pinhole camera.
 * x0, y0 - Principal point offset, normally it's at the
 *          center of image.
 * s      - Axis skew who causes shear distortion.
 *
 * @note All public functions of this class are thread-safe
 */
class KMatrix
{
private:
    KValue value;
    NotifyEventHandler _dataChangedEvent;
protected:
    mutable ReadWriteLock rwLock;

public:
    KMatrix();
    KMatrix(const KValue& value);
    KMatrix(const KMatrix& value);

    const NotifyEventHandler& dataChangedEvent = this->_dataChangedEvent;
    bool isEmpty() const;
    void clear();
//properties' getters
    /**
     * @brief fx getter //TODO: more detailed document needed.
     * @return the value of the fx property.
     * @note Call getValue() instead if you are acquiring the whole K value.
     */
    double fx() const;
    /**
     * @brief fy getter //TODO: more detailed document needed.
     * @return the value of the fy property.
     * @note Call getValue() instead if you are acquiring the whole K value.
     */
    double fy() const;
    /**
     * @brief x0 getter //TODO: more detailed document needed.
     * @return the value of the x0 property.
     * @note Call getValue() instead if you are acquiring the whole K value.
     */
    double x0() const;
    /**
     * @brief y0 getter //TODO: more detailed document needed.
     * @return the value of the y0 property.
     * @note Call getValue() instead if you are acquiring the whole K value.
     */
    double y0() const;
    /**
     * @brief s getter //TODO: more detailed document needed.
     * @return the value of the s property.
     * @note Call getValue() instead if you are acquiring the whole K value.
     */
    double s() const;

//convenient getters for the consistency on concurrent access
    KValue getValue() const;

//properties' setters
    /**
     * @brief setFx //TODO: more detailed documents needed.
     * @param fx //TODO: more detailed documents needed.
     * @note Call setF or setValue instead if you are setting the F or the whole value;
     */
    void setFx( double fx );
    /**
     * @brief setFy //TODO: more detailed documents needed.
     * @param fy //TODO: more detailed documents needed.
     * @note Call setValue instead if you are setting the whole K value;
     */
    void setFy( double fy );
    /**
     * @brief setX0 //TODO: more detailed documents needed.
     * @param x0 //TODO: more detailed documents needed.
     * @note Call setValue instead if you are setting the whole K value;
     */
    void setX0( double x0 );
    /**
     * @brief setY0 //TODO: more detailed documents needed.
     * @param y0 //TODO: more detailed documents needed.
     * @note Call setValue instead if you are setting the whole K value;
     */
    void setY0( double y0 );
    /**
     * @brief setS //TODO: more detailed documents needed.
     * @param s //TODO: more detailed documents needed.
     * @note Call setValue instead if you are setting the whole K value;
     */
    void setS( double s );

//convenient atomic setters
    void setValue( const KValue& value );
    void setValue( double fx, double fy, double x0, double y0, double s );

//convenient operator overloading
    KMatrix& operator =(const KValue& value);
    bool operator ==(const KValue& value) const;
    bool operator ==(const KMatrix& other) const;
    inline bool operator !=(const KValue& value) const {return !(*this==value);}
    inline bool operator !=(const KMatrix& other) const{return !(*this==other);}
};

#endif // KMATRIX_H
