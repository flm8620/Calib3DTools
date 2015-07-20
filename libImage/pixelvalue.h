#ifndef PIXELVALUE_H
#define PIXELVALUE_H

#include <limits>
#include <tuple>
#include <type_traits>

namespace pixel {

struct Byte;
template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
struct RGBValue;

/**
 * @brief AllowedValuetypes, The data types suitable for pixel data in an Image
 */
typedef std::tuple<
            Byte, double, long double,
            RGBValue<Byte>, RGBValue<double>, RGBValue<long double>>
            AllowedValuetypes;

/**
 * @brief Find the index number of T in the AllowedValuetypes tuple
 */
template<typename T, int N = std::tuple_size<AllowedValuetypes>::value-1>
struct ValuetypeIndex :  public std::conditional<
        std::is_same<T, typename std::tuple_element<N,AllowedValuetypes>::type>::value,
                     std::integral_constant<int, N>,
                     ValuetypeIndex<T, N-1>>::type
{};

/**
 * @brief -1, the T is not in the AllowedValuetypes tuple
 */
template<typename T>
struct ValuetypeIndex<T, -1> : public std::integral_constant<int, -1>::type {};


/**
 * @brief Check if the T exists in the AllowedValuetypes tuple. Enable it if true
 */
template<typename T, class =std::enable_if<ValuetypeIndex<T>::value >=0 >>
struct ValidValuetype
{
    typedef T type;
    constexpr static int typeindex = ValuetypeIndex<T>::value;
    constexpr static size_t size = sizeof(T);
};

template<int I>
struct Valuetype
{
    typedef typename std::tuple_element<I, AllowedValuetypes>::type type;
};

template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
static inline unsigned char byteTruncate(T value)
{
    const static T BYTE_MAX = static_cast<T>(std::numeric_limits<unsigned char>::max());
    const static T BYTE_MIN = static_cast<T>(std::numeric_limits<unsigned char>::min());

    return static_cast<unsigned char>( value>BYTE_MAX ? BYTE_MAX :
                                       value<BYTE_MIN ? BYTE_MIN : value );
}

/**
 * @brief Image data type
 */
struct Byte
{
    unsigned char value;

    inline Byte(){}
    inline Byte(unsigned char value) : value(value){}
    inline operator unsigned char() const { return this->value; }
    template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
    explicit inline Byte(T value) { this->operator =(value); }

    const static Byte WHITE;
    const static Byte BLACK;

    template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
    inline Byte& operator =(T value) { this->value = byteTruncate(value); return *this; }
    inline Byte& operator =(unsigned char value) { this->value = value; return *this; }
    inline Byte& operator =(const Byte& original) { this->value = original.value; return *this; }

    template<typename T>
    inline bool operator ==(T other) const { return this->value==other; }
    inline bool operator ==(const Byte& other) const { return this->value==other.value; }
    template<typename T>
    inline bool operator !=(T other) const { return this->value!=other; }
    inline bool operator !=(const Byte& other) const { return this->value!=other.value; }
    template<typename T>
    inline bool operator >(T other) const { return this->value>other; }
    inline bool operator >(const Byte& other) const { return this->value>other.value; }
    template<typename T>
    inline bool operator <(T other) const { return this->value<other; }
    inline bool operator <(const Byte& other) const { return this->value<other.value; }
    template<typename T>
    inline bool operator >=(T other) const { return this->value>=other; }
    inline bool operator >=(const Byte& other) const { return this->value>=other.value; }
    template<typename T>
    inline bool operator <=(T other) const { return this->value<=other; }
    inline bool operator <=(const Byte& other) const { return this->value<=other.value; }

