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

        Rectangle() : Objecti(), _color(255, 255, 255, 255) {}

        Rectangle(int x, int y, int w, int h, int vx=0, int vy=0) :
            Objecti(x, y, w, h, vx, vy), _color(255, 255, 255, 255) {}

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
                glColor4ubv(_color.rgba);

                glBegin(GL_TRIANGLE_STRIP);
                    glVertex2i((GLint) _pos.x-_w/2, (GLint) _pos.y-_h/2);
                    glVertex2i((GLint) _pos.x+_w/2, (GLint) _pos.y-_h/2);
                    glVertex2i((GLint) _pos.x+_w/2, (GLint) _pos.y+_h/2);
                    glVertex2i((GLint) _pos.x-_w/2, (GLint) _pos.y+_h/2);
                    glVertex2i((GLint) _pos.x-_w/2, (GLint) _pos.y-_h/2);
                glEnd();
            }
            else if(Graphics::isTypeSDL())
            {
                boxRGBA(Graphics::getSDLScreen(), // surface
                        _pos.x-(_w/2), _pos.y-(_h/2),              // upper left
                        _pos.x+(_w/2), _pos.y+(_h/2),              // lower right
                    _color.R, _color.G, _color.B, _color.A);
            }
        }

        friend std::ostream& operator<<(std::ostream& os, Rectangle& from)
        {
            os << "x: " << from._pos.x << " y: " << from._pos.y
               << " w: " << from._w << " h: " << from._h
               << " vx: " << from._vel.x << " vy: " << from._vel.y;
            return os;
        }

    protected:

        Color4ub _color;
};

#endif // RECTANGLE_H
