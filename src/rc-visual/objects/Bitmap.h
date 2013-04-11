/*==============================================================================

	Bitmap.h

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
#ifndef BITMAP_H
#define BITMAP_H

#include "Config.h"

#include "DrawableObject.h"

class Bitmap : public DrawableObject
{
    public:

        Bitmap(string name, string parentOscAddress);

        void draw();
        void draw(int x, int y);

        void setBitmap(vector<bool> bitmap) {this->bitmap = bitmap;}

        void setDrawFromCenter(bool yesno) {bDrawFromCenter = yesno;}

    protected:
    
    	// compute the pixel size based on the width/height and size of bitmap
    	void computePixelSize();

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);
        bool writeXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& message,
        					   const osc::MessageSource& source);

        vector<bool> bitmap;   /// actual bitmap
		unsigned int bitmapWidth, bitmapHeight;	/// dimen of the bitmap

        visual::Point pos;			/// screen position
        unsigned int width, height; /// screen height
        unsigned int pixelWidth, pixelHeight; /// dimen of one pixel in the bitmap
        bool bFilled;
        bool bDrawFromCenter;       /// draw from the center using pos?
};

#endif // BITMAP_H
