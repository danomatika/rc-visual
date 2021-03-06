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

Bitmap::Bitmap(string name, string parentOscAddress) :
	DrawableObject("bitmap", name, parentOscAddress), 
	bitmapWidth(1), bitmapHeight(1),
	pos(0, 0), width(1), height(1), pixelWidth(1), pixelHeight(1),
	bFilled(true), bDrawFromCenter(false)
{
	// add variables to Xml
	addXmlAttribute("width", "bitmap", XML_TYPE_UINT, &bitmapWidth);
	addXmlAttribute("height", "bitmap", XML_TYPE_UINT, &bitmapHeight);
	addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
	addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
	addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
	addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
	addXmlAttribute("yesno", "filled", XML_TYPE_BOOL, &bFilled);
	addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);
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

		visual::Graphics::stroke(color);
		
		if(bFilled)
			visual::Graphics::fill(color);
		else
			visual::Graphics::noFill();

		visual::Graphics::rectMode(visual::CORNER);
		
		for(unsigned int _y = 0; _y < bitmapHeight; ++_y)
		{
			for(unsigned int _x = 0; _x < bitmapWidth; ++_x)
			{
				if(bitmap.at(_y*bitmapWidth + _x))
					visual::Graphics::rectangle(xPos, yPos, pixelWidth, pixelHeight);
					
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

void Bitmap::setSize(unsigned int w, unsigned int h)
{
	width = w;
	height = h;
	computePixelSize();
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
			LOG << "       " << line << endl;

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
					default: // ignore
						break;
				}
				chars >> c;
			}
		}

		// correct size?
		if(bitmapWidth == 0)	bitmapWidth = 1;
		if(bitmapHeight == 0)	bitmapHeight = 1;
		if(numPix < bitmapWidth*bitmapHeight)
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
	if(bitmap.empty())
		return true;
		
	stringstream frame;
	frame << std::endl;

	// read through all the chars
	for(unsigned int y = 0; y < bitmapHeight; ++y)
	{
		for(unsigned int x = 0; x < bitmapWidth; ++x)
		{
			if(bitmap.at(y*bitmapWidth + x))
				frame << '*';	// filled
			else
				frame << '-';	// empty
		}
		frame << std::endl;
	}
	
	// find element, add if it dosen't exit
	TiXmlElement* child = Xml::obtainElement(e, "frame");
	Xml::setText(child, frame.str());

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
		computePixelSize();
		return true;
	}
	else if(message.path() == getOscRootAddress() + "/size/width")
	{
		message.tryNumber(&width, 0);
		computePixelSize();
		return true;
	}
	else if(message.path() == getOscRootAddress() + "/size/height")
	{
		message.tryNumber(&height, 0);
		computePixelSize();
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
