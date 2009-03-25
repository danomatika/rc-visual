/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>

    Adapted from a class in the verybasicrenderclient, probably by Carl-Johan
==============================================================================*/
#include "Texture.h"

#include <string.h> // for memset

#include "ImageIO.h"

Texture::Texture() : _texID(0), _iBytesPerPixel((GLuint) EMPTY), _glDataType(0),
_iTexWidth(0), _iTexHeight(0), _fAspectRatio(0)
{}

Texture::~Texture()
{
    //clear();
}

Texture::Texture(const Texture& from)
{
    _texID = from._texID;
    _iBytesPerPixel = from._iBytesPerPixel;
    _glDataType = from._glDataType;
    _iTexWidth = from._iTexWidth;
    _iTexHeight = from._iTexHeight;
    _fAspectRatio = from._fAspectRatio;
}

Texture& Texture::operator=(const Texture& from)
{
    _texID = from._texID;
    _iBytesPerPixel = from._iBytesPerPixel;
    _glDataType = from._glDataType;
    _iTexWidth = from._iTexWidth;
    _iTexHeight = from._iTexHeight;
    _fAspectRatio = from._fAspectRatio;
    return *this;
}

bool Texture::allocate(int width, int height, GLTextureType glTexType)
{
    // bail if size is not power of 2
    if(width%2 != 0 || height%2 != 0)
    {
        LOG_ERROR << "Texture: Cannot allocate for non power of 2 sized image with w: "
                  << width << " h: " << height << ", ignoring" << std::endl;
        return false;
    }

	// attempt to free the previous bound texture, if we can
	clear();

    // set type
    _iBytesPerPixel = (GLuint) glTexType;
	switch(glTexType)
	{
		case RGB:
            _glDataType = GL_RGB;
            break;

		case RGBA:
			_glDataType = GL_RGBA;
            break;

		case LUMINANCE:
			_glDataType = GL_LUMINANCE;
            break;

        case EMPTY:
            _glDataType = GL_RGB;
            LOG_DEBUG << "Texture::allocate(): Ignoring allocation for GLTextureType EMPTY, using RGB instead" << std::endl;
            return false;
    }

	glGenTextures(1, &_texID);

	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texID);
		glTexImage2D(GL_TEXTURE_2D, 0, _glDataType, _iTexWidth, _iTexHeight,
            0, _iBytesPerPixel, GL_UNSIGNED_BYTE, 0);  // init to black...
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisable(GL_TEXTURE_2D);

    // check for gl error
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        LOG_DEBUG << "Texture::allocate(): GL Error: " << GLHelper::getErrorString(err) << std::endl;
    }

    _fAspectRatio = (float)_iTexWidth / (float)_iTexHeight;

    LOG_DEBUG << "Texture: Allocated texture for id: " << _texID << std::endl;
    LOG_DEBUG << "  _iBytesPerPixel:    " << _iBytesPerPixel << std::endl;
    LOG_DEBUG << "  _iTexWidth:         " << _iTexWidth << std::endl;
    LOG_DEBUG << "  _iTexHeight:        " << _iTexHeight << std::endl;
    LOG_DEBUG << "  _fAspectRatio:      " << _fAspectRatio << std::endl;

    return true;
}

void Texture::clear()
{
	// try to free up the texture memory so we don't reallocate
	// http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/gl/deletetextures.html
	if(_texID != 0)
	{
		glDeleteTextures(1, &_texID);
	}

    _iBytesPerPixel = EMPTY;
    _glDataType = 0;
	_iTexWidth = 0;
	_iTexHeight = 0;
	_fAspectRatio = 0;
}

bool Texture::loadImage(std::string filename)
{
    // free previous texture
	clear();

    // load image
	int iBitsPerPixel = 0;
	unsigned char* pucPixels = ImageIO::loadImage(filename, _iTexWidth, _iTexHeight, iBitsPerPixel);
	_iBytesPerPixel = iBitsPerPixel/8;   // convert FreeImage BitsPP to BytesPP
    if(pucPixels == NULL)
    {
        return false;
    }

    // bail if size is not power of 2
    if(_iTexWidth%2 != 0 || _iTexHeight%2 != 0)
    {
        LOG_ERROR << "Texture: Cannot load non power of 2 sized image \"" << filename
                  << "\" with w: " << _iTexWidth << " h: " << _iTexHeight << ", ignoring" << std::endl;
        delete [] pucPixels;
        return false;
    }

    // check bits per pixel
	switch(_iBytesPerPixel)
	{
		case 1:
			_glDataType = GL_LUMINANCE;
            break;

		case 3:
			_glDataType = GL_BGR;
            break;

		case 4:
			_glDataType = GL_BGRA;
            break;

        default:
            LOG_ERROR << "Texture::loadImage: bpp " << _iBytesPerPixel << " in \"" << filename
                      << "\" not supported, ignoring" << std::endl;
            delete [] pucPixels;
            clear();
            return false;
	}

    glGenTextures(1, &_texID);

    enable();

		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, _iBytesPerPixel, _iTexWidth, _iTexHeight,
            0, _glDataType, GL_UNSIGNED_BYTE, pucPixels);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        unbind();

    disable();

    delete [] pucPixels;

    // check for gl error
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        LOG_ERROR << "Texture::loadImage(): GL Error: " << GLHelper::getErrorString(err) << std::endl;
    }

    _fAspectRatio = (float)_iTexWidth / (float)_iTexHeight;

    LOG_DEBUG << "Texture: Loaded texture for id: " << _texID << " from file \"" << filename << "\"" << std::endl;
    LOG_DEBUG << "  _iBytesPerPixel:    " << _iBytesPerPixel << std::endl;
    LOG_DEBUG << "  _iTexWidth:         " << _iTexWidth << std::endl;
    LOG_DEBUG << "  _iTexHeight:        " << _iTexHeight << std::endl;
    LOG_DEBUG << "  _fAspectRatio:      " << _fAspectRatio << std::endl;

	return true;
}

void Texture::enable()
{
    glEnable(GL_TEXTURE_2D);
}

void Texture::disable()
{
    glDisable(GL_TEXTURE_2D);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, _texID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::draw(float x, float y, float width, float height)
{
	bind();

        glBegin(GL_QUADS);

            //glNormal3f(0, 0, 1);
            glTexCoord2f(0, 0); // bottom left
            glVertex2f((GLfloat) x-(width/2), (GLfloat) (y-(height/2)));

            //glNormal3f(0, 0, 1);
            glTexCoord2f(1, 0); // bottom right
            glVertex2f((GLfloat) x+(width/2), (GLfloat) (y-height/2));

            //glNormal3f(0, 0, 1);
            glTexCoord2f(1, 1); // top right
            glVertex2f((GLfloat) x+(width/2), (GLfloat) (y+height/2));

            //glNormal3f(0, 0, 1);
            glTexCoord2f(0, 1); // top left
            glVertex2f((GLfloat) (x-width/2), (GLfloat) (y+height/2));

        glEnd();

	unbind();
}

bool Texture::setImageData(void* data)
{
	bind();

    glTexImage2D(GL_TEXTURE_2D, 0, _iBytesPerPixel, _iTexWidth, _iTexHeight, 0, _glDataType, GL_UNSIGNED_BYTE, data);

    // check for gl error
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        LOG_ERROR << "Texture::setImageData(): GL Error: " << GLHelper::getErrorString(err) << std::endl;
    }

    // check if this is a valid texture
    if(!glIsTexture(_texID))
    {
        LOG_ERROR << "Texture: Could not create texture from pixel data, clearing" << std::endl;
        clear();
        return false;
    }

	unbind();

	return true;
}
