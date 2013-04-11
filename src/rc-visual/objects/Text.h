/*==============================================================================

	Text.h

	rc-visual: a simple, osc-controlled 2d graphics engine
  
	Copyright (C) 2007, 2010, 2011  Dan Wilcox <danomatika@gmail.com>

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
#ifndef TEXT_H
#define TEXT_H

#include "Config.h"

#include "DrawableObject.h"

class Text : public DrawableObject
{
    public:

        Text(string name, string parentOscAddress) :
			DrawableObject("text", name, parentOscAddress), pos(0, 0), bDrawFromCenter(0)
        {
            // add variables to Xml
            addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
            addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
            addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);
        }

        void draw()
        {
            if(bVisible && !text.empty())
            {
                visual::Graphics::stroke(color);
                    
                if(bDrawFromCenter)
				{
					int w = text.size() * CONFIG_FONT_SIZE;
					Config::instance().getFont().draw(pos.x-w/2, pos.y, text);
				}
                else
				{
                    Config::instance().getFont().draw(pos.x, pos.y, text);
				}
            }
        }

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


            else if(message.path() == getOscRootAddress() + "/string" &&
            		message.types() == "s")
            {
                text = message.asString(0);
                return true;
            }
            
            else if(message.path() == getOscRootAddress() + "/center")
            {
				message.tryBool(&bDrawFromCenter, 0);
                return true;
            }


            return false;
        }

		bool readXml(TiXmlElement* e)
		{
			TiXmlElement* child = Xml::getElement(e, "string");
			if(child != NULL)
			{    
				text = Xml::getText(child);
				return true;
			}
			else {
				LOG_WARN << "Text " << name << ": string element empty" << endl;
			}
			return false;
		}
		
		bool writeXml(TiXmlElement* e)
		{
			TiXmlElement* child = Xml::obtainElement(e, "string");
			Xml::setText(child, text);
			return true;
		}

        visual::Point pos;
        string text;
        bool bDrawFromCenter;       /// draw from the center using pos
};

#endif // RECT_H
