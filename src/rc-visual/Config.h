/*==============================================================================

	Config.h

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
#ifndef CONFIG_H
#define CONFIG_H

#include "Common.h"

/**
    \class  Config
    \brief  global, per-application instance state variable container class

    implemented as a singleton class following:
    http://en.wikipedia.org/wiki/Singleton_pattern

    no initialization is needed, just use equt::Config::instance() to access
    member functions, data
**/
class Config : public xml::XmlObject
{
    public:

		/**
            \brief singleton data access
            \return a reference to itself

            creates a new object on the first call
        **/
        static Config& instance();
        
        /// load resources
        void setup();
        
        /// print current variables to LOG
        void print();
        
        /* ***** VARIABLES ***** */
        
        unsigned int listeningPort;		///< the listening port
        string listeningAddress;		///< base listening address
        
        string sendingIp;				///< ip to send to
        unsigned int sendingPort;		///< port to send to
        
        //string baseAddress;			///< base osc sending address
        string notificationAddress;		///< base osc sending address for notifications
        string deviceAddress;			///< base osc sending addess for devices
        
        string fontFilename;			///< font filename

		/* **** OBJECTS ***** */
        
        /// get a reference to the OscSender and OscReceiver
        inline osc::OscSender& getOscSender() 		{return _oscSender;}
        inline osc::OscReceiver& getOscReceiver() 	{return _oscReceiver;}
        
        /// get the global font
        inline visual::Font& getFont() {return _font;}
        
        /**
        	\brief	parse the commandline options
        */
        bool parseCommandLine(int argc, char **argv);

    private:

        OscSender 	_oscSender;       	///< global osc sender
        OscReceiver _oscReceiver;		///< global osc receiver
        
        visual::Font _font;			///< global font
        
        // hide all the constructors, copy functions here
        Config();                       // cannot create
        virtual ~Config() {}           	// cannot destroy
        void operator =(Config& from) {}// not copyable
};

#endif // CONFIG_H
