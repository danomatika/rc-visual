/*==============================================================================

	Sprite.h

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
#ifndef SPRITE_H
#define SPRITE_H

#include "Config.h"

#include "DrawableObject.h"
#include "Bitmap.h"
#include "Image.h"

// one frame in the sprite
struct SpriteFrame  {

	public:
	
		SpriteFrame(DrawableObject *object);
		~SpriteFrame();
	
		virtual void setup()			{o->setup();}
		virtual void draw(int x, int y)	{o->draw(x, y);}
		virtual string getName()		{return o->getName();}
		
		void resize(unsigned int width, unsigned int height);
	
		unsigned int getFrameTime()	{return frameTime;}
		
		DrawableObject* getObject()	{return o;}
	
	protected:
	
		unsigned int frameTime;
		DrawableObject *o;
};

//// base class for an object with frametime
//class SpriteObject {
//	
//	public:
//	
//		unsigned int getFrameTime()	{return frameTime;}
//	
//	protected:
//	
//		unsigned int frameTime;
//};
//
//// frame object types
//class SpriteBitmap : public SpriteObject, public Bitmap {
//	
//	public:
//	
//		SpriteBitmap(string name, string parentOscAddress);
//};
//class SpriteImage : public SpriteObject, public Image {
//	
//	public:
//	
//		SpriteImage(string name, string parentOscAddress);
//};

class Sprite : public DrawableObject
{
    public:

        Sprite(string name, string parentOscAddress);
        ~Sprite();

        void addFrame(SpriteFrame* frame);
        void removeFrame(SpriteFrame* frame);
        void clear();

        void nextFrame();
        void prevFrame();
        void gotoFrame(unsigned int num);
        void gotoFrame(string name);

		void setup();
        void draw();
		
		string getType() {return "sprite";}

        void setDrawFromCenter(bool yesno);
        void setDrawAllLayers(bool yesno) {bDrawAllLayers = yesno;}

    protected:

		void resizeIfNecessary();

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& message,
        					   const osc::MessageSource& source);

		struct SpriteObject
		{
			DrawableObject *object;		/// object to draw
			unsigned int frameTime;     /// how long to display in ms
		};
        std::vector<SpriteFrame*> frames;

        visual::Point pos;
		unsigned int width, height;
        bool bAnimate;
        bool bLoop;
        bool bPingPong;
        bool bDrawFromCenter;
        bool bDrawAllLayers;

        int currentFrame;
        unsigned int timestamp;
        bool bForward;  /// advance frames?
};

#endif // SPRITE_H
