--[[ A solution contains projects, and defines the available configurations

http://industriousone.com/premake/user-guide

example: http://opende.svn.sourceforge.net/viewvc/opende/trunk/build/premake4.lua?revision=1708&view=markup

http://bitbucket.org/anders/lightweight/src/tip/premake4.lua

]]
solution "rc-visual"
	configurations { "Debug", "Release" }
	objdir "../obj"

-- rc-visual executable
project "rc-visual"
	kind "ConsoleApp"
	language "C++"
	targetdir "../src/rc-visual"
	files { "../src/rc-visual/**.h", "../src/rc-visual/**.cpp" }
	
	includedirs { "../src",
				  "../externals/",
				  "../externals/visualframework" }
	libdirs { "../externals/visualframework",
			  "../externals/xmlframework",
      		  "../externals/oscframework" }
	links { "oscframework", "xmlframework", "visualframework",
		    "SDL_net", "SDL_ttf", "SDL_image" }

	configuration "linux"
		buildoptions { "`pkg-config --cflags sdl`",
					   "`pkg-config --cflags SDL_gfx`",
					   "`pkg-config --cflags liblo`",
					   "`pkg-config --cflags SDL_image`" }
		linkoptions { "`pkg-config --libs sdl`",
					  "`pkg-config --libs SDL_gfx`",
					  "`pkg-config --libs liblo`",
					  "`pkg-config --libs SDL_image`" }

	configuration 'macosx'
		-- MacPorts
		includedirs { "/opt/local/include"}
		libdirs { "/opt/local/lib" }
		links { "lo", "pthread", "SDLmain", "SDL", "SDL_gfx" }
		linkoptions { "-Wl,-framework,Cocoa", "-Wl,-framework,OpenGL",
					  "-Wl,-framework,ApplicationServices",
					  "-Wl,-framework,Carbon", "-Wl,-framework,AudioToolbox",
					  "-Wl,-framework,AudioUnit", "-Wl,-framework,IOKit" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }

-- rc-visual-send executable
project "rc-visual-send"
	kind "ConsoleApp"
	language "C++"
	targetdir "../src/rc-visual-send"
	files { "../src/rc-visual-send/**.h", "../src/rc-visual-send/**.cpp" }
	
	includedirs { "../src",
				  "../externals/" }
	libdirs { "../externals/oscframework" }
	links { "oscframework" }

	configuration "linux"
		buildoptions { "`pkg-config --cflags liblo`" }
		linkoptions { "`pkg-config --libs liblo`" }

	configuration 'macosx'
		-- MacPorts
		includedirs { "/opt/local/include"}
		libdirs { "/opt/local/lib" }
		links { "lo", "pthread", "SDLmain", "SDL", "SDL_gfx" }
		linkoptions { "-Wl,-framework,Cocoa", "-Wl,-framework,OpenGL",
					  "-Wl,-framework,ApplicationServices",
					  "-Wl,-framework,Carbon", "-Wl,-framework,AudioToolbox",
					  "-Wl,-framework,AudioUnit", "-Wl,-framework,IOKit" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
		
		
