/*==============================================================================

	Sprite.cpp

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
#include "Sprite.h"

SpriteBitmap::SpriteBitmap(string name, string parentOscAddress) :
	Bitmap(name, parentOscAddress), frameTime(0)
{
	// add variables to Xml
	addXmlAttribute("frametime", "bitmap", XML_TYPE_UINT, &frameTime);
	
	// detach unneeded variables from Xml
	removeXmlAttribute("name", "bitmap");
}

Sprite::Sprite(string name, string parentOscAddress) :
	DrawableObject("sprite", name, parentOscAddress),
    pos(0, 0), bAnimate(true), bLoop(true), bPingPong(true),
    bDrawFromCenter(false), bDrawAllLayers(false),
    currentFrame(0), timestamp(0), bForward(true)
{
    // add variables to Xml
    addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
    addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
    addXmlAttribute("animate", "animation", XML_TYPE_BOOL, &bAnimate);
    addXmlAttribute("loop", "animation", XML_TYPE_BOOL, &bLoop);
    addXmlAttribute("pingpong", "animation", XML_TYPE_BOOL, &bPingPong);
    addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);
    addXmlAttribute("yesno", "overlay", XML_TYPE_BOOL, &bDrawAllLayers);

    // detach unneeded variables from Xml
	removeXmlElement("color");

    timestamp = visual::Graphics::getMillis();
}

Sprite::~Sprite()
{
    clear();
}

void Sprite::addBitmap(SpriteBitmap* bitmap)
{
    if(bitmap == NULL)
    {
        LOG_ERROR << "Sprite: Cannot add NULL bitmap" << endl;
        return;
    }

    addXmlObject(bitmap);

    bitmapList.push_back(bitmap);
}

void Sprite::removeBitmap(SpriteBitmap* bitmap)
{
    if(bitmap == NULL)
    {
        LOG_ERROR << "Sprite: Cannot remove NULL bitmap" << endl;
        return;
    }

    vector<SpriteBitmap*>::iterator iter;
    iter = find(bitmapList.begin(), bitmapList.end(), bitmap);
    if(iter != bitmapList.end())
    {
        removeXmlObject((*iter));
        bitmapList.erase(iter);
    }
}

void Sprite::clear()
{
    /// delete all the bitmaps
    for(unsigned int i = 0; i < bitmapList.size(); ++i)
    {
        SpriteBitmap* b = bitmapList.at(i);
        delete b;
    }
    bitmapList.clear();
}

void Sprite::nextFrame()
{
    if(bitmapList.size() < 2)
        return;

    currentFrame++;

    if(currentFrame >= (int) bitmapList.size())
    {
        if(bPingPong)
        {
            bForward = false;
            currentFrame = bitmapList.size()-2;
        }
        else
         currentFrame = 0;
    }
}

void Sprite::prevFrame()
{
    if(bitmapList.size() < 2)
        return;

    currentFrame--;

    if(currentFrame < 0)
    {
        if(bPingPong)
        {
            bForward = true;
            currentFrame = 1;
        }
        else
        {
            currentFrame = bitmapList.size()-1;
        }
    }
}

void Sprite::gotoFrame(unsigned int num)
{
    if(currentFrame >= (int) bitmapList.size())
    {
        LOG_WARN << "Sprite: Cannot goto frame num " << num
                 << ", index out of range" << endl;
        return;
    }

    currentFrame = num;
}

void Sprite::gotoFrame(string name)
{
    for(unsigned int i = 0; i < bitmapList.size(); ++i)
    {
        if(name == bitmapList.at(i)->getName())
        {
            currentFrame = i;

            return;
        }
    }
}

void Sprite::draw()
{
    if(bitmapList.empty())
        return;

    // animate frames?
    if(bAnimate)
    {
        // go to next frame if time has elapsed
        if(visual::Graphics::getMillis() - timestamp > bitmapList.at(currentFrame)->getFrameTime())
        {
            if(bForward)
                nextFrame();
            else
                prevFrame();
            timestamp = visual::Graphics::getMillis();
        }
    }

    // draw frame(s)?
    if(bVisible)
    {
        if(bDrawAllLayers)
        {
            for(unsigned int i = 0; i < bitmapList.size(); ++i)
            {
                SpriteBitmap* b = bitmapList.at(i);
                b->draw(pos.x, pos.y);
            }
        }
        else if(currentFrame >= 0 && currentFrame < (int) bitmapList.size())
        {
            SpriteBitmap* b = bitmapList.at(currentFrame);
            b->draw(pos.x, pos.y);
        }
    }
}

void Sprite::setDrawFromCenter(bool yesno)
{
	bDrawFromCenter = yesno;
    for(unsigned int i = 0; i < bitmapList.size(); ++i)
    {
        SpriteBitmap* b = bitmapList.at(i);
        b->setDrawFromCenter(bDrawFromCenter);
    }
}

bool Sprite::readXml(TiXmlElement* e)
{
    string name;

    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "bitmap")
        {
			name = Xml::getAttrString(child, "name", visual::Util::toString(bitmapList.size()));
			LOG_DEBUG << "Sprite: Loading bitmap \"" << name << "\"" << std::endl;

			SpriteBitmap* b = new SpriteBitmap(name, getOscRootAddress());
			if(b->loadXml(child))
			{
				addBitmap(b);
			}
        }

        child = child->NextSiblingElement();
    }

    // init all loaded bitmaps draw settings
    setDrawFromCenter(bDrawFromCenter);

    return true;
}

bool Sprite::processOscMessage(const osc::ReceivedMessage& message,
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


    else if(message.path() == getOscRootAddress() + "/center")
    {
		bool b = bDrawFromCenter;
		if(message.tryBool(&b, 0))
		{
			setDrawFromCenter(b);
        }
		return true;
    }


    else if(message.path() == getOscRootAddress() + "/animate")
    {
		message.tryBool(&bAnimate, 0);
        return true;
    }
    
    else if(message.path() == getOscRootAddress() + "/overlay")
    {
		message.tryBool(&bDrawFromCenter, 0);
        return true;
    }


    return false;
}
