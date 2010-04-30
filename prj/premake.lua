--[[
	
	Dan Wilcox <danomatika@gmail.com>

--]]

project.name 		= "rc-visual"
project.bindir	 	= "../bin"
project.libdir 		= "../lib"

project.configs		= { "Debug", "Release" }

---------------------------------------------------------
--- build the externals
---------------------------------------------------------
package = newpackage()
package.name 		= "externals"
package.kind 		= "lib"
package.language 	= "c++"

package.postbuildcommands = {
	"cd ../externals/visualframework/prj && make"
}

---------------------------------------------------------
--- build rc-visual classes
---------------------------------------------------------
package = newpackage()
package.name 		= "visualClasses"
package.kind 		= "lib"
package.language 	= "c++"

package.files = { 
	matchfiles( "../src/classes/*.h", "../src/classes/*.cpp" )
}

package.includepaths = {
	"../src",
	"../src/classes",
    "/usr/include",
	"../externals",
	"../externals/visualframework/src",
	"../externals/visualframework/externals",
	"../externals/visualframework/externals/include"
}

package.libpaths = {
	"../lib",
	"../externals/lib",
	"../externals/visualframework/externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/visualClasses/Debug"
package.config["Release"].objdir = "../obj/visualClasses/Release"

package.config["Debug"].target   = "visualClassesD"
package.config["Release"].target = "visualClasses"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }


package.links = { "SDL", "SDL_gfx" }
package.config["Debug"].links = { "tinyxmlD", "oscpackD", "visualframeworkD" }
package.config["Release"].links = { "tinyxml", "oscpack", "visualframework" }

---------------------------------------------------------
--- build rc-visual-send
---------------------------------------------------------
package = newpackage()
package.name 		= "rc-visual-send"
package.kind 		= "exe"
package.language 	= "c++"

package.files = { 
    matchfiles( "../src/rc-visual-send/*.h", "../src/rc-visual-send/*.cpp" ),
}

package.includepaths = {
	"../src",
	"../src/classes",
    "/usr/include",
	"../externals/visualframework/src",
	"../externals/visualframework/externals",
	"../externals/visualframework/externals/include"
}

package.libpaths = {
	"../lib",
	"../externals/visualframework/lib",
	"../externals/visualframework/externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/rc-visual-send/Debug"
package.config["Release"].objdir = "../obj/rc-visual-send/Release"

package.config["Debug"].target   = "rc-visual-sendD"
package.config["Release"].target = "rc-visual-send"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }


package.links = { "SDL", "SDL_gfx" }
package.config["Debug"].links = { "visualframeworkD", "oscpackD", "visualClassesD" }
package.config["Release"].links = { "visualframework", "oscpack", "visualClasses" }

---------------------------------------------------------
--- build rc-visual-tests
---------------------------------------------------------
package = newpackage()
package.name 		= "rc-visual-tests"
package.kind 		= "exe"
package.language 	= "c++"

package.files = { 
    matchfiles( "../src/rc-visual-tests/*.h", "../src/rc-visual-tests/*.cpp" ),
}

package.includepaths = {
	"../src",
	"../src/classes",
    "/usr/include",
	"../externals/visualframework/src",
	"../externals/visualframework/externals",
	"../externals/visualframework/externals/include"
}

package.libpaths = {
	"../lib",
	"../externals/visualframework/lib",
	"../externals/visualframework/externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/rc-visual-tests/Debug"
package.config["Release"].objdir = "../obj/rc-visual-tests/Release"

package.config["Debug"].target   = "rc-visual-testsD"
package.config["Release"].target = "rc-visual-tests"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }


package.links = { "SDL", "SDL_gfx" }
package.config["Debug"].links = { "visualframeworkD", "oscpackD", "visualClassesD" }
package.config["Release"].links = { "visualframework", "oscpack", "visualClasses" }

---------------------------------------------------------
--- build rc-visual
---------------------------------------------------------
package = newpackage()
package.name 		= "rc-visual"
package.kind 		= "exe"
package.language 	= "c++"

package.files = { 
    matchfiles( "../src/rc-visual/*.h", "../src/rc-visual/*.cpp" ),
}

package.includepaths = {
	"../src",
	"../src/classes",
    "/usr/include",
	"../externals/visualframework/src",
	"../externals/visualframework/externals",
	"../externals/visualframework/externals/include",
	"/usr/include/glib-2.0",
	"/usr/lib/glib-2.0/include"
}

package.libpaths = {
	"../lib",
	"../externals/visualframework/lib",
	"../externals/visualframework/externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/rc-visual/Debug"
package.config["Release"].objdir = "../obj/rc-visual/Release"

package.config["Debug"].target   = "rc-visualD"
package.config["Release"].target = "rc-visual"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }


package.links = { "SDL", "SDL_gfx", "glib-2.0", "lo" }
package.config["Debug"].links = { "visualframeworkD", "visualClassesD", "tinyxmlD", "oscpackD" }
package.config["Release"].links = { "visualframework", "visualClassesD", "tinyxml", "oscpack" }

