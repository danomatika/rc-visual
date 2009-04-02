/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

#include "Common.h"

#include "Rectangle.h"
#include "Texture.h"

class Sprite : public Rectangle
{
    public:

        Sprite() : Rectangle(), _curTex(0) {}

        Sprite(float x, float y, float w, float h, float vx=0, float vy=0) :
            Rectangle(x, y, w, h, vx, vy), _curTex(0) {}

        virtual ~Sprite() {}

        //Sprite(const Sprite& from);

		//Sprite& operator=(const Sprite& from);

        virtual void update() {}

        virtual void draw();

        /// load an image and add it to the texture vector
        bool loadImage(std::string filename);

        /// use the next texutre in the vector, wraps
        void nextFrame();

        /// use the prev texture in the vector, wraps
        void prevFrame();

        /// go to a specific texture in the vector, ignores bad values
        void goToFrame(uint8_t frame);

    protected:

        std::vector<Texture> _vTextures;

        uint8_t _curTex;    // current texture in the vector
};

#endif // SPRITE_H
