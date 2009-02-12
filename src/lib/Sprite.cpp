#include "Sprite.h"

Sprite::Sprite(string name, int virt_width, int virt_height, int num_frames)
{
    sprite_name = name;

    // default starting pos
    pos_x = 0;
    pos_y = 0;

    // default physical size
    height = 64;
    width = 64;

    // virtual sprite dimensions
    s_num_pix_x = virt_width;
    s_num_pix_y = virt_height;

    // physical dimensions of one virtual pixel
    pix_h = height/s_num_pix_y;
    pix_w = width/s_num_pix_x;

    // frames and num pixels per frame
    s_num_frames = num_frames;
    s_num_pix_f = s_num_pix_x*s_num_pix_y;
    frame = 0;  // start at frame 0

    // allocate sprite
    sprite = new bool[s_num_pix_f*s_num_frames];

    // animate by default
    advance_frames = false;

    // show by default
    is_visible = true;

    // default color is white, no transparency
    r = 255;
    g = 255;
    b = 255;
    a = 255;

    // clear the sprite to all zeros
    clear();
}

Sprite::~Sprite()
{
    //if(sprite != NULL)
    //    delete sprite;
}

void Sprite::render(SDL_Surface *screen)
{
    if(!is_visible) return;    // do nothing if hidden

    int offset = frame * s_num_pix_f;
    int px = pos_x, py = pos_y; // upper right corner phys pos  of virtual pixel

    // loop through pixels in the frame
    for(int y = 0; y < s_num_pix_y; y++)
    {
        for(int x = 0; x < s_num_pix_x; x++)
        {
            // render virtual pixel
            if(sprite[(x + y*s_num_pix_x) + offset] == true)
                boxRGBA(screen, px, py, px+pix_w-1, py+pix_h-1, r, g, b, a);
            px += pix_w;
        }
        px = pos_x;
        py += pix_h;
    }

    if(advance_frames)  // go to next frame?
    {
        frame ++;
        if(frame >= s_num_frames)
        frame = 0;
    }
}

void Sprite::nextFrame()
{
    frame ++;
    if(frame >= s_num_frames)
        frame = 0;
}

void Sprite::prevFrame()
{
    frame --;
    if(frame < 0)
        frame = s_num_frames;
}

void Sprite::gotoFrame(int frame_index)
{
    if(frame_index >= 0 && frame_index > s_num_frames)
    {
        frame = frame_index;
        return;
    }

    cout << "Sprite \"" << sprite_name << "\": invalid frame index: \"" << frame_index << "\"" << endl;
}

void Sprite::clear()
{
    // write all zeros
    for(int f = 0; f < s_num_pix_f*s_num_frames; f++)
        sprite[f] = false;
}

void Sprite::setSprite(bool *sprite_in)
{
    if(sprite != NULL)  delete sprite;
        sprite = sprite_in;
}

void Sprite::setFrame(int frame, bool *sprite_in)
{
    int offset = frame * s_num_pix_f;
    for(int p = 0; p < s_num_pix_f; p++)
        sprite[p+offset] = sprite_in[p];
}

void Sprite::setPos(int x, int y)
{
    pos_x = x;
    pos_y = y;
}

void Sprite::setSize(int phys_width, int phys_height)
{
    height = phys_height;
    width = phys_width;

    // recalc physical dimensions of one virtual pixel
    pix_h = height/s_num_pix_y;
    pix_w = width/s_num_pix_x;
}

void Sprite::setColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    r = R;
    g = G;
    b = B;
    a = A;
}

void Sprite::print()
{
    cout << sprite_name << endl
         << "w: " << width << " h: " << height << endl
         << "x: " << pos_x << " y: " << pos_y << endl
         << "r: " << (int) r << " g: " << (int) g << " b: " << (int) b << " a: " << (int) a << endl
         << "frames: " << s_num_frames << " animate: " << advance_frames << " visible: " << is_visible << endl
         << endl;

    int px = pos_x, py = pos_y; // upper right corner phys pos  of virtual pixel

    // loop through frames
    for(int f = 0; f < s_num_frames; f++)
    {
        // loop through pixels in the frame
        for(int y = 0; y < s_num_pix_y; y++)
        {
            for(int x = 0; x < s_num_pix_x; x++)
            {
                // render virtual pixel
                if(sprite[(x + y*s_num_pix_x) + f*s_num_pix_f] == true)
                    cout << '*';
                else
                    cout << '-';
                cout << ' ';
                px += pix_w;
            }
            px = pos_x;
            py += pix_h;
            cout << endl;
        }
        cout << endl;
    }
}
