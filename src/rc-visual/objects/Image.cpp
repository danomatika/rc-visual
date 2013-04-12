/*==============================================================================

	Image.cpp

	rc-visual: a simple, osc-controlled 2d graphics engine
  
	Copyright (C) 2007, 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "Image.h"

Image::Image(string name, string parentOscAddress) :
	DrawableObject("image", name, parentOscAddress), image(NULL),
    pos(0, 0), width(0), height(0), bDrawFromCenter(false)
{
    // add variables to Xml
    addXmlAttribute("file", "image", XML_TYPE_STRING, &filename);
    addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
    addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
    addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
    addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
    addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);

    // detach unneeded variables from Xml
	removeXmlElement("color");
}

bool Image::loadFile(string filename)
{
	if(filename == "")
    	filename = this->filename;
	
	if(!Config::instance().getResourceManager().addImage(filename, visual::Util::toDataPath(filename)))
	{
		LOG_WARN << "Image: \"" << name << "\" couldn't load \""
				 << filename << "\"" << std::endl;
    	return false;
	}
	image = Config::instance().getResourceManager().getImage(filename);

    if(width == 0)	width = image->width();
    if(height == 0) height = image->height();
	
	LOG << "Image: loaded \"" << filename << "\" "
			  << width << "x" << height << endl;
		  
   resizeIfNecessary();

    return true;
}

void Image::setup()
{
	if(Config::instance().getResourceManager().imageExists(filename))
	{
		image = Config::instance().getResourceManager().getImage(filename);
	}
	else {
		loadFile();
	}
}

void Image::draw()
{
    draw(pos.x, pos.y);
}

void Image::draw(int x, int y)
{
    if(!image || !image->isLoaded())
        return;

    if(bVisible)
    {
        if(bDrawFromCenter)
            visual::Graphics::textureMode(visual::CENTER);
        else
            visual::Graphics::textureMode(visual::CORNER);

        image->draw(x, y);
    }    
}

void Image::setSize(unsigned int w, unsigned int h)
{
	width = w;
	height = h;
	resizeIfNecessary();
}

/* ***** PROTECTED ***** */

void Image::resizeIfNecessary()
{
	 // resize if needed
    if(image->width() != width || image->height() != height)
    {
    	LOG_DEBUG << "Image: \"" << name << "\" resized to "
        		  << width << "x" << height << std::endl;
        image->resize(width, height);
    }
}

bool Image::readXml(TiXmlElement* e)
{
    return true;
}

bool Image::writeXml(TiXmlElement* e)
{
    return true;
}

bool Image::processOscMessage(const osc::ReceivedMessage& message,
							  const osc::MessageSource& source)
{
    // call the base class
    if(DrawableObject::processOscMessage(message, source))
    {
        return true;
    }


    if(message.path() == getOscRootAddress() + "/position")
    {
		message.tryNumber(&pos.x, 0);
		message.tryNumber(&pos.y, 1);
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/position/x")
    {
        message.tryNumber(&pos.x, 0);
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/position/y")
    {
        message.tryNumber(&pos.y, 0);
        return true;
    }
	
	
	else if(message.path() == getOscRootAddress() + "/size")
    {
    	message.tryNumber(&width, 0);
    	message.tryNumber(&height, 1);
        resizeIfNecessary();
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/size/width")
    {
    	message.tryNumber(&width, 0);
        resizeIfNecessary();
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/size/height")
    {
    	message.tryNumber(&height, 0);
        resizeIfNecessary();
        return true;
    }


    else if(message.path() == getOscRootAddress() + "/center" &&
    		message.types() == "i")
    {
		message.tryBool(&bDrawFromCenter, 0);
        return true;
    }

    return false;
}
