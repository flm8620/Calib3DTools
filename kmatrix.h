#ifndef KMATRIX_H
#define KMATRIX_H

#include "readwritelock.h"
#include <QtCore>


typedef struct { double fx, fy, x0, y0, s; } KValue;
typedef struct { double x, y; } Vector2D;
inline bool operator ==(const KValue& l, const KValue& r)
{
    return l.fx==r.fx && l.fy==r.fy && l.x0==r.x0 && l.y0==r.y0 && l.s==r.s ;
}

/**
 * @brief The KMatrix ; //TODO: more detailed documents needed.
 * @note All public functions of this class are thread-safe
 */
class KMatrix : public QObject
{
    Q_OBJECT
public:

    KMatrix(QObject * parent = 0);
    KMatrix(const KValue& value, QObject * parent = 0);
    KMatrix(const KMatrix& value, QObject * parent = 0);

    bool isEmpty() const;

//properties' getters
    /**
     * @brief fx getter //TODO: more detailed document needed.
     * @return the value of the fx property.
     * @note Call getF() or getValue() instead if you are acquiring the F or the whole K value.
     */
    double fx() const;
    /**
     * @brief fy getter //TODO: more detailed document needed.
     * @return the value of the fy property.
     * @note Call getF() or getValue() instead if you are acquiring the F or the whole K value.
     */
    double fy() const;
    /**
     * @brief x0 getter //TODO: more detailed document needed.
     * @return the value of the x0 property.
     * @note Call getOrigin() or getValue() instead if you are acquiring the origin or the whole K value.
     */
    double x0() const;
    /**
     * @brief y0 getter //TODO: more detailed document needed.
     * @return the value of the y0 property.
     * @note Call getOrigin() or getValue() instead if you are acquiring the origin or the whole K value.
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
    Vector2D getF() const;
    Vector2D getOrigin() const;

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
     * @note Call setF or setValue instead if you are setting the F or the whole value;
     */
    void setFy( double fy );
    /**
     * @brief setX0 //TODO: more detailed documents needed.
     * @param x0 //TODO: more detailed documents needed.
     * @note Call setOrigin or setValue instead if you are setting the origin or the whole value;
     */
    void setX0( double x0 );
    /**
     * @brief setY0 //TODO: more detailed documents needed.
     * @param y0 //TODO: more detailed documents needed.
     * @note Call setOrigin or setValue instead if you are setting the origin or the whole value;
     */
    void setY0( double y0 );
    /**
     * @brief setS //TODO: more detailed documents needed.
     * @param s //TODO: more detailed documents needed.
     * @note Call setValue instead if you are setting the whole value;
     */
    void setS( double s );

//convenient atomic setters
    void setValue( const KValue& value );
    void setValue( double fx, double fy, double x0, double y0, double s );
    void setF( const Vector2D& f );
    void setF( double fx, double fy );
    void setOrigin( const Vector2D origin );
    void setOrigin( double x0, double y0 );

//convenient operator overloading
    KMatrix& operator =(const KValue& value);
    bool operator ==(const KValue& value) const;
    bool operator ==(const KMatrix& other) const;

signals:
    void dataChanged();

protected:
    mutable ReadWriteLock rwLock;
private:
    KValue value;
};

Q_DECLARE_METATYPE(KMatrix)

#endif // KMATRIX_H