    template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
    inline T operator +(T other) const { return other + this->value; }
    inline int operator +(const Byte& other) const { return int(this->value) + int(other.value); }
    template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
    inline T operator -(T other) const { return - other + this->value; }
    inline int operator -(const Byte& other) const { return int(this->value) - int(other.value); }
    template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
    inline T operator *(T other) const { return other * this->value; }
    inline int operator *(const Byte& other) const { return int(this->value) * int(other.value); }
    template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
    inline T operator /(T other) const { return (static_cast<T>(1)/other) * this->value; }
    inline int operator /(const Byte& other) { return int(this->value) / int(other.value); }

    template<typename T>
    inline Byte& operator +=(T other) { return *this = *this + other; }
    template<typename T>
    inline Byte& operator -=(T other) { return *this = *this - other; }
    template<typename T>
    inline Byte& operator *=(T other) { return *this = *this * other; }
    template<typename T>
    inline Byte& operator /=(T other) { return *this = static_cast<T>(*this) / other; }

    inline Byte& operator ++() { return *this+=1; }
//    inline const Byte operator ++()
//    {
//        Byte result(*this);
//        *this += 1;
//        return result;
//    }
    inline Byte& operator --() { return *this-=1; }
//    inline const Byte operator --()
//    {
//        Byte result(*this);
//        *this-=1;
//        return result;
//    }
};


/**
 * @brief Image color data type
 */
template<typename T>
struct RGBValue<T>
{
    typename std::enable_if<
                std::is_arithmetic<T>::value ||
                std::is_same<T,Byte>::value,
                T>::type r,g,b;

    inline RGBValue(){}
    explicit inline RGBValue(T luma ) : r(luma), g(luma), b(luma) {}
    inline RGBValue(T r, T g, T b ) : r(r), g(g), b(b) {}
    inline RGBValue(const RGBValue<T>& value) : r(value.r), g(value.g), b(value.b) {}

    const static RGBValue<T> WHITE;
    const static RGBValue<T> BLACK;

    template<typename V, class=std::enable_if<std::is_arithmetic<V>::value>>
    explicit inline RGBValue(const RGBValue<V>& value)
        :r(static_cast<T>(value.r)), g(static_cast<T>(value.g)),b(static_cast<T>(value.b)) {}

    inline RGBValue<T>& operator =(const RGBValue<T>& value)
    {
        this->r=value.r;
        this->g=value.g;
        this->b=value.b;
        return *this;
    }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    inline RGBValue<T>& operator =(const RGBValue<V>& value)
    {
        this->r = static_cast<T>(value.r);
        this->g = static_cast<T>(value.g);
        this->b = static_cast<T>(value.b);
        return *this;
    }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    inline RGBValue<T>& operator +=(const RGBValue<V>& addend)
    {
        this->r += addend.r;
        this->g += addend.g;
        this->b += addend.b;
        return *this;
    }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    inline RGBValue<T>& operator +=(V addend)
    {
        this->r += addend;
        this->g += addend;
        this->b += addend;
        return *this;
    }

    template<typename V>
    inline RGBValue<T>& operator -=(const V& substrahend)
    { return *this += -substrahend; }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    inline RGBValue<T>& operator *=(const RGBValue<V>& multiplicand)
    {
        this->r *= multiplicand.r;
        this->g *= multiplicand.g;
        this->b *= multiplicand.b;
        return *this;
    }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    inline RGBValue<T>& operator *=(V multiplicand)
    {
        this->r *= multiplicand;
        this->g *= multiplicand;
        this->b *= multiplicand;
        return *this;
    }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    inline RGBValue<T>& operator /=(V divisor)
    {
        return *this *= 1.0/static_cast<double>(divisor);
    }

    inline RGBValue<T>& operator /=(long double divisor)
    {
        return *this *= 1.0L/divisor;
    }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    inline RGBValue<T>& operator /=(const RGBValue<V>& divisor)
    {
        return (*this *= RGBValue<double>({1.0/static_cast<double>(divisor.r),
                                      1.0/static_cast<double>(divisor.g),
                                      1.0/static_cast<double>(divisor.b) }) );
    }

