/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>

    Adapted from a class in the verybasicrenderclient, probably by Carl-Johan
==============================================================================*/
#include "ImageIO.h"

#include "Common.h"

#include <FreeImagePlus.h>
#include <GL/gl.h>

#include <string.h> // for memcpy

unsigned char* ImageIO::loadImage(std::string filename, int &width, int &height, int &bpp)
{
	LOG_DEBUG << "ImageIO: Loading \"" << filename << "\"" << std::endl;

	fipImage image;

    if(!image.load(filename.c_str()))
    {
        LOG_ERROR << "ImageIO: Loading image \"" << filename << "\" failed" <<  std::endl;
		return NULL;
    }

    width = image.getWidth();
    height = image.getHeight();
    bpp = image.getBitsPerPixel();

    unsigned char* pucPixels = new unsigned char[image.getImageSize()];

	try
	{
		memcpy(pucPixels, image.accessPixels(), image.getImageSize());

        image.clear();
	}
	catch (...)
	{
        LOG_ERROR << "ImageIO::loadImage(): Copying image data \"" << filename << "\" failed" <<  std::endl;
        delete [] pucPixels;
		return NULL;
	}

	return pucPixels;
}

// only suitable for 32bit images!!!
// jpeg output only
bool ImageIO::saveImage(std::string filename, unsigned char* pixels, int width, int height, int bpp, FileType type)
{
    // set image type
    int iFlag = 0;
    switch(type)
    {
        case JPG:
            iFlag = JPEG_QUALITYGOOD;
            filename = filename + ".jpg";
            break;

        case PNG:
            iFlag = PNG_Z_DEFAULT_COMPRESSION;
            filename = filename + ".png";
            break;
    }

    LOG_DEBUG << "ImageIO: Saving \"" << filename << "\"" << std::endl;

    fipImage image;

    if(!image.setSize(FIT_BITMAP, width, height, bpp))
    {
        LOG_ERROR << "ImageIO::saveImage(): allocating \"" << filename << "\" failed" <<  std::endl;
		return false;
    }

	try
	{
		memcpy(image.accessPixels(), pixels, width*height*bpp/8);
	}
	catch (...)
	{
		LOG_ERROR << "ImageIO::saveImage(): Copying image data \"" << filename << "\" failed" << std::endl;
		return false;
	}

    if(!image.save(filename.c_str(), iFlag))
    {
        LOG_ERROR << "ImageIO::saveImage(): saving \"" << filename << "\" failed" <<  std::endl;
		return false;
    }

    return true;
}

bool ImageIO::saveScreenshot (std::string filename, int x, int y, int width, int height)
{
    unsigned char* pucPixels = new unsigned char [width * height * 3];

    glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, pucPixels);
	if(!saveImage(filename, pucPixels, width, height, 24, PNG))
	{
	    return false;
	}

    // cleanup
	delete [] pucPixels;

    return true;
}
