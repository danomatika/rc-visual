#ifndef SPRITE_H
#define SPRITE_H

#include <cmath>
#include <string>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL_gfxPrimitives.h>

using namespace std;

// a sprite
class Sprite
{
    public:

        Sprite(string name, int virt_width, int virt_height, int num_frames);

        virtual ~Sprite();

        void render(SDL_Surface *screen);

        void clear();

        void nextFrame();

        void prevFrame();

        void gotoFrame(int frame_index);

        void setSprite(bool *sprite_in);

        void setFrame(int frame, bool *sprite_in);

        void setPos(int x, int y);

        void setSize(int phys_width, int phys_height);

        void setColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A);

        void inline visible(bool show) {is_visible = show;};

        string inline getName() {return sprite_name;};

        int getWidth() {return width;};

        int getHeight() {return height;};

        void inline animate(bool animate) {advance_frames = animate;};

        void print();

    protected:

    private:
        bool *sprite;       // sprite as 2d array of bools, should only be 1 char per bool
        string sprite_name; // name of sprite

        Sint16 pos_x, pos_y;    // physical sprite position, upper right corner
        Sint16 width, height;   // physical sprite dimensions
        Uint8 r, g, b, a;       // sprite color and alpha

        int s_num_pix_x, s_num_pix_y;   // sprite x num virtual pixels
        int pix_w, pix_h;               // physical dimension of a single virtual pixel
        int s_num_pix_f;                // number of pixels in 1 frame

        int s_num_frames;       // number of frames in the sprite
        int frame;              // current frame number
        bool advance_frames;    // go to next frame automatically?
        bool is_visible;           // show sprite?
};

#endif // SPRITE_H
