rc-visual
===================================

the robotcowboy visual engine

a simple Open Sound Control 2d graphics engine

Copyright (c) [Dan Wilcox](danomatika.com) 2007 - 2013

DESCRIPTION
-----------

The rc-visual package contains the following parts:

1. rc-visual - OSC-controlled 2d engine
2. rc-visual-send - OSC notification command tool

This group of tools allows any OSC-capable program to control simple 2d visuals which are specified in xml scene descriptions. A notification tool can control a running graphics engine.

These tools are developed for the robotcowboy project, a wearable computer
music system using Pure Data in GNU/Linux. See http://robotcowboy.com

QUICK START
-----------

Here's a quick start to build and install for Ubuntu/Debian on the command line:
<pre>
sudo apt-get install libsdl-dev libsdl-gfx1.2-dev libsdl-net1.2-dev libsdl-ttf2.0-dev libsdl-image1.2-dev liblo-dev
git clone git://github.com/danomatika/rc-visual.git
cd rc-visual
./configure
make
sudo make install
</pre>

If everything finished successfully, you're good to go. 

BUILD REQUIREMENTS
------------------

The following libraries are required:

* SDL
* SDL_gfx
* SDL_net
* SDL_ttf
* SDL_image
* liblo (lightweight osc)

### Linux

Install the required development versions of the libraries using your distro's package manager.

For Debian/Ubuntu, you can use use `apt-get` on the command line:
<pre>
sudo apt-get libsdl-dev libsdl-gfx1.2-dev libsdl-net1.2-dev libsdl-ttf2.0-dev libsdl-image1.2-dev liblo-dev
</pre>

### Mac OS

On Max OS X, they can be installed easily using [Macports](http://macports.org) or [Homebrew](http://mxcl.github.com/homebrew/)

#### Macports

* install the Macports binary and setup the Macports environment
* goto the Terminal and install the libs:
<pre>
sudo port install libsdl libsdl_gfx libsdl_net libsdl_ttf libsdl_image liblo
</pre>

If you use the default Macports install location of `/opt/local`, you will need to set the Macports include and lib dirs before running ./configure:
<pre>
export CPPFLAGS=-I/opt/local/include && export LDFLAGS=-L/opt/local/lib
</pre>

#### Homebrew

* install the Homebrew environment
* go to the Terminal and install the libs:
<pre>
brew install sdl sdl_gfx sdl_net sdl_ttf sdl_image liblo
</pre>

### Windows

Windows support should work, but hasn't been tested. I'd recommend installing binary versions of the required libraries and building rc-visual in MiniGW/Cygwin.

BUILD AND INSTALLATION
----------------------

As this is an GNU autotools project, simply run on the command line:

<pre>
./configure
make
sudo make install
</pre>

This readme, example config files, and resources are also installed to your doc dir, something like `$(prefix)/share/doc/rc-visual`.

By default, the configure script installs to `/usr/local`. To change this behavior, specify a new dir before building the project:

<pre>
./configure --prefix=/path/to/install/dir
</pre>

If using Macports on Mac OS X, it is recommended to use the Macports default prefix of `/opt/local`.

USAGE
-----

All applications have a full help usage printout, use -h or --help.

----
### rc-visual

[1]:https://raw.github.com/danomatika/rc-visual/master/doc/rc-visual_screenshot.png

![image][1]

    % rc-visual scene_file.xml

Starts rc-visual using the given xml scene description. The file sets connection information (if not using defaults) and lists visual scenes and scene elements. Look at the `example.xml` file installed to the doc folder or in the `data` folder  of the source distribution for details.

See the pd patches in the pd folder for info on how to communicate with rc-visual.

Note: Values set on the command line override those in the scene file.

#### Options

You can also specify values on the command line which override values in the config file:
<pre>
  -i, --ip                     IP address to send to; default is '127.0.0.1'
  -p, --port                   Port to send to; default is '8880'
  --listening_port             Listening port; default is '7770'
  --connectionId               Connection id for notifications; default is '0'
</pre>

#### Event Streaming

rc-visual streams keyboard event information in the following OSC address format:

<pre>
/rc-visual/devices/keyboard KEY
</pre>

* _KEY_ is the current key pressed value

#### Notifications 
rc-unitd also sends status notification messages:<pre>/rc-visual/notifications/connect ID/rc-unitd/notifications/disconnect ID
</pre>

* _ID_ is the connectionID specified in the config file or as a the command line option (0 by default)

----
### rc-visual-send

    % rc-visual-send

Used to control a running rc-visual. Can be used to signal scene changes, scene file loading, and send a quit command.

Load a config file (clears current):
<pre>
% rd-visual-send file some_file.xml
</pre>

Reload the current file (for live changes):
<pre>
% rc-visual-send reload
</pre>

Go to next scene:
<pre>
% rc-visual-send scene next
</pre>

Go to previous scene:
<pre>
% rc-visual-send scene prev
</pre>

Go to scene by number:
<pre>
% rc-visual-send scene 1
</pre>

Go to scene by name:
<pre>
% rc-visual-send scene scene1
</pre>

Tell rd-visual to shutdown:
<pre>
% rc-visual-send quit
</pre>

#### Options

rc-visual-send has ip and port setting options similar to rc-visual:
<pre>
  -i, --ip               IP address to send to; default is '127.0.0.1'
  -p, --port             Port to send to; default is '7770'
  -q, --quiet            Don't print a summary
</pre>

Example, tell rc-visual running on machine at 10.0.0.100 using port 10100 to shutdown:
<pre>
% rc-visual-send -i 10.0.0.100 -p 10100 quit
</pre>

----
### Console Error

As rc-visual uses SDL, it will not work over a SSH connection and you'll get the following error:
<pre>
Error: Graphics: Unable to open a console terminal
</pre>

Run it from a real terminal on the machine.

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
* animated gif support
* scene transitions, fades
* different render backends (OpenGL)
* lua scripting support (to create dynamic scenes)
* plugin architecture

