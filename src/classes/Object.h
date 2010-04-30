/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef OBJECT_H
#define OBJECT_H

#include <vmmlib/vmmlib.h>

/**
    \class Object
    \brief abstract class for object position, velocity, and size
**/
template<typename T>
class Object
{
    public:

        Object() : _pos(0, 0), _w(0), _h(0), _vel(0, 0)
            {}

        Object(T x, T y, T w, T h, T vx=0, T vy=0) :
            _pos(x, y), _w(w), _h(h), _vel(x, y)
            {}

        virtual ~Object() {}

        /// attribute sets
        void set(T x, T y, T w, T h, T vx, T vy)
        {
            _pos.x = x;
            _pos.y = y;
            _w = w;
            _h = h;
            _vel.x = vx;
            _vel.y = vy;
        }
        void set(T x, T y, T w, T h)
        {
            _pos.x = x;
            _pos.y = y;
            _w = w;
            _h = h;
        }
        void setPos(T x, T y)
        {
            _pos.x = x;
            _pos.y = y;
        }
        void setSize(T w, T h)
        {
            _w = w;
            _h = h;
        }
        void setVel(T vx, T vy)
        {
            _vel.x = vx;
            _vel.y = vy;
        }
        void setX(T x)      {_pos.x = x;}
        void setY(T y)      {_pos.y = y;}
        void setW(T w)      {_w = w;}
        void setH(T h)      {_h = h;}
        void setVX(T vx)    {_vel.x = vx;}
        void setVY(T vy)    {_vel.y = vy;}

        /// attribute gets
        T getX()    {return _pos.x;}
        T getY()    {return _pos.y;}
        T getW()    {return _w;}
        T getH()    {return _h;}
        T getVX()   {return _vel.x;}
        T getVY()   {return _vel.y;}

        virtual void update() = 0;

        virtual void draw() = 0;

    protected:

        vmml::Vector2<T> _pos;
        T _w;
        T _h;
        vmml::Vector2<T> _vel;
};

typedef Object<int>     Objecti;
typedef Object<float>   Objectf;
typedef Object<double>  Objectd;

#endif // OBJECT_H
