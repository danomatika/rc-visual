/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Common.h"

#include <SDL/SDL_gfxPrimitives.h>

#include "Object.h"
#include "Color.h"

/**
    \class Rectangle
    \brief a colored gl rectangle
**/
class Rectangle : public Objecti
{
    public:

        Rectangle() : Objecti() {}

        Rectangle(int x, int y, int width, int height, int velX=0, int velY=0) :
            Objecti(x, y, width, height, velX, velY) {}

        virtual ~Rectangle() {}

        void setColor(Color4ub& color) {_color = color;}

        void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255)
            {_color.set(r, g, b, a);}

        virtual void update() {}

        /// draws from the center
        virtual void draw()
        {
            if(Graphics::isTypeOGL())
            {
                _color.glColor();

                glBegin(GL_TRIANGLE_STRIP);
                    glVertex2i((GLint) _x-_w/2, (GLint) _y-_h/2);
                    glVertex2i((GLint) _x+_w/2, (GLint) _y-_h/2);
                    glVertex2i((GLint) _x+_w/2, (GLint) _y+_h/2);
                    glVertex2i((GLint) _x-_w/2, (GLint) _y+_h/2);
                    glVertex2i((GLint) _x-_w/2, (GLint) _y-_h/2);
                glEnd();
            }
            else if(Graphics::isTypeSDL())
            {
                boxRGBA(Graphics::getSDLScreen(), // surface
                        _x-(_w/2), _y-(_h/2),                 // upper left
                        _x+(_w/2), _y+(_h/2),              // upper right
                    _color.R(), _color.G(), _color.B(), _color.A());
            }
        }

        friend std::ostream& operator<<(std::ostream& os, Rectangle& from)
        {
            os << "x: " << from._x << " y: " << from._y
               << " w: " << from._w << " h: " << from._h
               << " vx: " << from._vx << " vy: " << from._vy;
            return os;
        }

    protected:

        Color4ub _color;
};

#endif // RECTANGLE_H
