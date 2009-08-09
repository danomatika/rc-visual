#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include<iostream>
#include<string>

#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>

using namespace std;

class glTexture
{
    public:
        glTexture();

        glTexture(string filename);

        virtual ~glTexture();

        bool load(string filename);

        void clear();

        void print();

        bool inline loaded() {return loaded_;};

        GLuint texture;  // texture handle
        int h, w;  // texture dimensions

    protected:

    private:
        bool loaded_;
        string filename;
};

#endif // GLTEXTURE_H
