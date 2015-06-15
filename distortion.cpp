#include "distortion.h"

DistortionItemDelegate* DistortionItemDelegateDealer::get(int index)
{
    if(this->contains(index))
        return this->value(index);

    QWriteLocker lock(this->rwLock);
    return this->contains(index) ? this->value(index) :
               ((*this)[index] = new DistortionItemDelegate(*this->parent, index));
}

DistortionItemDelegateDealer::~DistortionItemDelegateDealer()
{
    foreach(DistortionItemDelegate* delegate, this->values()) {
        delete delegate;
    }
    this->clear();
}


static inline void unsafeCopy( double* dest, const double * src, int count )
{
    for(int i; i<count; i++, dest++, src++ )
        *dest = *src;
}

Distortion::Distortion( const double* original, int size, QObject* parent ) :
    QObject(parent), values(size), delegates(this, &this->rwLock)

{
    if( original!=NULL && size>0 )
        unsafeCopy( this->values.data(), original, size );
}

Distortion::Distortion( const QVarLengthArray<double>& other, QObject* parent ) :
    Distortion(other.data(), other.size(), parent)
{

}

Distortion::Distortion(const Distortion& other, QObject* parent ) :
    Distortion( (other.rwLock.lockForRead(), other.values), parent )
{
    other.rwLock.unlock();
}

double Distortion::value(int index, double defaultValue) const
{
    QReadLocker lock(&this->rwLock);
    return values.value(index, defaultValue);
}

int Distortion::size() const
{
    QReadLocker lock(&this->rwLock);
    return values.size();
}

void Distortion::set(int index, double value)
{
    if( index<0 )
        return;

    QWriteLocker lock( &this->rwLock );

    if(index>=values.size()) {

        values.resize( index+1 );
        this->values.replace( index, value );
        lock.unlock();
        emit this->dataSizeChanged(index+1);

    } else if(value != this->values.value(index)) {

        this->values.replace( index, value );
        lock.unlock();
        emit this->dataChanged(index,index);

    }
}

void Distortion::insert(int index, double value)
{
    if( index<0 )
        return;

    QWriteLocker lock( &this->rwLock );

    if(index>=this->values.size()) {
        this->values.resize( index+1 );
        this->values.replace( index, value );
    } else {
        this->values.insert(index, value);
    }

    int newSize = this->values.size();
    lock.unlock();
    emit this->dataSizeChanged(newSize);
}

void Distortion::remove(int index)
{
    if(index<0)
        return ;

    QWriteLocker lock( &this->rwLock );

    if(index<this->values.size()) {
        this->values.remove(index);

        int newSize = this->values.size();
        lock.unlock();
        emit this->dataSizeChanged(newSize);
    }
}

void Distortion::copyItem(const Distortion& from, int fromIndex, int toIndex, int count)
{
    if( fromIndex<0 || toIndex<0 )
        return;

    QReadLocker srcLock( &from.rwLock );
    QWriteLocker lock( &this->rwLock );

    int fromSize = from.values.size();
    if( fromIndex+count>=fromSize )
        count = fromSize - fromIndex;
    if( count<=0 )
        return;

    if(toIndex+count>=this->values.size()) {

        int newSize = toIndex+count+1;
        this->values.resize( newSize );
        unsafeCopy(this->values.data()+toIndex, from.values.data()+fromIndex, count);
        lock.unlock();
        srcLock.unlock();
        emit this->dataSizeChanged( newSize );

    } else {

        unsafeCopy(this->values.data()+toIndex, from.values.data()+fromIndex, count);
        lock.unlock();
        srcLock.unlock();
        emit this->dataChanged( toIndex, toIndex+count-1 );
    }
}

double Distortion::atomicAdd(int index, double addend)
{
    if( index<0 )
        return 0;

    QWriteLocker lock( &this->rwLock );

    double result;
    if(index>=this->values.size()) {
        this->values.resize( index+1 );
        this->values.replace(index, addend);
        lock.unlock();
        result = addend;
        emit this->dataSizeChanged(index+1);
    } else {
        result = this->values.data()[index] += addend;
        lock.unlock();
        emit this->dataChanged(index, index);
    }
    return result;
}

double Distortion::atomicAdd(int index, const Distortion& addend, int addendIndex)
{
    QReadLocker srcLock( &addend.rwLock );
    return this->atomicAdd(index, addend.values.value(addendIndex, 0));
}

double Distortion::atomicSubstract(int index, const Distortion& subtrahend, int subtrahendIndex)
{
    QReadLocker srcLock( &subtrahend.rwLock );
    return this->atomicAdd(index, -subtrahend.values.value(subtrahendIndex));
}


int Distortion::atomicCompare(int index, const Distortion& other, int otherIndex) const
{
    QReadLocker srcLock( &other.rwLock );
    QReadLocker lock(&this->rwLock);
    double thisValue = values.value(index, 0);
    double otherValue = other.values.value(otherIndex, 0);
    return thisValue==otherValue ? 0 : thisValue>otherValue ? 1 : -1;
}

DistortionItemDelegate& Distortion::operator [](int index)
{
    return *( this->delegates.get(index) );
}
