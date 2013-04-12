/*==============================================================================

	Pixel.h

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
#ifndef PIXEL_H
#define PIXEL_H

#include "Config.h"

#include "DrawableObject.h"

class Pixel : public DrawableObject
{
    public:

        Pixel(string name, string parentOscAddress) :
			DrawableObject("pixel", name, parentOscAddress), pos(0, 0)
        {
            // add variables to Xml
            addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
            addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
        }

        void draw()
        {
            if(bVisible)
            {
                visual::Graphics::stroke(color);
                visual::Graphics::point(pos.x, pos.y);
            }
        }
		
		string getType() {return "pixel";}

    protected:

        bool processOscMessage(const osc::ReceivedMessage& message,
                               const osc::MessageSource& source)
        {
            // call the base class
            if(DrawableObject::processOscMessage(message, source))
            {
                return true;
            }


            else if(message.path() == getOscRootAddress() + "/position")
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


            return false;
        }

        visual::Point pos;
};

#endif // PIXEL_H
