/*==============================================================================

	Scene.h

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
#ifndef SCENE_H
#define SCENE_H

#include "Common.h"

#include "objects/DrawableObject.h"

class Scene : public XmlObject, public OscObject
{
    public:

        Scene(string name, string parentOscAddress);
        virtual ~Scene();

        /// add an object
        void addObject(DrawableObject* object);

        /// remove an object
        void removeObject(DrawableObject* object);

        /// clears (deletes) all the objects in the list
        void clear();

		/// setup resources
        void setup();

        /// draw all the objects in the list
        void draw();

        /* ***** UTIL ***** */

        string getName() {return _name;}
        visual::Color& getBackground() {return _background;}
        int getFPS() {return _fps;}

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

    private:

        string _name;
        vector<DrawableObject*> _objectList;
        visual::Color _background;
        int _fps;
};

#endif // SCENE_H
