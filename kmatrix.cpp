#include "kmatrix.h"

using concurrent::ReadLock;
using concurrent::WriteLock;
const static KValue EMPTY_K = {0, 0, 0, 0, 0};

KMatrix::KMatrix(const KValue& value) : value(value) {}
KMatrix::KMatrix() : KMatrix(EMPTY_K) {}
KMatrix::KMatrix(const KMatrix& k) : KMatrix(k.getValue()) {}

bool KMatrix::isEmpty() const
{
    ReadLock locker(this->rwLock);
    return this->value == EMPTY_K;
}

void KMatrix::clear()
{
    this->setValue(EMPTY_K);
}

double KMatrix::fx() const
{
    ReadLock locker(this->rwLock);
    return this->value.fx;
}

double KMatrix::fy() const
{
    ReadLock locker(this->rwLock);
    return this->value.fy;
}

double KMatrix::x0() const
{
    ReadLock locker(this->rwLock);
    return this->value.x0;
}

double KMatrix::y0() const
{
    ReadLock locker(this->rwLock);
    return this->value.y0;
}

double KMatrix::s() const
{
    ReadLock locker(this->rwLock);
    return this->value.s;
}

KValue KMatrix::getValue() const
{
    ReadLock locker(this->rwLock);
    return this->value;
}

static inline bool lockAndSet(double &var, double value, ReadWriteLock &rwlock)
{
    WriteLock lock(rwlock);
    if (value != var) {
        var = value;
        return true;
    }
    return false;
}

static inline bool lockAndSet(KValue& var, double fx, double fy, double x0, double y0, double s, ReadWriteLock& rwlock)
{
    WriteLock lock(rwlock);

    bool result = false;
    if (fx != var.fx) {
        var.fx = fx;
        result = true;
    }
    if (fy != var.fy) {
        var.fy = fy;
        result = true;
    }
    if (x0 != var.x0) {
        var.x0 = x0;
        result = true;
    }
    if (y0 != var.y0) {
        var.y0 = y0;
        result = true;
    }
    if (s != var.s) {
        var.s = s;
        result = true;
    }
    return result;
}

static inline bool lockAndSet(double& varX, double& varY, double x, double y, ReadWriteLock& rwlock)
{
    WriteLock lock(rwlock);

    bool result = false;
    if (x != varX) {
        varX = x;
        result = true;
    }
    if (y != varY) {
        varY = y;
        result = true;
    }
    return result;
}

void KMatrix::setFx( double fx )
{
    if( lockAndSet( this->value.fx, fx, this->rwLock ) )
        this->_dataChangedEvent.trigger();
}

void KMatrix::setFy( double fy )
{
    if( lockAndSet( this->value.fy, fy, this->rwLock ) )
        this->_dataChangedEvent.trigger();
}

void KMatrix::setX0( double x0 )
{
    if( lockAndSet( this->value.x0, x0, this->rwLock ) )
        this->_dataChangedEvent.trigger();
}

void KMatrix::setY0( double y0 )
{
    if( lockAndSet( this->value.y0, y0, this->rwLock ) )
        this->_dataChangedEvent.trigger();
}

void KMatrix::setS(double s)
{
    if( lockAndSet( this->value.s, s, this->rwLock ) )
        this->_dataChangedEvent.trigger();
}

void KMatrix::setValue(const KValue &value)
{
    if (lockAndSet(this->value, value.fx, value.fy, value.x0, value.y0, value.s, this->rwLock ) )
        this->_dataChangedEvent.trigger();
}

void KMatrix::setValue(double fx, double fy, double x0, double y0, double s)
{
    if (lockAndSet(this->value, fx, fy, x0, y0, s, this->rwLock))
        this->_dataChangedEvent.trigger();
}

KMatrix &KMatrix::operator =(const KValue &value)
{
    this->setValue(value);
    return *this;
}

bool KMatrix::operator ==(const KValue &value) const
{
    ReadLock lock(this->rwLock);
    return this->value == value;
}

bool KMatrix::operator ==(const KMatrix &other) const
{
    ReadLock lock(this->rwLock);
    ReadLock otherLock(other.rwLock);
    return this->value == other.value;
}
