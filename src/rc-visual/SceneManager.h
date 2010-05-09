/*==============================================================================

	SceneManager.h

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
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Common.h"

#include "Config.h"
#include "Scene.h"

class App;

class SceneManager : public XmlObject, public OscObject
{
    public:

        SceneManager(App& app);
        virtual ~SceneManager();

        /// add an object
        void addObject(Scene* object);

        /// remove an object
        void removeObject(Scene* object);

        /// clears (deletes) all the objects in the list
        void clear(bool keepCurScene=false);

		/// loads graphics resources
		void setup();

		// scene transport
        void nextScene();
        void prevScene();
        void gotoScene(unsigned int num);
        void gotoScene(string name);

        /// draw all the objects in the list
        void draw();
        
        /// show the scene name when changing?
        void showSceneName(bool yesno) {_bShowSceneName = yesno;}
		void toggleSceneName() {_bShowSceneName = !_bShowSceneName;}
        
        /// reload the scene file
        void reload();

    protected:

		/// set the background and fps from a scene
        void setupScene(Scene* s);

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& message,
                               const osc::MessageSource& source);

    private:

		App& _app;

        int _currentScene;
        vector<Scene*> _objectList;
        
        bool _bShowSceneName;
        visual::Timer _sceneNameTimer;
        visual::Font _sceneNameFont;
};

#endif // SCENE_MANAGER_H
