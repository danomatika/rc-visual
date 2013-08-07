/*==============================================================================

	main.cpp

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

#include "Common.h"

#include "Config.h"
#include "App.h"

using namespace visual;

int main(int argc, char *argv[])
{
	#ifdef RESOURCE_DIR // defined in configure.ac
		Util::setDataPath(Util::makeAbsolutePath((string) RESOURCE_DIR));
	#else // for debugging without autotools
		Util::setDataPath(Util::makeAbsolutePath(Util::getDirPath(Util::getExecutablePath())+"/../../data"));
	#endif
	LOG << "Resource dir is " << Util::getDataPath() << endl;
    string iconPath = Util::toDataPath("icon.bmp");

	// create an App before parsing, so xml is loaded into SceneManager
	App application;

	// parse the commandline
    if(!Config::instance().parseCommandLine(argc, argv))
    	return EXIT_FAILURE;
	
    // initialize SDL context
    if(!Graphics::init(640, 480, 24, HARDWARE))
		return EXIT_FAILURE;

    // initialize app
    application.init();

    // set icon and open window
    Graphics::setWindowIcon(iconPath);
    if(!Graphics::createWindow(PACKAGE))
		return EXIT_FAILURE;

    // setup sdl resources
    application.setup();

    // main app loop
    application.mainLoop();

    // cleanup after exit from loop
    application.cleanup();

    return EXIT_SUCCESS;
}
