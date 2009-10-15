#ifndef VISUAL_H
#define VISUAL_H

#include <iostream>
//#include <string>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

// template class for visual selections
class Visual
{
    public:

        Visual();

        virtual ~Visual();

        void setup(int screen_w_, int screen_h_);

        void draw();

        virtual void update();

        void cleanup();

    protected:

        void rect(int x, int y, int w, int h);

        int screen_w;
        int screen_h;

    private:
};

// class for colors
class Color
{
    public:

        Color() {r = 0; g = 0; b = 0;};

        Color(float r_, float g_, float b_) {r = r_; g = g_; b = b_;};

        virtual ~Color() {};

        void inline set(float r_, float g_, float b_) {r = r_; g = g_; b = b_;};
        void inline setR(float r_) {r = r_;}
        void inline setG(float g_) {g = g_;}
        void inline setB(float b_) {b = b_;}

        float inline getR() {return r;}
        float inline getG() {return g;}
        float inline getB() {return b;}

    protected:
        float r;
        float g;
        float b;

    private:
};


// class for coordinates
class Coord
{
    public:

        Coord() {x = 0; y = 0;};

        Coord(int x_, int y_) {x = x_; y = y_;};

        virtual ~Coord() {};

        void inline set(int x_, int y_) {x = x_; y = y_;};
        void inline setX(int x_) {x = x_;};
        void inline setY(int y_) {y = y_;};

        int inline getX(void) {return x;};
        int inline getY() {return y;};

        void update();

        void cleanup();

    protected:
        int x;
        int y;

    private:
};

// class for rectangles
class Rect
{
    public:

        Rect() { x = 0; y = 0; w = 0; y = 0; c = new Color(1.0, 1.0, 1.0); show = true;};

        Rect(int x_, int y_, int w_, int h_)
            {x = x_; y = y_; w = w_; h = h_;  c = new Color(1.0, 1.0, 1.0); show = true;};

        virtual ~Rect() {};

        void inline set(int x_, int y_, int w_, int h_)
            {x = x_; y = y_; w = w_; h = h_;};
        void inline setX(int x_) {x = x_;};
        void inline setY(int y_) {y = y_;};
        void inline setW(int w_) {w = w_;};
        void inline setH(int h_) {h = h_;};

        void inline setColor(Color *c_) {c = c_;}

        void inline setShow(bool show_) {show = show_;};

        int inline getX() {return x;};
        int inline getY() {return y;};
        int inline getW() {return w;};
        int inline getH() {return h;};

        void draw();

    protected:
        int x;
        int y;
        int w;
        int h;
        Color *c;
        bool show;

    private:
};

#endif
