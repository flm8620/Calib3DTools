#ifndef DISTORTION_H
#define DISTORTION_H

#include "Concurrent/readwritelock.h"
#include "Event/eventhandler.h"
#include <functional>
#include <vector>
#include <map>

using concurrent::ReadWriteLock;
using event::EventConnection;
using event::IntegerNotifyEventHandler;

typedef event::EventHandler<void, int, int> IntRangeNotifyEventHandler;
typedef IntRangeNotifyEventHandler::Listener IntRangeNotifyEventListener;

/**
 * @brief The Distortion
 * @note All public functions of this class are thread-safe
 */
class Distortion
{
private:
    std::vector<double> values;
    IntegerNotifyEventHandler _dataSizeChangedEvent;
    IntRangeNotifyEventHandler _dataChangedEvent;

protected:
    mutable ReadWriteLock rwLock;

public:
    Distortion(const double* original=NULL, size_t size=0 );
    Distortion( const std::vector<double>& other );
    Distortion( const Distortion& other );

    const IntegerNotifyEventHandler& dataSizeChangedEvent = this->_dataSizeChangedEvent;
    const IntRangeNotifyEventHandler& dataChangedEvent = this->_dataChangedEvent;

    double value(size_t index, double defaultValue=0) const;
    inline double operator [](size_t index) const { return this->value(index); }
    int size() const;
    inline bool isEmpty() const { return this->size()<=0; }
    inline bool isNotEmpty() const { return this->size()>0; }

    void set(size_t index, double value);
    void copyItem(const Distortion& from, size_t fromIndex, size_t toIndex, size_t count);
    double atomicAdd(size_t index, double addend);
    double atomicAdd(size_t index, const Distortion& addend, size_t addendIndex);
    double atomicSubstract(size_t index, const Distortion& subtrahend, size_t subtrahendIndex);
    int atomicCompare(size_t index, const Distortion& other, size_t otherIndex) const;

    class ItemDelegate
    {
    private:
        Distortion& parent;
        const size_t index;

    public:
        inline ItemDelegate(Distortion& parent, size_t index) :parent(parent),index(index) {}

        inline double value() const { return parent.value(this->index); }
        inline operator double() const { return this->value(); }

        inline ItemDelegate& operator =(double value)
                    { return parent.set(this->index, value), *this; }
        inline ItemDelegate& operator =(const ItemDelegate& other)
                    { return parent.copyItem(other.parent, other.index, this->index, 1), *this; }

        inline bool operator ==(double value) const { return this->value()==value; }
        inline bool operator !=(double value) const { return this->value()!=value; }
        inline bool operator ==(const ItemDelegate& another) const
                    { return this->parent.atomicCompare(this->index, another.parent, another.index)==0; }
        inline bool operator !=(const ItemDelegate& another) const { return !((*this)==another); }

        inline ItemDelegate& operator +=(double addend)
                    { return parent.atomicAdd(this->index, addend), *this; }
        inline ItemDelegate& operator -=(double subtrahend) { return *this += -subtrahend; }
        inline ItemDelegate& operator +=(const ItemDelegate& addend)
                    { return parent.atomicAdd(this->index, addend.parent, addend.index), *this; }
        inline ItemDelegate& operator -=(const ItemDelegate& subtrahend)
                    { return parent.atomicSubstract(this->index, subtrahend.parent, subtrahend.index), *this; }

        //TODO: add more item operator overloading here.
    };
    inline ItemDelegate& operator [](size_t index) { return *( this->delegates.get(index) ); }

private:

    class DelegateDealer : private std::map<size_t, ItemDelegate*>
    {
    private:
        Distortion& parent;
    public:
        inline DelegateDealer(Distortion& parent) : parent(parent) {}
        ~DelegateDealer();

        ItemDelegate* get(size_t index);
    } delegates;
};



#endif // DISTORTION_H

