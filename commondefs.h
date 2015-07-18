#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#include <limits.h>

template<typename T>
struct Bi
{
    T x,y;

    Bi(){}
    Bi( const Bi<T>& original ) : x(original.x), y(original.y) {}
    Bi( const T& x, const T& y ) : x(x), y(y) {}
    template<typename R>
    inline Bi<T>& operator =( const Bi<R>& r ) { x=static_cast<T>(r.x); y=static_cast<T>(r.y); return *this; }
    template<typename R>
    inline bool operator ==( const Bi<R>& r ) { return x==r.x && y==r.y; }
    template<typename R>
    inline bool operator !=( const Bi<R>& r ) { return !(*this==r); }
};


/* fast integral power function */
inline double ipow(double x, int power)
{
    unsigned abs = power<0 ? -power:power;
    double result;
    for (result=1.0; abs!=0; abs>>=1, x*=x) if( abs&1 ) result *= x;
    return power<0 ? 1.0/result : result;
}

/* fast integral square root function */
inline unsigned int isqrt(unsigned long x )
{
    if(x==0) return 0;

    unsigned int result=0, bit=UINT_MAX;
    while ((bit&x)==x) bit>>=1;
    bit>>=1; bit++;

    while(bit!=0) {
        register unsigned t = result|bit;
        if(t*t<=x) result|=bit;
        bit>>=1;
    }

    return result;
}

const int MAX_POLYNOME_ORDER = 11;
typedef Bi<double> Vector2D;
typedef Bi<unsigned int> pixelAddr;


#endif // COMMONDEFS_H

