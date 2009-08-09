#include <cstdlib>
#include <SDL.h>

#include "../../Sprite.h"

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // create a new sprite
    Sprite sprite1("s1", 4, 4, 2);
    bool s1 [4*4*2] = {
        1,0,0,1,
        1,0,0,1,
        0,1,1,0,
        0,1,1,0,

        0,1,1,0,
        0,1,1,0,
        1,0,0,1,
        1,0,0,1};
    sprite1.setSprite(s1);
    sprite1.setSize(640, 480);
    sprite1.animate(true);


    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        sprite1.render(screen);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        usleep(200000);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
