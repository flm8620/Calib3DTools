#include "kmatrix.h"

const static KValue EMPTY_K = {0,0,0,0,0};

KMatrix::KMatrix(const KValue& value, QObject * parent) : QObject(parent)
{
    this->rwLock = &this->_rwLock;
    this->value = value;
}

KMatrix::KMatrix(QObject * parent) : KMatrix(EMPTY_K, parent) {}
KMatrix::KMatrix(const KMatrix& k, QObject *parent) : KMatrix(k.getValue(), parent) {}

bool KMatrix::isEmpty() const
{
    QReadLocker locker(this->rwLock);
    return this->value == EMPTY_K;
}

double KMatrix::fx() const
{
    QReadLocker locker(this->rwLock);
    return this->value.fx;
}

double KMatrix::fy() const
{
    QReadLocker locker(this->rwLock);
    return this->value.fy;
}


double KMatrix::x0() const
{
    QReadLocker locker(this->rwLock);
    return this->value.x0;
}

double KMatrix::y0() const
{
    QReadLocker locker(this->rwLock);
    return this->value.y0;
}

double KMatrix::s() const
{
    QReadLocker locker(this->rwLock);
    return this->value.s;
}

KValue KMatrix::getValue() const
{
    QReadLocker locker(this->rwLock);
    return this->value;
}

Vector2D KMatrix::getF() const
{
    QReadLocker locker(this->rwLock);
    return Vector2D({this->value.fx, this->value.fy});
}

Vector2D KMatrix::getOrigin() const
{
    QReadLocker locker(this->rwLock);
    return Vector2D({this->value.x0, this->value.y0});
}

static inline bool lockAndSet(double& var, double value, QReadWriteLock* rwlock)
{
    QWriteLocker lock(rwlock);
    if( value != var ) {
        var = value;
        return true;
    }
    return false;
}

static inline bool lockAndSet(KValue& var, double fx, double fy, double x0, double y0, double s, QReadWriteLock* rwlock)
{
    QWriteLocker lock(rwlock);

    bool result = false;
    if( fx != var.fx ) {
        var.fx = fx;
        result = true;
    }
    if( fy != var.fy ) {
        var.fy = fy;
        result = true;
    }
    if( x0 != var.x0 ) {
        var.x0 = x0;
        result = true;
    }
    if( y0 != var.y0 ) {
        var.y0 = y0;
        result = true;
    }
    if( s != var.s ) {
        var.s = s;
        result = true;
    }
    return result;
}

static inline bool lockAndSet(double& varX, double& varY, double x, double y, QReadWriteLock* rwlock)
{
    QWriteLocker lock(rwlock);

    bool result = false;
    if( x != varX ) {
        varX = x;
        result = true;
    }
    if( y != varY ) {
        varY = y;
        result = true;
    }
    return result;
}

void KMatrix::setFx( double fx )
{
    if( lockAndSet( this->value.fx, fx, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setFy( double fy )
{
    if( lockAndSet( this->value.fy, fy, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setX0( double x0 )
{
    if( lockAndSet( this->value.x0, x0, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setY0( double y0 )
{
    if( lockAndSet( this->value.y0, y0, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setS( double s )
{
    if( lockAndSet( this->value.s, s, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setValue( const KValue& value )
{
    if( lockAndSet( this->value, value.fx, value.fy, value.x0, value.y0, value.s, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setValue(double fx, double fy, double x0, double y0, double s )
{
    if( lockAndSet( this->value, fx, fy, x0, y0, s, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setF( const Vector2D& f )
{
    if( lockAndSet( this->value.fx, this->value.fy, f.x, f.y, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setF(double fx, double fy)
{
    if( lockAndSet( this->value.fx, this->value.fy, fx, fy, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setOrigin( const Vector2D origin )
{
    if( lockAndSet( this->value.x0, this->value.y0, origin.x, origin.y, this->rwLock ) )
        emit this->dataChanged();
}

void KMatrix::setOrigin( double x0, double y0 )
{
    if( lockAndSet( this->value.x0, this->value.y0, x0, y0, this->rwLock ) )
        emit this->dataChanged();
}


KMatrix& KMatrix::operator =(const KValue& value)
{
    this->setValue(value);
    return *this;
}

bool KMatrix::operator ==(const KValue& value) const
{
    QReadLocker lock(this->rwLock);
    return this->value == value;
}

bool KMatrix::operator ==(const KMatrix& other) const
{
    QReadLocker lock(this->rwLock);
    QReadLocker otherLock(other.rwLock);
    return this->value == other.value;
}
