/*==============================================================================

	DrawableObject.h

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
#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "../Common.h"

#include "../Config.h"

class DrawableObject : public XmlObject, public OscObject
{
    public:

        DrawableObject(string objectType, string objectName, string parentOscAddress) :
            XmlObject(objectType), OscObject(parentOscAddress+"/"+objectName),
			bVisible(true), name(objectName)
        {
            // attach variables to Xml
            addXmlAttribute("name", objectType, XML_TYPE_STRING, &name);
			
			addXmlAttribute("R", "color", XML_TYPE_BYTE, &color.R);
            addXmlAttribute("G", "color", XML_TYPE_BYTE, &color.G);
            addXmlAttribute("B", "color", XML_TYPE_BYTE, &color.B);
            addXmlAttribute("A", "color", XML_TYPE_BYTE, &color.A);

            addXmlAttribute("yesno", "visible", XML_TYPE_BOOL, &bVisible);
			
			LOG << "	OBJECT " << parentOscAddress+"/"+objectName << endl;
        }

		virtual void setup() {};
        virtual void draw() = 0;
		virtual void draw(int x, int y) {}
		
		virtual void setSize(unsigned int width, unsigned int height) {}
		virtual void setDrawFromCenter(bool yesno) {}

        string getName() {return name;}
		virtual string getType() = 0;

    protected:

        /// process one osc message, derived objects should call this
        /// using DrawableObject::processOscMessage() to handle the base variables
        virtual bool processOscMessage(const ReceivedMessage& message,
                            		   const MessageSource& source)
        {
            if(message.path() == getOscRootAddress() + "/color")
            {
                message.tryNumber((unsigned int*) &color.R, 0);
				message.tryNumber((unsigned int*) &color.G, 1);
				message.tryNumber((unsigned int*) &color.B, 2);
				message.tryNumber((unsigned int*) &color.A, 3);
                return true;
            }
            else if(message.path() == getOscRootAddress() + "/color/R")
            {
                message.tryNumber((unsigned int*) &color.R, 0);
                return true;
            }
            else if(message.path() == getOscRootAddress() + "/color/G")
            {
                message.tryNumber((unsigned int*) &color.G, 0);
                return true;
            }
            else if(message.path() == getOscRootAddress() + "/color/B")
            {
                message.tryNumber((unsigned int*) &color.B, 0);
                return true;
            }
            else if(message.path() == getOscRootAddress() + "/color/A")
            {
                message.tryNumber((unsigned int*) &color.A, 0);
                return true;
            }


            else if(message.path() == getOscRootAddress() + "/visible")
            {
				message.tryBool(&bVisible, 0);
                return true;
            }

            return false;
        }

        visual::Color color;
        bool bVisible;
        string name;
};

#endif // DRAWABLE_OBJECT_H
