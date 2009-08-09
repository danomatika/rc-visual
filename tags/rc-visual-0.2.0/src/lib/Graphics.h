#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include <SDL/SDL.h>

class Graphics
{
    public:

        static bool isTypeUnknown();

        static bool isTypeSDL();

        static bool isTypeOGL();

        /** \name Data Gets **/
        static int getWidth();
        static int getHeight();

        /** \name SDL Functions **/

        static SDL_Surface* getSDLScreen();

        /** \name GL Functions **/

        /// enables GL Alpha Blending
        static void enableOGLAlphaBlending();

        /// disables GL blending
        static void disableOGLBlending();

        static void enableOGLRaster2D();

        static void disableOGLRaster2D();

        /// inits GLEW and prints version
//        static bool initGLEW();

        /// returns a string if there is a gl error
        static std::string getErrorString(int error);

        /// draw the viewport as a box
        static void drawViewPort();
};

#endif // GRAPHICS_H
