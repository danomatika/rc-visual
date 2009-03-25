/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>

    Adapted from a class in the verybasicrenderclient, probably by Carl-Johan
==============================================================================*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common.h"
#include "Object.h"

/**
    \class Texture
    \brief a class to load and display an openGL texture with optional white border
**/
class Texture
{
	public:

        enum GLTextureType
        {
            EMPTY = 0,
            RGB = 3,
            RGBA = 4,
            LUMINANCE = 1
        };

		Texture();

		virtual ~Texture();

        /// copy constructor
		Texture(const Texture& from);

        /// copy assignment
		Texture& operator=(const Texture& from);

        /// deallocates memory
        void clear();

        /// load an image, handles allocation automatically
        bool loadImage(std::string filename);

        /// allocate space for an image
        bool allocate(int width, int height, GLTextureType glTexType);

        /// set the image data, assumes allocate was called
        bool setImageData(void* data);

		/// draws from the center on a quad, set the size
		void draw(float x, float y, float width, float height);

		/// glBind, unbind texture
		void bind();
		void unbind();

        /// glEnable, glDisable texture
		static void enable();
		static void disable();

		/// data get
		float getAspect() {return _fAspectRatio;}

	protected:

		GLuint  _texID;         /// texture id
		GLuint  _iBytesPerPixel;/// GL_TEXTURE_RECTANGLE_2D or GL_TEXTURE_RECTANGLE_ARB
        GLuint  _glDataType;    /// texture data type: GL_RGB, GL_LUMINANCE, or GL_RGBA

		int _iTexWidth, _iTexHeight;    /// image dimensions (ie 320x240)
		float _fAspectRatio;            /// image aspect ratio, W/H
};

#endif // TEXTURE_H
