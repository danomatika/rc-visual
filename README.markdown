rc-visual
===================================

the robotcowboy visual engine

a simple, osc-controlled 2d graphics engine

Copyright (c) [Dan Wilcox](danomatika.com) 2007, 2010

DESCRIPTION
-----------

The rc-visual package contains the following parts:

1. rc-visual - osc-controlled, 2d engine
2. rc-visual-send - osc command tool

This group of tools allows any osc-capable program to control simple 2d visuals which are specified in xml scene descriptions. A notification tool can control a running graphics engine.

These tools are developed for the robotcowboy project, a wearable computer
music system using Pure Data in GNU/Linux. See http://robotcowboy.com

BUILD REQUIREMENTS
------------------

The following libraries are required:

* SDL
* SDL_gfx
* SDL_net
* SDL_ttf
* SDL_image
* liblo (lightweight osc)

On Max OS X, they can be installed using macports: http://macports.org

* install the macport binary and setup the macports environment
* goto the Terminal and install the libs:
<pre>
sudo port install libsdl libsdl_gfx libsdl_net libsdl_ttf libsdl_image liblo
</pre>

If using macports on Mac OS X, you need to set the macports include and lib dirs before running ./configure:
<pre>
export CPPFLAGS=-I/opt/local/include && export LDFLAGS=-L/opt/local/lib
</pre>

BUILD AND INSTALLATION
----------------------

As this is an GNU autotools project, simply run:

<pre>
./configure
make
sudo make install
</pre>

By default, the configure script installs to `/usr/local`.  To change this behavior, specify a new dir before building the project:

<pre>
./configure --prefix=/path/to/install/dir
</pre>

If using macports on Mac OS X, it is recommended to use the macports default prefix of `/opt/local`.

USAGE
-----

All applications have a full help usage printout, use -h or --help.

----

[1]:https://raw.github.com/danomatika/rc-visual/master/doc/rc-visual_screenshot.png

![image][1]

% rc-visual scene_file.xml

Starts rc-visual using the given xml scene description. The file sets connection information (if not using defaults) and lists visual scenes and scene elements. Look at the example.xml file install to the doc folder for details.

See the pd patches in the pd folder for info on how to communicate with rc-viusal.

Note: Values set on the commandline override those in the scene file.

----

% rc-visual-send

Used to control a running rc-visual. Can be used to signal scene changes, scene file loading, and send a quit command.

DEVELOPING
----------

A Premake4 script and IDE files can be found in the prj folder.  Premake4 can generate the IDE files from a given lua script.  Download Premake4 from http://industriousone.com/premake.

Make sure the externals are built by calling the prj/setupbuild script which runs configure and calls make in the externals dir.

You can enable a debug build using:
<pre>
./configure --enable-debug
</pre>

I develop using an IDE, then update the autotools files when the sources are finished.  I run make dist-check to make sure the distributable package can be built successfully.

FUTURE IDEAS/IMPROVEMENTS
-------------------------

* greater image support through libDevil?
* animation support (especially animated gifs)
* scene transitions, fades
* different render backends (OpenGL)
* lua scripting support (to create dynamic scenes)
* plugin architecture

