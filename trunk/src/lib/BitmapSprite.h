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
            std::vector<bool> bitmap;
        };

        BitmapSprite();

        virtual ~BitmapSprite();

        void update() {};

        void draw();

        void nextFrame();

        void prevFrame();

        void gotoFrame(uint frameIndex);

        inline void setSize(int physWidth, int physHeight);
        inline void setPixelSize(int w, int h) {_pixelW = w; _pixelH = h;}
        inline void setVisible(bool show) {_bIsVisible = show;}
        inline void setAnimate(bool animate) {_bAdvanceFrames = animate;}
        inline int getVirtualWidth() {return _spriteW;}
        inline int getVirtualHeight() {return _spriteH;}

        void print(std::string indent="");

        bool loadXml(TiXmlElement *xmlPtr);

    protected:

        bool getFrame(TiXmlElement* xmlPtr);

        std::vector<Frame*> _sprite;    /// sprite
        uint _frame;                     /// current frame

        int _spriteW, _spriteH; /// sprite x num virtual pixels
        int _pixelW, _pixelH;   /// physical dimension of a single virtual pixel

        bool _bAdvanceFrames;   /// go to next frame automatically?
        bool _bIsVisible;       /// show sprite?
};

#endif // BITMAPSPRITE_H
