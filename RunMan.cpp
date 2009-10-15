#include "RunMan.h"


RunMan::RunMan()
{
    //ctor
}

RunMan::~RunMan()
{
    //dtor
}

void RunMan::setup(int screen_w_, int screen_h_)
{
    screen_w = screen_w_;
    screen_h = screen_h_;

    Rect *r = new Rect(0, 0, screen_w, screen_h);
    Color *c = new Color(1.0, 1.0, 1.0);
    r->setColor(c);
    r->setShow(false);
    v_controls.push_back(*r);

    r = new Rect(0, 0, 20, 120);
    c = new Color(1.0, 1.0, 0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(0, 120, 20, 120);
    c = new Color(1.0, 0, 0);
    r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(0, 240, 20, 120);
    c = new Color(0, 1.0, 0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(0, 360, 20, 120);
    c = new Color(0, 0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(0, 480, 20, 120);
    c = new Color(0, 1.0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    r = new Rect(600, 500, 200, 200);
    c = new Color(1.0, 0, 1.0);
     r->setColor(c);
    v_controls.push_back(*r);

    cout<< "RunMan Num: " << v_controls.size() << endl;
}

void RunMan::update(string cntl, float val)
{
    vector<Rect>::iterator c = v_controls.begin();

    if(cntl == "key")
    {
        if(val == 1)
            c->setShow(true);
        else
            c->setShow(false);
    }

    else if(cntl == "string1")
    {
        c += 1;
        c->setW((int) val);
    }

    else if(cntl == "string2")
    {
        c += 2;
        c->setW((int) val);
    }

    else if(cntl == "string3")
    {
        c += 3;
        c->setW((int) val);
    }

    else if(cntl == "string4")
    {
        c += 4;
        c->setW((int) val);
    }

    else if(cntl == "string5")
    {
        c += 5;
        c->setW((int) val);
    }

    else if(cntl == "string6")
    {
        c += 6;
        c->setY((int) val);
    }
}

void RunMan::draw()
{
    vector<Rect>::iterator c;
    for(c = v_controls.begin(); c != v_controls.end(); c++)
        c->draw();
}

void RunMan::cleanup()
{

}

