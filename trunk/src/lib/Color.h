/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef COLOR_H
#define COLOR_H

#include "Common.h"

template<typename T>
class Color
{
    public:

        Color() : _R(0), _G(0), _B(0), _A(0) {}

        Color(T r, T g, T b, T a=0) :
            _R(r), _G(g), _B(b), _A(a) {}

        virtual ~Color() {}

        /// copy operator
        void operator =(Color* from)
        {
            _R = from->R();
            _G = from->G();
            _B = from->B();
            _A = from->A();
        }

        /// attribute sets
        void set(T r, T g, T b, T a=0)
        {
            _R = r;
            _G = g;
            _B = b;
            _A = a;
        }
        void setR(T r)  {_R = r;}
        void setG(T g)  {_G = g;}
        void setB(T b)  {_B = b;}
        void setA(T a)  {_A = a;}

        /// attribute gets
        T R()    {return _R;}
        T G()    {return _G;}
        T B()    {return _B;}
        T A()    {return _A;}

        /// set the glColor
        void glColor()      {glColor3ub(_R, _G, _B);}
        void glColorAlpha() {glColor4ub(_R, _G, _B, _A);}

    private:

        T _R;
        T _G;
        T _B;
        T _A;
};

typedef Color<uint8_t>          Color4ub;
typedef Color<unsigned int>     Color4ui;
typedef Color<int>              Color4i;
typedef Color<float>            Color4f;
typedef Color<double>           Color4d;

#endif // COLOR_H
