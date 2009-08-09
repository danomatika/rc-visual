#include "glTexture.h"

glTexture::glTexture()
{
    loaded_ = false;
    h = 0;
    w = 0;
}

glTexture::glTexture(string filename)
{
    loaded_ = false;
    h = 0;
    w = 0;
    load(filename);
}

glTexture::~glTexture()
{
    //dtor
}

// from http://gpwiki.org/index.php/SDL:Tutorials:Using_SDL_with_OpenGL
bool glTexture::load(string _filename)
{
    SDL_Surface *image;	// This surface will tell us the details of the image
    GLenum texture_format;
    GLint nOfColors;

    if(image = IMG_Load(_filename.c_str()))//SDL_LoadBMP(filename.c_str()))
    {
        /*
        // Check that the image's width is a power of 2
        if((image->w & (image->w - 1)) != 0)
            cout << "load texture warning: " << filename << "'s width is not a power of 2" << endl;

        // Also check if the height is a power of 2
        if((image->h & (image->h - 1)) != 0)
            cout << "load texture warning: " << filename << "'s height is not a power of 2" << endl;
        */
        // get the number of channels in the SDL surface
        nOfColors = image->format->BytesPerPixel;
        if(nOfColors == 4)     // contains an alpha channel
        {
            if(image->format->Rmask == 0x000000ff)
                texture_format = GL_RGBA;
            else
                texture_format = GL_BGRA;
        }
        else if(nOfColors == 3)     // no alpha channel
        {
            if(image->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        }
        else
        {
            cout << "load texture warning: " << _filename << " is not truecolor..  this will probably break" << endl;
            // this error should not go unhandled
            SDL_FreeSurface(image);
            return false;
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures(1, &texture);

        // Bind the texture object
        glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);

        // Set the texture's stretching properties
        glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, nOfColors, image->w, image->h, 0,
                          texture_format, GL_UNSIGNED_BYTE, image->pixels);
    }
    else
    {
        cout << "SDL_image could not load " << _filename << ": "<< SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    // Free the SDL_Surface only if it was successfully created
    if(!image)
        return false;

    h = image->h;
    w = image->w;
    SDL_FreeSurface(image);
    loaded_ = true;
    filename = _filename;

    return true;
}

void glTexture::clear()
{
    glDeleteTextures(1, &texture);
}

void glTexture::print()
{
    if(!loaded_)
        return;

    cout << filename << endl
         << "   w: " << w << endl
         << "   h: " << h << endl
         << "   a: " << (float) w/h << endl;
}
