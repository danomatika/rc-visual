/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef OBJECT_H
#define OBJECT_H

#include "vmmlib/vmmlib.h"

using namespace vmml;

/**
    \class Object
    \brief abstract class for object position, velocity, and size
**/
template<typename T>
class Object
{
    public:

        Object() : _pos(0, 0), _vel(0, 0),
                   _x(_pos.xy[0]), _y(_pos.xy[1]),
                   _w(0), _h(0),
                   _vx(_vel.xy[0]), _vy(_vel.xy[1])
                    {}

        Object(T x, T y, T w, T h, T vx=0, T vy=0) :
            _pos(x, y), _vel(vx, vy),
            _x(_pos.xy[0]), _y(_pos.xy[1]),
            _w(w), _h(h),
            _vx(_vel.xy[0]), _vy(_vel.xy[1])
            {}

        virtual ~Object() {}

        /// attribute sets
        void set(T x, T y, T w, T h, T vx=0, T vy=0)
        {
            _x = x;
            _y = y;
            _w = w;
            _h = h;
            _x = vx;
            _y = vy;
        }
        void setPos(T x, T y)
        {
            _x = x;
            _y = y;
        }
        void setSize(T w, T h)
        {
            _w = w;
            _h = h;
        }
        void setVel(T vx, T vy)
        {
            _vx = vx;
            _vy = vy;
        }
        void setX(T x)      {_x = x;}
        void setY(T y)      {_y = y;}
        void setW(T w)      {_w = w;}
        void setH(T h)      {_h = h;}
        void setVX(T vx)    {_vx = vx;}
        void setVY(T vy)    {_vy = vy;}

        /// attribute gets
        T getX()    {return _x;}
        T getY()    {return _y;}
        T getW()    {return _w;}
        T getH()    {return _h;}
        T getVX()   {return _vx;}
        T getVY()   {return _vy;}

        virtual void update() = 0;

        virtual void draw() = 0;

    protected:

        Vector2<T>  _pos;
        Vector2<T>  _vel;

        // references are to the data inside the vectors
        // for ease of use in derived classes
        T& _x;
        T& _y;
        T _w;
        T _h;
        T& _vx;
        T& _vy;
};

typedef Object<int>     Objecti;
typedef Object<float>   Objectf;

#endif // OBJECT_H
