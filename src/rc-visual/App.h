/*==============================================================================

	App.h

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
#ifndef APP_H
#define APP_H

#include "Common.h"

#include "Config.h"
#include "SceneManager.h"

class App : public visual::Application, public OscObject
{
    public:

        App();

        bool init();

        void setup();

        void update();

        void draw();

        void cleanup();

        void keyPressed(SDLKey key, SDLMod mod);
        
        inline void stop() {bRunning = false;}
		
		SceneManager& getSceneManager() {return sceneManager;}
        
    protected:

		/// received osc message callback
        bool processOscMessage(const osc::ReceivedMessage& message,
                               const osc::MessageSource& source);
                                  
        /// signal callback
		static void signalExit(int signal);

    private:

        bool bRunning;  //< running or paused?

        Config& config;	//< config reference
		bool bSceneFileIsConfigFile; //< was the current scene file loaded with the config?
									 //< this will change to false once a scene is loaded separately
        OscReceiver& receiver;
        OscSender& sender;
        
        SceneManager sceneManager;

        unsigned int reloadTimestamp;
		unsigned int saveTimestamp;
};

#endif // APP_H
