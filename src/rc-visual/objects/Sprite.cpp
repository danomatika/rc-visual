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

SpriteFrame::SpriteFrame(DrawableObject *object): frameTime(100), o(object)
{
	// add variables to Xml
	o->addXmlAttribute("frametime", o->getType(), XML_TYPE_UINT, &frameTime);
	
	// detach unneeded variables from Xml
	o->removeXmlAttribute("name", o->getType());
}

SpriteFrame::~SpriteFrame()
{
	if(o) delete o;
}

Sprite::Sprite(string name, string parentOscAddress) :
	DrawableObject("sprite", name, parentOscAddress),
	pos(0, 0), width(0), height(0), bAnimate(true), bLoop(true), bPingPong(true),
	bDrawFromCenter(false), bDrawAllLayers(false),
	currentFrame(0), timestamp(0), bForward(true)
{
	// add variables to Xml
	addXmlAttribute("x", "position", XML_TYPE_FLOAT, &pos.x);
	addXmlAttribute("y", "position", XML_TYPE_FLOAT, &pos.y);
	addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
	addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
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

void Sprite::addFrame(SpriteFrame* frame)
{
	if(frame == NULL)
	{
		LOG_ERROR << "Sprite: Cannot add NULL frame" << endl;
		return;
	}

	addXmlObject(frame->getObject());
	frames.push_back(frame);
}

void Sprite::removeFrame(SpriteFrame* frame)
{
	if(frame == NULL)
	{
		LOG_ERROR << "Sprite: Cannot remove NULL frame" << endl;
		return;
	}

	vector<SpriteFrame*>::iterator iter;
	iter = find(frames.begin(), frames.end(), frame);
	if(iter != frames.end())
	{
		removeXmlObject((*iter)->getObject());
		delete (*iter);
		frames.erase(iter);
	}
}

void Sprite::clear()
{
	/// delete all frames
	for(unsigned int i = 0; i < frames.size(); ++i)
	{
		SpriteFrame* f = frames.at(i);
		delete f;
	}
	frames.clear();
}

void Sprite::nextFrame()
{
	if(frames.size() < 2)
		return;

	currentFrame++;

	if(currentFrame >= (int) frames.size())
	{
		if(bPingPong)
		{
			bForward = false;
			currentFrame = frames.size()-2;
		}
		else
		 currentFrame = 0;
	}
}

void Sprite::prevFrame()
{
	if(frames.size() < 2)
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
			currentFrame = frames.size()-1;
		}
	}
}

void Sprite::gotoFrame(unsigned int num)
{
	if(currentFrame >= (int) frames.size())
	{
		LOG_WARN << "Sprite: Cannot goto frame num " << num
				 << ", index out of range" << endl;
		return;
	}

	currentFrame = num;
}

void Sprite::gotoFrame(string name)
{
	for(unsigned int i = 0; i < frames.size(); ++i)
	{
		if(name == frames.at(i)->getName())
		{
			currentFrame = i;

			return;
		}
	}
}

void Sprite::setup()
{
	for(unsigned int i = 0; i < frames.size(); ++i)
	{
		frames[i]->setup();
		
		if(width != 0 && height != 0)
		{
			frames[i]->getObject()->setSize(width, height);
		}
	}
}

void Sprite::draw()
{
	if(frames.empty())
		return;

	// animate frames?
	if(bAnimate)
	{
		// go to next frame if time has elapsed
		if(visual::Graphics::getMillis() - timestamp > frames.at(currentFrame)->getFrameTime())
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
			for(unsigned int i = 0; i < frames.size(); ++i)
			{
				SpriteFrame* f = frames.at(i);
				f->draw(pos.x, pos.y);
			}
		}
		else if(currentFrame >= 0 && currentFrame < (int) frames.size())
		{
			SpriteFrame* f = frames.at(currentFrame);
			f->draw(pos.x, pos.y);
		}
	}
}

void Sprite::resizeIfNecessary()
{
	if(width != 0 && height != 0)
	{
		for(unsigned int i = 0; i < frames.size(); ++i)
		{
			SpriteFrame* f = frames.at(i);
			f->getObject()->setSize(width, height);
		}
	}
}

void Sprite::setDrawFromCenter(bool yesno)
{
	bDrawFromCenter = yesno;
	for(unsigned int i = 0; i < frames.size(); ++i)
	{
		SpriteFrame* f = frames.at(i);
		f->getObject()->setDrawFromCenter(bDrawFromCenter);
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
			name = Xml::getAttrString(child, "name", visual::Util::toString(frames.size()));
			LOG_DEBUG << "Sprite: Loading bitmap \"" << name << "\"" << std::endl;

			SpriteFrame* f = new SpriteFrame(new Bitmap(name, getOscRootAddress()));
			if(f->getObject()->loadXml(child))
			{
				addFrame(f);
			}
		}
		else if(child->ValueStr() == "image")
		{
			name = Xml::getAttrString(child, "name", visual::Util::toString(frames.size()));
			LOG_DEBUG << "Sprite: Loading image \"" << name << "\"" << std::endl;

			SpriteFrame* f = new SpriteFrame(new Image(name, getOscRootAddress()));
			if(f->getObject()->loadXml(child))
			{
				addFrame(f);
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

	else if(message.path() == getOscRootAddress() + "/frame")
	{
		unsigned int frame = 0;
		message.tryNumber(&frame, 0);
		gotoFrame(frame);
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
