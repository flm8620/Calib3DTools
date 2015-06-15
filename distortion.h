#ifndef DISTORTION_H
#define DISTORTION_H

#include <QtCore>

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
    inline double operator [](int index) const { return this->value(index); }
    int size() const;
    inline bool isEmpty() const { return this->size()<=0; }
    inline bool isNotEmpty() const { return this->size()>0; }

    void set(int index, double value);
    void insert(int index, double value);
    void remove(int index);
    void copyItem(const Distortion& from, int fromIndex, int toIndex, int count);
    double atomicAdd(int index, double addend);
    double atomicAdd(int index, const Distortion& addend, int addendIndex);
    double atomicSubstract(int index, const Distortion& subtrahend, int subtrahendIndex);
    int atomicCompare(int index, const Distortion& other, int otherIndex) const;

    class ItemDelegate
    {
    private:
        Distortion& parent;
        const int index;

    public:
        inline ItemDelegate(Distortion& parent, int index) :parent(parent),index(index) {}

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
    inline ItemDelegate& operator [](int index) { return *( this->delegates.get(index) ); }

signals:
    void dataChanged(int fromIndex, int toIndex);
    void dataSizeChanged(int newSize);

protected:
    mutable QReadWriteLock rwLock;

private:
    QVarLengthArray<double> values;

    class DelegateDealer : private QHash<int, ItemDelegate*>
    {
    private:
        Distortion& parent;
    public:
        inline DelegateDealer(Distortion& parent) : parent(parent) {}
        ~DelegateDealer();

        ItemDelegate* get(int index);
    } delegates;
};

Q_DECLARE_METATYPE(Distortion)


#endif // DISTORTION_H

