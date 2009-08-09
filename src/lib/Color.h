/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef COLOR_H
#define COLOR_H

#include "Common.h"

// usage: glColor4fv(color.rgba);

template<typename T>
class Color
{
    public:
        // struct and array for glColor calls
        union
        {
            struct
            {
                T  R, G, B, A;  // individual access
            };
            T rgba[4];  // 4 value vector for glColor4fv
            T rgb[3];   // 3 value vector for glColor3fv
        };

        Color() : R(0), G(0), B(0), A(0) {}

        Color(T r, T g, T b, T a) :
            R(r), G(g), B(b), A(a) {}

        virtual ~Color() {}

        /// copy constructor
		Color(const Color& from)
		{
            R = from.R;
            G = from.G;
            B = from.B;
            A = from.A;
		}

        /// copy operator
        void operator =(Color& from)
        {
            R = from.R;
            G = from.G;
            B = from.B;
            A = from.A;
        }

        /// attribute sets
        void set(T r, T g, T b, T a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
        void set(T r, T g, T b)
        {
            R = r;
            G = g;
            B = b;
        }

        friend std::ostream& operator<<(std::ostream& os, Color<T>& from)
        {
            os << "r: " << from.R << " g: " << from.G << " b: " << from.B
               << " a: " << from.A;
            return os;
        }
};

typedef Color<uint8_t>          Color4ub;
typedef Color<unsigned int>     Color4ui;
typedef Color<int>              Color4i;
typedef Color<float>            Color4f;
typedef Color<double>           Color4d;

#endif // COLOR_H
