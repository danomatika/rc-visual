#ifndef SDLCONTEXT_H
#define SDLCONTEXT_H

#include <iostream>
#include <string>

#include <SDL/SDL.h>

#include "Common.h"

class SdlContext
{
    public:

        enum Mode {
            WINDOW = 0,
            FULLSCREEN = SDL_FULLSCREEN
        };

        enum Type {
            UNKOWN      = 0,
            SOFTWARE    = SDL_SWSURFACE,
            HARDWARE    = SDL_HWSURFACE,
            OPENGL      = SDL_OPENGL
        };

        SdlContext(int w, int h, int depth, Type type=HARDWARE);

        virtual ~SdlContext();

        bool init();

        bool createWindow(std::string title);

        void inline setWindow()     {_mode = WINDOW;};
        void inline setFullscreen() {_mode = FULLSCREEN;};

        // global gets
        static const Type getType() {return _type;}
        static SDL_Surface* getScreen() {return _screen;}
        static const int getWidth()   {return _iWidth;}
        static const int getHeight()  {return _iHeight;}
        static const int getDepth()   {return _iDepth;}

    protected:

    private:

        bool initSDL();

        bool initOpenGL();

        static SDL_Surface* _screen;   /// SDL draw surface

        static int _iWidth;         /// window width
        static int _iHeight;        /// window height
        static int _iDepth;         /// bit depth
        Uint32 _ui32VideoFlags;     /// sdl video mode flags
        Mode _mode;                 /// context mode, WINDOW or FULLSCREEN
        static Type _type;          /// context type
        std::string _sTitle;        /// window title
};

#endif // SDLCONTEXT_H
