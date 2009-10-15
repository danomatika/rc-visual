#include "Vel.h"


Vel::Vel()
{
    //ctor
}

Vel::~Vel()
{
    //dtor
}

void Vel::setup(int screen_w_, int screen_h_)
{
    screen_w = screen_w_;
    screen_h = screen_h_;

    Rect *r = new Rect(600, 0, 200, 150);
    Color *c = new Color(0.25, 0, 0);
    r->setColor(c);
    r->setShow(false);
    v_controls.push_back(*r);

    r = new Rect(600, 150, 200, 150);
    c = new Color(0, 0.5, 0);
    r->setColor(c);
    r->setShow(false);
    v_controls.push_back(*r);

    r = new Rect(600, 300, 200, 150);
    c = new Color(0, 0, 0.25);
     r->setColor(c);
     r->setShow(false);
    v_controls.push_back(*r);

    r = new Rect(600, 450, 200, 150);
    c = new Color(0.25, 0, 0.25);
     r->setColor(c);
     r->setShow(false);
    v_controls.push_back(*r);

    r = new Rect(0, screen_h/4*3, 0, 200);
    c = new Color(1.0, 0, 0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(0, screen_h/2, 0, 200);
    c = new Color(0, 1.0, 0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(0, screen_h/4, 0, 200);
    c = new Color(0, 0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(0, 0, 0, 200);
    c = new Color(1.0, 0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(screen_w/2, screen_h/2, 100, 100);
    c = new Color(1.0, 1.0, 1.0);
     r->setColor(c);
     r->setShow(false);
    v_controls.push_back(*r);

    cout<< "Vel Num: " << v_controls.size() << endl;
}

void Vel::update(string cntl, float val)
{
    vector<Rect>::iterator c = v_controls.begin();

    if(cntl == "L1")
    {
        c->setShow((bool) val);
    }

    else if(cntl == "L2")
    {
        c += 1;
        c->setShow((bool) val);
    }

    else if(cntl == "R1")
    {
        c += 2;
        c->setShow((bool) val);
    }

    else if(cntl == "R2")
    {
        c += 3;
        c->setShow((bool) val);
    }

    else if(cntl == "LUD")
    {
        c += 4;
        c->setW((int) val);
    }

    else if(cntl == "LLR")
    {
        c += 5;
        c->setW((int) val);
    }

    else if(cntl == "RUD")
    {
        c += 6;
        c->setW((int) val);
    }

    else if(cntl == "RLR")
    {
        c += 7;
        c->setW((int) val);
    }

    else if(cntl == "BEAT")
    {
        c += 8;
        c->setShow((bool) val);
    }
}

void Vel::draw()
{
    vector<Rect>::iterator c;
    for(c = v_controls.begin(); c != v_controls.end(); c++)
        c->draw();
}

void Vel::cleanup()
{

}

