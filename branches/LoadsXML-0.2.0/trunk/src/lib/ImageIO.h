/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>

    Adapted from a class in the verybasicrenderclient, probably by Carl-Johan
==============================================================================*/
#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <string>

/**
    \class ImageIO
    \brief provides functions for loading and saving images

    uses the FreeImage library:
        * http://freeimage.sourceforge.net/
        * FreeImagePlus api doc: http://freeimage.sourceforge.net/fip/index.html
        * Ubuntu package: libfreeimage-dev
**/
class ImageIO
{
    public:

        enum FileType
        {
            JPG,
            PNG
        };

        /**
            \brief  load an image and return the pixel data

            \param  filename    name of image file to load
            \param  width       width of image in pixels
            \param  height      height of image in pixels
            \param  bpp         bits per pixel

            \return pixel data on success, NULL on failure

            Note: width, height, and bpp are passed by reference to write in the values
            on load
        **/
        static unsigned char* loadImage(std::string filename, int &width, int &height, int &bbp);

        /**
            \brief  save an image

            \param  filename    name of image file to save without extension
            \param  pixels      pixel data
            \param  width       width of image in pixels
            \param  height      height of image in pixels
            \param  type        JPG or PNG

            \return true on success, false on failure
        **/
        static bool saveImage(std::string filename, unsigned char* pixels, int width, int height, int bpp, FileType type);

        /**
            \brief  save a screenshot using glReadPixels

            \param  filename    name of image file to save without extension
            \param  pixels      pixel data
            \param  x           corner coordinate
            \param  y           corner coordinate
            \param  width       width of the screen area
            \param  height      height of the screen area

            \return true on success, false on failure
        **/
        static bool saveScreenshot (std::string filename, int x, int y, int width, int height);
};

#endif //IMAGEIO_H
