#include "distortion.h"
using concurrent::ReadLock;
using concurrent::WriteLock;

Distortion::Distortion(const double* original, size_t size) :
    values(size), delegates(*this)

{
    for(size_t i=0; i<size; i++) values[i] = original[i];
}

Distortion::Distortion(const std::vector<double> &other) :
    values(other), delegates(*this)
{

}

Distortion::Distortion(const Distortion& other) :
    Distortion( (other.rwLock.lockForRead(), other.values) )
{
    other.rwLock.unlock();
}

double Distortion::value(size_t index, double defaultValue) const
{
    ReadLock lock(this->rwLock);
    return values.size()>index ? values[index] : defaultValue;
}

int Distortion::size() const
{
    ReadLock lock(this->rwLock);
    return values.size();
}

void Distortion::set(size_t index, double value)
{
    WriteLock lock( this->rwLock );

    if(index>=this->values.size()) {

        this->values.resize( index+1 );
        this->values[index] = value;
        lock.unlock();
        this->_dataSizeChangedEvent.trigger(index+1);

    } else if(value != this->values[index]) {

        this->values[index] = value;
        lock.unlock();
        this->_dataChangedEvent.trigger(index,index);

    }
}

void Distortion::copyItem(const Distortion& from, size_t fromIndex, size_t toIndex, size_t count)
{
    ReadLock srcLock( from.rwLock );
    WriteLock lock( this->rwLock );

    size_t fromSize = from.values.size();
    if( fromIndex+count>=fromSize )
        count = fromSize - fromIndex;
    if( count<=0 )
        return;

    if(toIndex+count>=this->values.size()) {

        size_t newSize = toIndex+count+1;
        this->values.resize( newSize );
        for(size_t i=0, t=toIndex, f=fromIndex; i<count; i++,t++,f++) this->values[t] = from.values[f];
        lock.unlock();
        srcLock.unlock();
        this->_dataSizeChangedEvent.trigger( newSize );

    } else {

        for(size_t i=0, t=toIndex, f=fromIndex; i<count; i++,t++,f++) this->values[t] = from.values[f];
        lock.unlock();
        srcLock.unlock();
        this->_dataChangedEvent.trigger( toIndex, toIndex+count-1 );
    }
}

double Distortion::atomicAdd(size_t index, double addend)
{
    WriteLock lock( this->rwLock );

    double result;
    if(index>=this->values.size()) {
        this->values.resize( index+1 );
        this->values[index]=addend;
        lock.unlock();
        result = addend;
        this->_dataSizeChangedEvent.trigger(index+1);
    } else {
        result = this->values[index] += addend;
        lock.unlock();
        this->_dataChangedEvent.trigger(index, index);
    }
    return result;
}

double Distortion::atomicAdd(size_t index, const Distortion& addend, size_t addendIndex)
{
    ReadLock srcLock( addend.rwLock );
    return addend.values.size()>addendIndex ?
                this->atomicAdd(index, addend.values[addendIndex]) :
                this->value(index);
}

double Distortion::atomicSubstract(size_t index, const Distortion& subtrahend, size_t subtrahendIndex)
{
    ReadLock srcLock( subtrahend.rwLock );
    return subtrahend.values.size()>subtrahendIndex ?
                this->atomicAdd(index, -subtrahend.values[subtrahendIndex]) :
                this->value(index);
}


int Distortion::atomicCompare(size_t index, const Distortion& other, size_t otherIndex) const
{
    ReadLock srcLock( other.rwLock );
    ReadLock lock(this->rwLock);
    double thisValue = values.size()>index ? values[index] : 0;
    double otherValue = other.values.size()>otherIndex ? other.values[otherIndex] : 0;
    return thisValue==otherValue ? 0 : thisValue>otherValue ? 1 : -1;
}

Distortion::ItemDelegate* Distortion::DelegateDealer::get(size_t index)
{
    auto it = this->find(index);
    if(it != this->end())
        return it->second;

    WriteLock lock(this->parent.rwLock);
    it = this->find(index);
    if(it != this->end())
         return it->second;

    return (*this)[index] = new ItemDelegate(this->parent, index);
}

Distortion::DelegateDealer::~DelegateDealer()
{
    WriteLock lock(this->parent.rwLock);
    for( auto it = this->begin(); it!=this->end(); ++it)
        delete it->second;
    this->clear();
}
