#ifndef DISTORTION_H
#define DISTORTION_H

#include <QtCore>

class Distortion;
class DistortionItemDelegate;

class DistortionItemDelegateDealer : private QHash<int, DistortionItemDelegate*>
{
private:
    Distortion* parent;
    QReadWriteLock* rwLock;
public:
    inline DistortionItemDelegateDealer(Distortion* parent, QReadWriteLock* rwLock) : parent(parent), rwLock(rwLock) {}
    ~DistortionItemDelegateDealer();
    DistortionItemDelegate* get(int index);
};

/**
 * @brief The Distortion
 * @note All public functions of this class are thread-safe
 */
class Distortion : public QObject
{
    Q_OBJECT
public:
    Distortion( const double* original=NULL, int size=0, QObject* parent=NULL );
    Distortion( const QVarLengthArray<double>& other, QObject* parent=NULL );
    Distortion( const Distortion& other, QObject* parent=NULL );

    double value(int index, double defaultValue=0) const;
    void set(int index, double value);
    int size() const;
    void insert(int index, double value);
    void remove(int index);
    void copyItem(const Distortion& from, int fromIndex, int toIndex, int count);
    double atomicAdd(int index, double addend);
    double atomicAdd(int index, const Distortion& addend, int addendIndex);
    double atomicSubstract(int index, const Distortion& subtrahend, int subtrahendIndex);
    int atomicCompare(int index, const Distortion& other, int otherIndex) const;
    DistortionItemDelegate& operator [](int index);
    inline double operator [](int index) const { return this->value(index); }
    inline bool isEmpty() const { return this->size()<=0; }
    inline bool isNotEmpty() const { return this->size()>0; }
signals:
    void dataChanged(int fromIndex, int toIndex);
    void dataSizeChanged(int newSize);
private:
    QVarLengthArray<double> values;
    DistortionItemDelegateDealer delegates;
protected:
    mutable QReadWriteLock rwLock;
};

Q_DECLARE_METATYPE(Distortion)

class DistortionItemDelegate
{
private:
    Distortion& parent;
    int index;
public:
    inline double value() { return parent.value(this->index); }
    inline DistortionItemDelegate(Distortion& parent, int index) :parent(parent),index(index) {}
    inline DistortionItemDelegate& operator =(double value)
                { return parent.set(this->index, value), *this; }
    inline DistortionItemDelegate& operator =(const DistortionItemDelegate& other)
                { return parent.copyItem(other.parent, other.index, this->index, 1), *this; }
    inline bool operator ==(double value) { return double(*this)==value; }
    inline bool operator !=(double value) { return double(*this)!=value; }
    inline bool operator ==(const DistortionItemDelegate& another)
                { return this->parent.atomicCompare(this->index, another.parent, another.index)==0; }
    inline bool operator !=(const DistortionItemDelegate& another) { return !((*this)==another); }
    inline DistortionItemDelegate& operator +=(double addend)
                { return parent.atomicAdd(this->index, addend), *this; }
    inline DistortionItemDelegate& operator -=(double subtrahend) { return *this += -subtrahend; }
    inline DistortionItemDelegate& operator +=(const DistortionItemDelegate& addend)
                { return parent.atomicAdd(this->index, addend.parent, addend.index), *this; }
    inline DistortionItemDelegate& operator -=(const DistortionItemDelegate& subtrahend)
                { return parent.atomicSubstract(this->index, subtrahend.parent, subtrahend.index), *this; }
//TODO: add more operator overloading here.
    inline operator double() { return this->value(); }
};

#endif // DISTORTION_H

