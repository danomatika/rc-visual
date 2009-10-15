#ifndef ARPNOW_H
#define ARPNOW_H

#include <iostream>
#include <string>
#include <vector>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Visual.h"

using namespace std;

class ArpNow: public Visual
{
    public:

        ArpNow();

        virtual ~ArpNow();

        void setup(int screen_w_, int screen_h_);

        void update(string cntl, float val);

        void draw();

        void cleanup();

    protected:

    private:
        int screen_w;
        int screen_h;
        vector<Rect>    v_controls;
};

#endif // ARPNOW_H
