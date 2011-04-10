/*==============================================================================

	App.cpp

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
#include "App.h"

#include <sstream>

using namespace visual;

App* appPtr;

App::App() : OscObject(""), bRunning(true),
	config(Config::instance()),
    receiver(Config::instance().getOscReceiver()),
    sender(Config::instance().getOscSender()),
    sceneManager(*this),
    reloadTimestamp(0)
{
	appPtr = this;

    // set osc addresses
    setOscRootAddress(Config::instance().baseAddress);
    receiver.setOscRootAddress(Config::instance().baseAddress);
	
	LOG << "SCENE MANAGER " << sceneManager.getOscRootAddress() << endl;

	// add osc objects
    receiver.addOscObject(this);
    receiver.addOscObject(&sceneManager);
    
    // add xml objects
    config.addXmlObject(&sceneManager);
    
    reloadTimestamp = Graphics::getMillis();
}

App::~App()
{}

bool App::init()
{
	// don't show the cursor if not debugging
    Graphics::showMouseCursor(bDebug);

    // setup the osc receiver
    receiver.setup(9990);
    receiver.start();
    
    // setup the osc sender
    sender.setup(config.sendingIp, config.sendingPort);

    // set the xml filename (for reloading)
    if(config.getXmlFilename() != "")
    {
		sceneManager.setXmlFilename(config.getXmlFilename());
    }

    return true;
}

void App::setup()
{
	config.print();
	config.setup();
    
    // start out at 25 fps
    setFrameRate(25);
    
    // set signal handling
    signal(SIGTERM, signalExit);    // terminate
    signal(SIGQUIT, signalExit);    // quit
    signal(SIGINT,  signalExit);	// interrupt
	
    // try to load first scene
    sceneManager.setup();
}

void App::update()
{}

void App::draw()
{
	if(bRunning)
    {
        sceneManager.draw();
    }
    
    if(bDebug)
    {
    	stringstream stream;
        stream << getFrameRate();
        Graphics::stroke(0xFFFFFF);
    	config.getFont().draw(0, 0, stream.str());
    }
}

void App::cleanup()
{
    receiver.stop();
}

void App::keyPressed(SDLKey key, SDLMod mod)
{            
    switch(key)
    {
    	case SDLK_LEFT:
            sceneManager.prevScene();
            return;

        case SDLK_RIGHT:
            sceneManager.nextScene();
            return;
            
        case 'p':
        	if(mod & KMOD_SHIFT)
            {
                bRunning = !bRunning;
                receiver.ignoreMessages(!bRunning);
                LOG_DEBUG << "Running: " << bDebug << endl;
                return;
            }
            break;

        case 'd':
        	if(mod & KMOD_SHIFT)
            {
            	toggleDebug();
                Graphics::showMouseCursor(bDebug);
            	LOG_DEBUG << "Debug: " << bDebug << endl;
                return;
            }
            break;

        case 'r':
        	if(mod & KMOD_SHIFT)
            {
                if(Graphics::getMillis() - reloadTimestamp > 5000)
                {
                    LOG << "Reloading xml file" << endl;
                    sceneManager.reload();
                    return;
                }
            }
            break;

        default:
            break;
    }
    
    // forward key events
    sender << BeginMessage(config.deviceAddress + "/keyboard")
           << (unsigned char) key << EndMessage();
    sender.send();
}

/* ***** PROTECTED ***** */

bool App::processOscMessage(const osc::ReceivedMessage& message,
								  const osc::MessageSource& source)
{
	LOG_DEBUG << "Received " << message.path() << " " << message.types() << std::endl;
    
    if(message.path() == getOscRootAddress() + "/scene")
    {
        if(message.types() == "s")
        {
            string scene = message.asString(0);
            sceneManager.gotoScene(scene);
            return true;
        }
        else if(message.types() == "i")
        {
            int index = message.asInt32(0);
            sceneManager.gotoScene(index);
            return true;
        }
    }
    
    else if(message.path() == getOscRootAddress() + "/scene/prev")
    {
    	sceneManager.prevScene();
    	return true;
    }
    
    else if(message.path() == getOscRootAddress() + "/scene/next")
    {
    	sceneManager.nextScene();
    	return true;
    }

	else if(message.path() == getOscRootAddress() + "/file" && message.types() == "s")
    {
        sceneManager.loadXmlFile(message.asString(0));
        return true;
    }
    
    else if(message.path() == getOscRootAddress() + "/reload")
    {
        sceneManager.reload();
        return true;
    }
    
    else if(message.path() == getOscRootAddress() + "/framerate" && message.types() == "f")
    {
        setFrameRate(message.asFloat(0));
        return true;
    }

    else if(message.path() == getOscRootAddress() + "/quit")
    {
        exitMainLoop();
        return true;
    }

    return false;
}

void App::signalExit(int signal)
{
	appPtr->exitMainLoop();
    LOG << endl << "    " << PACKAGE << ": Signal caught.  Exiting ..." << endl;
}
