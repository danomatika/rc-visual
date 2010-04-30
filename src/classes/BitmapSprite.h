#ifndef BITMAPSPRITE_H
#define BITMAPSPRITE_H

#include <vector>

#include "Common.h"
#include "Rectangle.h"

class BitmapSprite : public Rectangle
{
    public:

        struct Frame
        {
            std::vector<bool> frame;
            uint w, h;  // virtual pixel size
        };

        BitmapSprite();

        virtual ~BitmapSprite();

        void update() {};

        void draw();

    protected:

        std::vector<Frame> _frames;
        uint curFrame;
};

#endif // BITMAPSPRITE_H