    inline RGBValue<T>& operator /=(RGBValue<long double> divisor)
    {
        return *this *= RGBValue<long double>(
                               {1.0L/static_cast<long double>(divisor.r),
                                1.0L/static_cast<long double>(divisor.g),
                                1.0L/static_cast<long double>(divisor.b)});
    }

    inline RGBValue<T>& operator ++() { return *this += static_cast<T>(1); }
    inline RGBValue<T>& operator --() { return *this -= static_cast<T>(1); }
//    inline RGB<T> operator ++()
//    {
//        RGB<T> result(*this);
//        *this += static_cast<T>(1);
//        return result;
//    }
//    inline RGB<T> operator --()
//    {
//        RGB<T> result(*this);
//        *this -= static_cast<T>(1);
//        return result;
//    }

    template<typename V, class =std::enable_if<std::is_arithmetic<V>::value>>
    explicit operator V()
    {
        const static RGBValue<double> BT601LUMA(0.299, 0.587, 0.114);
        return static_cast<V>( this->r*BT601LUMA.r + this->g*BT601LUMA.g + this->b*BT601LUMA.b );
    }

    explicit operator Byte()
    {
        const static RGBValue<double> BT601LUMA(0.299, 0.587, 0.114);
        return byteTruncate( this->r*BT601LUMA.r + this->g*BT601LUMA.g + this->b*BT601LUMA.b );
    }
};


template<typename T>
const RGBValue<T> RGBValue<T>::WHITE(Byte::WHITE);
template<typename T>
const RGBValue<T> RGBValue<T>::BLACK(Byte::BLACK);

template<typename T, class =std::enable_if<std::is_arithmetic<T>::value>>
inline RGBValue<T> operator -(const RGBValue<T>& original)
{ return RGBValue<T>(-original.r, -original.g, -original.b); }

inline RGBValue<int> operator -(const RGBValue<Byte>& original)
{ return -RGBValue<int>(original); }

template<typename T, typename V>
inline RGBValue<T> operator +(const RGBValue<T>& addend1, const RGBValue<V>& addend2)
{
    return {
            addend1.r + addend2.r,
            addend1.g + addend2.g,
            addend1.b + addend2.b};
}

template<typename T, typename V>
inline RGBValue<T> operator +(const RGBValue<T>& addend1, V addend2)
{
    return {addend1.r + addend2,
            addend1.g + addend2,
            addend1.b + addend2 };
}

template<typename T, typename V>
inline RGBValue<V> operator +(T addend1, const RGBValue<V>& addend2) { return addend2 + addend1; }


template<typename T, typename V>
inline RGBValue<T> operator -(const RGBValue<T>& minus, const V& substrahend)
{ return minus + -substrahend; }

template<typename T, typename V>
inline RGBValue<T> operator *(const RGBValue<T>& multiplier, const RGBValue<V>& multiplicand)
{
    return {multiplier.r * multiplicand.r,
            multiplier.g * multiplicand.g,
            multiplier.b * multiplicand.b};
}

template<typename T, typename V>
inline RGBValue<T> operator *(const RGBValue<T>& multiplier, V multiplicand)
{
    return {multiplier.r * multiplicand,
            multiplier.g * multiplicand,
            multiplier.b * multiplicand};
}

template<typename T, typename V>
inline RGBValue<V> operator *(T multiplier, const RGBValue<V>& multiplicand) { return multiplicand*multiplier; }

template<typename T, typename V>
inline RGBValue<T> operator /(const RGBValue<T>& multiplier, const RGBValue<V>& multiplicand)
{
    return {multiplier.r / static_cast<double>(multiplicand.r),
            multiplier.g / static_cast<double>(multiplicand.g),
            multiplier.b / static_cast<double>(multiplicand.b)};
}

template<typename T, typename V>
inline RGBValue<T> operator /(const RGBValue<T>& dividend, V divisor)
{
    double invDivisor = 1.0/static_cast<double>(divisor);
    return dividend * invDivisor;
}


}

#endif // PIXELVALUE_H

