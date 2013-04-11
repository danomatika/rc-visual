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

/// a bitmap with frametime
class SpriteBitmap : public Bitmap
{
	public:
		SpriteBitmap(string name, string parentOscAddress);
	
		unsigned int getFrameTime() {return frameTime;}
	
	protected:
	
		unsigned int frameTime;     /// how long to display in ms
};

class Sprite : public DrawableObject
{
    public:

        Sprite(string name, string parentOscAddress);
        ~Sprite();

        void addBitmap(SpriteBitmap* bitmap);
        void removeBitmap(SpriteBitmap* bitmap);
        void clear();

        void nextFrame();
        void prevFrame();
        void gotoFrame(unsigned int num);
        void gotoFrame(string name);

        void draw();

        void setDrawFromCenter(bool yesno);
        void setDrawAllLayers(bool yesno) {bDrawAllLayers = yesno;}

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& message,
        					   const osc::MessageSource& source);

        std::vector<SpriteBitmap*> bitmapList;

        visual::Point pos;
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
