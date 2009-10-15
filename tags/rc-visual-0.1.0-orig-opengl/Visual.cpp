#include "Visual.h"


Visual::Visual()
{
    //ctor
}

Visual::~Visual()
{
    //dtor
}

void Visual::setup(int screen_w_, int screen_h_)
{
    screen_w = screen_w_;
    screen_h = screen_h_;
}

void Visual::draw()
{

}

void Visual::update()
{

}

void Visual::cleanup()
{

}

void Rect::draw()
{
    if(show)
    {
        glColor3f(c->getR(), c->getG(), c->getB());
        glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x+w, y);
            glVertex2i(x+w, y+h);
            glVertex2i(x, y+h);
        glEnd();
    }
}
