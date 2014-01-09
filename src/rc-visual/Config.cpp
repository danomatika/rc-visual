/*==============================================================================

	Config.cpp

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
#include "Config.h"

#include "App.h"
#include <tclap/tclap.h>

#if defined( __WIN32__ ) || defined( _WIN32 )
	#include <windows.h>
#endif

Config& Config::instance()
{
	static Config * pointerToTheSingletonInstance = new Config;
	return *pointerToTheSingletonInstance;
}

bool Config::parseCommandLine(int argc, char **argv)
{
	try
	{
		// the commandline parser
		TCLAP::CommandLine cmd("a simple 2d rendering engine", VERSION);
		
		stringstream itoa;
		itoa << sendingPort;
		
		// options to parse
		// short id, long id, description, required?, default value, short usage type description
		TCLAP::ValueArg<string> ipOpt("i", "ip", (string) "IP address to send to; default is '"+sendingIp+"'", false, sendingIp, "string");
		TCLAP::ValueArg<int> portOpt("p","port", (string) "Port to send to; default is '"+itoa.str()+"'", false, sendingPort, "int");
	 
		itoa.str("");
		itoa << listeningPort;
		TCLAP::ValueArg<int> inputPortOpt("", "listeningPort", "Listening port; default is '"+itoa.str()+"'", false, listeningPort, "int");
		
		itoa.str("");
		itoa << connectionId;
		TCLAP::ValueArg<int> connectionIdOpt("", "connectionId", "Connection id for notifications; default is '"+itoa.str()+"'", false, connectionId, "int");
		
		// commands to parse
		// name, description, required?, default value, short usage type description
		TCLAP::UnlabeledValueArg<string> fileCmd("xml", "visual xml file to load", false, "", "file");

		// add args to parser (in reverse order)
		cmd.add(connectionIdOpt);
		cmd.add(inputPortOpt);
		cmd.add(portOpt);
		cmd.add(ipOpt);
		
		// add commands
		cmd.add(fileCmd);
		
		// parse the commandline
		cmd.parse(argc, argv);

		// load the config file (if one exists)
		if(fileCmd.getValue() != "")
		{
			string filePath = visual::Util::makeAbsolutePath(fileCmd.getValue());
			LOG << "Config: loading \"" << filePath << "\"" << endl;
			
			App *app = (App*) _app;
			if(app->getSceneManager().loadXmlFile(filePath))
			{
				// set data path to config file folder
				visual::Util::setDataPath(visual::Util::getDirPath(filePath));
		
				closeXmlFile();
			}
		}
		
		// set the variables, may override xml settings
		if(ipOpt.isSet())			sendingIp = ipOpt.getValue();
		if(portOpt.isSet())			sendingPort = portOpt.getValue();
		if(inputPortOpt.isSet())	listeningPort = inputPortOpt.getValue();
		if(connectionIdOpt.isSet())	connectionId = connectionIdOpt.getValue();
	}
	catch(TCLAP::ArgException &e)  // catch any exceptions
	{
		LOG_ERROR << "CommandLine: " << e.error() << " for arg " << e.argId() << endl;
		return false;
	}

	return true;
}

void Config::setup()
{
	_font.load(fontFilename, CONFIG_FONT_SIZE);
}

void Config::print()
{        
	LOG << "listening port:	" << listeningPort << endl
		<< "listening address: " << baseAddress << endl
		<< "sending ip: " << sendingIp << endl
		<< "sending port: " << sendingPort << endl
		<< "sending address for notifications: " << notificationAddress << endl
		<< "sending address for devices:       " << deviceAddress << endl
		<< "connection id for notifications: " << connectionId << endl;
}

/* ***** PRIVATE ***** */

Config::Config() :
	XmlObject(""),
	listeningPort(9990),
	sendingIp("127.0.0.1"), sendingPort(8880),
	baseAddress((string) "/"+PACKAGE),
	notificationAddress(baseAddress+"/notifications"),
	deviceAddress(baseAddress+"/devices"),
	connectionId(0),
	fontFilename(visual::Util::toDataPath("ATARCC__.TTF"))
{
	// attach config values to xml attributes
	addXmlAttribute("port", "listening", XML_TYPE_UINT, &listeningPort);
	
	addXmlAttribute("ip", "sending", XML_TYPE_STRING, &sendingIp);
	addXmlAttribute("port", "sending", XML_TYPE_UINT, &sendingPort);
	
	addXmlAttribute("notificationAddress", "osc", XML_TYPE_STRING, &notificationAddress);
	addXmlAttribute("deviceAddress", "osc", XML_TYPE_STRING, &deviceAddress);
	addXmlAttribute("connectionId", "osc", XML_TYPE_UINT, &connectionId);
}
