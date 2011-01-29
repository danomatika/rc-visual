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

Image::Image(string name) : DrawableObject("image"), frameTime(0),
    pos(0, 0), width(0), height(0), bDrawFromCenter(false)
{
    // add variables to Xml
    addXmlAttribute("name", "image", XML_TYPE_STRING, &name);
    addXmlAttribute("file", "image", XML_TYPE_STRING, &filename);
    addXmlAttribute("frametime", "image", XML_TYPE_UINT, &frameTime);
    addXmlAttribute("x", "position", XML_TYPE_INT, &pos.x);
    addXmlAttribute("y", "position", XML_TYPE_INT, &pos.y);
    addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
    addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
    addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);

    // detach variables from Xml
    removeXmlAttribute("R", "color");
    removeXmlAttribute("G", "color");
    removeXmlAttribute("B", "color");
    removeXmlAttribute("A", "color");

    setName(name);
}

Image::~Image()
{}

bool Image::loadFile(string filename)
{
	if(filename == "")
    	filename = this->filename;
       
	image.load(visual::Util::toDataPath(filename));
    if(!image.isLoaded())
    	return false;
        
    if(width == 0)	width = image.width();
    if(height == 0) height = image.height();
        
    // resize if needed
    if(image.width() != (int) width || image.height() != (int) height)
    {
    	LOG_DEBUG << "Image: \"" << name << "\" resized to "
        		  << width << "x" << height << std::endl;
        image.resize(width, height);
    }

    return true;
}

void Image::setup()
{
	loadFile();
}

void Image::draw()
{
    draw(pos.x, pos.y);
}

void Image::draw(int x, int y)
{
    if(!image.isLoaded())
        return;

    if(bVisible)
    {
        if(bDrawFromCenter)
            visual::Graphics::imageMode(visual::CENTER);
        else
            visual::Graphics::imageMode(visual::CORNER);

        image.draw(x, y);
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


    if(message.path() == getOscRootAddress() + "/position" &&
    	message.types() == "ii")
    {
        pos.x = message.asInt32(0);
        pos.y = message.asInt32(1);
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/position/x" &&
    		message.types() == "i")
    {
        pos.x = message.asInt32(0);
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/position/y" &&
    		message.types() == "i")
    {
        pos.y = message.asInt32(0);
        return true;
    }


    else if(message.path() == getOscRootAddress() + "/center" &&
    		message.types() == "i")
    {
        bDrawFromCenter = message.asBool(0);
        return true;
    }

    return false;
}
