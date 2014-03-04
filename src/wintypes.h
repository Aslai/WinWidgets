#ifndef __WINWIDGETS_WINTYPES_H__
#define __WINWIDGETS_WINTYPES_H__
#include <windows.h>


namespace WinWidgets{
    template <class T, int minimum, int maximum> class ClampValue{
        T value;
        void Clamp(){ if( value < minimum ) value = minimum; if( value > maximum ) value = maximum; }
    public:
        ClampValue(){value = T();Clamp();}
        ClampValue( T in ){value = in; Clamp();}
        T Get(){return value;}
        ClampValue& operator=(T other){value = other;Clamp();return *this;}
        ClampValue<T, minimum, maximum>& operator+=(T other){return operator=(value + other);}
        ClampValue<T, minimum, maximum>& operator-=(T other){return operator=(value - other);}
        ClampValue<T, minimum, maximum>& operator/=(T other){return operator=(value / other);}
        ClampValue<T, minimum, maximum>& operator*=(T other){return operator=(value * other);}
        ClampValue<T, minimum, maximum>& operator|=(T other){return operator=(value | other);}
        ClampValue<T, minimum, maximum>& operator&=(T other){return operator=(value & other);}
        ClampValue<T, minimum, maximum>& operator^=(T other){return operator=(value ^ other);}
        int operator!=(T other){return (value != other);}
        int operator==(T other){return (value == other);}
        int operator>(T other){return (value > other);}
        int operator<(T other){return (value < other);}
        int operator>=(T other){return (value >= other);}
        int operator<=(T other){return (value <= other);}
        ClampValue<T, minimum, maximum>& operator%=(T other){return operator=(value % other);}
        operator bool(){ return value?true:false; }
        operator T(){ return value; }
    };
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator~( ClampValue<T, minimum, maximum> c ){return ClampValue<T, minimum, maximum>(~c.Get());}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator+( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() + v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator-( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() - v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator*( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() * v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator/( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() / v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator^( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() ^ v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator&( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() & v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator|( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() | v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator!( ClampValue<T, minimum, maximum> c){return ClampValue<T, minimum, maximum>(!c.Get());}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator%( ClampValue<T, minimum, maximum> c, T v){return ClampValue<T, minimum, maximum>(c.Get() % v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator<<( ClampValue<T, minimum, maximum> c, int v){return ClampValue<T, minimum, maximum>(c.Get() << v);}
    template <class T, T minimum, T maximum> ClampValue<T, minimum, maximum> operator>>( ClampValue<T, minimum, maximum> c, int v){return ClampValue<T, minimum, maximum>(c.Get() >> v);}

    typedef ClampValue<int,0,255> ClampByte;
    typedef ClampValue<double,0,1> ClampFloat;


    struct Point{
        int X, Y;
    };
    struct Color{
       ClampByte r, g, b, a;
    };
    struct Brush{
        Color color;
        int size;
        bool filled;
    };
    struct Rect{
        int x, y;
        unsigned int w, h;
    };
    struct Icon{
        HICON ico;
    };
    struct Cursor{
        HCURSOR cur;
    };
}

#endif
