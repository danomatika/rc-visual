#ifndef SPRITE_H
#define SPRITE_H

#include <cmath>
#include <string>
#include <iostream>
#include <vector>

#include "Common.h"
#include <SDL/SDL_gfxPrimitives.h>


// a sprite
class Sprite
{
    public:

        class Frame
        {
            public:
            Frame() {}

            Frame(const Frame& from)
            {
                bitmap = from.bitmap;
            }

            Frame operator=(const Frame& from)
            {
                bitmap = from.bitmap;
                return *this;
            }

            std::vector<bool> bitmap;
        };

        Sprite();

        virtual ~Sprite();

        bool allocate(int virt_width, int virt_heught, int num_frames);

        void render(SDL_Surface* screen);

        void clear();

        void nextFrame();

        void prevFrame();

        void gotoFrame(int frame_index);

        //void setSprite(bool *sprite_in);

        void addFrame(std::vector<bool> frame);

        // data sets
        void setName(std::string name) {sprite_name = name;};
//        void setNumFrames(int num)  {s_num_frames = num;};
        void setPos(int x, int y);
        void setSize(int phys_width, int phys_height);
        void setVirtualSize(int w, int h) {pix_w = w; pix_h = h;}
        void setColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A);

        void inline visible(bool show) {is_visible = show;};
        void inline animate(bool animate) {advance_frames = animate;};

        // data gets
        std::string inline getName() {return sprite_name;};
        int getWidth() {return width;};
        int getHeight() {return height;};
        int getVirtualWidth() {return s_num_pix_x;}
        int getVirtualHeight() {return s_num_pix_y;}
  //      int getNumFrames()  {return s_num_frames;}

        void print();


    protected:

    private:
        std::vector<Frame*>  sprite;     // sprite as 2d array of bools, should only be 1 char per bool
        std::string sprite_name; // name of sprite

        Sint16 pos_x, pos_y;    // physical sprite position, upper right corner
        Sint16 width, height;   // physical sprite dimensions
        Uint8 r, g, b, a;       // sprite color and alpha

        int s_num_pix_x, s_num_pix_y;   // sprite x num virtual pixels
        int pix_w, pix_h;               // physical dimension of a single virtual pixel
        int s_num_pix_f;                // number of pixels in 1 frame

        //int s_num_frames;       // number of frames in the sprite
        int frame;              // current frame number
        bool advance_frames;    // go to next frame automatically?
        bool is_visible;           // show sprite?
};

#endif // SPRITE_H
