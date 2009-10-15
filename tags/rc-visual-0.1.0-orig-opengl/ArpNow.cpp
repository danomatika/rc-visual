#include "ArpNow.h"


ArpNow::ArpNow()
{
    //ctor
}

ArpNow::~ArpNow()
{
    //dtor
}

void ArpNow::setup(int screen_w_, int screen_h_)
{
    screen_w = screen_w_;
    screen_h = screen_h_;

    Rect *r = new Rect(0, 0, 800, 600);
    Color *c = new Color(1.0, 1.0, 0);
    r->setColor(c);
    r->setShow(false);
    v_controls.push_back(*r);

    r = new Rect(0, 0, 160, 0);
    c = new Color(1.0, 0, 0);
    r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(160, 0, 160, 50);
    c = new Color(0, 1.0, 0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(320, 0, 160, 50);
    c = new Color(0, 0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(480, 0, 160, 0);
    c = new Color(0, 1.0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(640, 0, 160, 0);
    c = new Color(1.0, 0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    cout<< "ArpNow Num: " << v_controls.size() << endl;
}

void ArpNow::update(string cntl, float val)
{
    vector<Rect>::iterator c = v_controls.begin();

    if(cntl == "voice6")
        c->setShow((bool) val);

    else if(cntl == "voice1")
    {
        c += 1;
        c->setH((int) val);
    }

    else if(cntl == "voice2")
    {
        c += 2;
        c->setY((int) val);
    }

    else if(cntl == "voice3")
    {
        c += 3;
        c->setY((int) val);
    }

    else if(cntl == "voice4")
    {
        c += 4;
        c->setH((int) val);
    }

    else if(cntl == "voice5")
    {
        c += 5;
        c->setH((int) val);
    }
}

void ArpNow::draw()
{
    vector<Rect>::iterator c;
    for(c = v_controls.begin(); c != v_controls.end(); c++)
        c->draw();
}

void ArpNow::cleanup()
{

}

