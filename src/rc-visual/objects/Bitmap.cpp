/*==============================================================================

	Bitmap.cpp

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
#include "Bitmap.h"

#include <sstream>

using namespace visual;

Bitmap::Bitmap(string name) : DrawableObject("bitmap"), 
	bitmapWidth(1), bitmapHeight(1), frameTime(0),
    pos(0, 0), width(1), height(1), pixelWidth(1), pixelHeight(1),
    bFilled(true), bDrawFromCenter(false)
{
    // add variables to Xml
    addXmlAttribute("frametime", "bitmap", XML_TYPE_UINT, &frameTime);
    addXmlAttribute("width", "bitmap", XML_TYPE_UINT, &bitmapWidth);
    addXmlAttribute("height", "bitmap", XML_TYPE_UINT, &bitmapHeight);
    addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
    addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
    addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
    addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
    addXmlAttribute("yesno", "filled", XML_TYPE_BOOL, &bFilled);
    addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);

    setName(name);
}

void Bitmap::draw()
{
    draw(pos.x, pos.y);
}

void Bitmap::draw(int x, int y)
{
    if(bitmap.empty())
        return;

    if(bVisible)
    {
        int xPos = x, yPos = y;

        if(bDrawFromCenter)
        {
            xPos = xPos - width/2;
            yPos = yPos - height/2;
        }

        Graphics::stroke(color);
        
        if(bFilled)
        	Graphics::fill(color);
        else
        	Graphics::noFill();

		Graphics::rectMode(CORNER);
        
        for(unsigned int _y = 0; _y < bitmapHeight; ++_y)
        {
            for(unsigned int _x = 0; _x < bitmapWidth; ++_x)
            {
                if(bitmap.at(_y*bitmapWidth + _x))
                	Graphics::rectangle(xPos, yPos, pixelWidth, pixelHeight);
                    
                xPos += pixelWidth;
            }
            
            if(bDrawFromCenter)
            	xPos = x - width/2;
            else
            	xPos = x;
                
            yPos += pixelHeight;
        }
    }
}

/* ***** PROTECTED ***** */

void Bitmap::computePixelSize()
{
	pixelWidth = width/bitmapWidth;
    pixelHeight = height/bitmapHeight;
}

bool Bitmap::readXml(TiXmlElement* e)
{
    TiXmlElement* child = Xml::getElement(e, "frame");
    if(child != NULL)
    {    
        stringstream frame(Xml::getText(child));
        string line;
        unsigned int numPix = 0;

        // read through all the chars
        while(!frame.eof())
        {
            frame >> line;
            cout << "       " << line << endl;

            stringstream chars(line);

            char c;
            chars >> c;
            while(!chars.eof())
            {
                switch(c)
                {
                    case '*':   // filled
                        bitmap.push_back(true);
                        numPix++;
                        break;
                    case '-':   // empty
                        bitmap.push_back(false);
                        numPix++;
                        break;
                    default:
                        break;
                }
                chars >> c;
            }
        }

        // correct size?
        if(numPix != bitmapWidth*bitmapHeight)
        {
            LOG_WARN << "Bitmap: Not enough pixels in frame: " << numPix
                     << ", need " << bitmapWidth*bitmapHeight << std::endl;
            bitmap.clear();
            return false;
        }
        
        computePixelSize();
    }

    return true;
}

bool Bitmap::writeXml(TiXmlElement* e)
{
    stringstream frame;
    frame << std::endl;  // endl

    // read through all the chars
    for(unsigned int y = 0; y < height; ++y)
    {
        for(unsigned int x = 0; x < width; ++x)
        {
            if(bitmap[y*width + x])
                frame << '*';   // filled
            else
                frame << '-';      // empty
        }
        frame << std::endl;  // endl
    }

    return true;
}

bool Bitmap::processOscMessage(const osc::ReceivedMessage& message,
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
    

    else if(message.path() == getOscRootAddress() + "/size" &&
    		message.types() == "ii")
    {
        width = message.asInt32(0);
        height = message.asInt32(1);
        computePixelSize();
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/size/width" &&
    		message.types() == "i")
    {
        width = message.asInt32(0);
        computePixelSize();
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/size/height" &&
    		message.types() == "i")
    {
        height = message.asInt32(0);
        computePixelSize();
        return true;
    }


    else if(message.path() == getOscRootAddress() + "/center" &&
    		message.types() == "i")
    {
        bDrawFromCenter = (bool) message.asInt32(0);
        return true;
    }


    return false;
}
