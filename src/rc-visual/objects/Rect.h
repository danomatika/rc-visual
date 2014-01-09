/*==============================================================================

	Rect.h

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
#ifndef RECT_H
#define RECT_H

#include "Config.h"

#include "DrawableObject.h"

class Rect : public DrawableObject
{
	public:

		Rect(string name, string parentOscAddress) :
			DrawableObject("rect", name, parentOscAddress), pos(0, 0),
			width(1), height(1), bFilled(true), bDrawFromCenter(0)
		{
			// add variables to Xml
			addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
			addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
			addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
			addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
			addXmlAttribute("yesno", "filled", XML_TYPE_BOOL, &bFilled);
			addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);
		}

		void draw()
		{
			if(bVisible)
			{
				visual::Graphics::stroke(color);

				if(bFilled)
					visual::Graphics::fill(color);
				else
					visual::Graphics::noFill();
					
				if(bDrawFromCenter)
					visual::Graphics::rectMode(visual::CENTER);
				else
					visual::Graphics::rectMode(visual::CORNER);

				visual::Graphics::rectangle(pos.x, pos.y, width, height);
			}
		}
		
		string getType() {return "rect";}

	protected:

		bool processOscMessage(const osc::ReceivedMessage& message,
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
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/size/width")
			{
				message.tryNumber(&width, 0);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/size/height")
			{
				message.tryNumber(&height, 0);
				return true;
			}


			else if(message.path() == getOscRootAddress() + "/filled")
			{
				message.tryBool(&bFilled, 0);
				return true;
			}
			
			else if(message.path() == getOscRootAddress() + "/center")
			{
				message.tryBool(&bDrawFromCenter, 0);
				return true;
			}


			return false;
		}

		visual::Point pos;
		unsigned int width, height;
		bool bFilled;
		bool bDrawFromCenter;       /// draw from the center using pos
};


#endif // RECT_H
