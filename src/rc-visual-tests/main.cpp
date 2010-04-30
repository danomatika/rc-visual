/*  main.cpp

    rc-visual-send

  Copyright (C) 2008 Dan Wilcox

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

*/
#include <iostream>
#include <unistd.h>
#include <sstream>

#include <visualframework.h>
#include <tclap/Tclap.h>

using namespace std;

int main(int argc, char *argv[])
{
    // the commandline parser
    TCLAP::CommandLine cmd("send control OSC messages to rc-visual", ' ', "0.1");

    // variables to parse
    TCLAP::ValueArg<string> ipAddrArg("i","ip","Ip address to send to", false, "127.0.0.1", "string");
    TCLAP::ValueArg<int> portArg("p","port","Port to send to", false, 9990, "int");
    TCLAP::UnlabeledMultiArg<string> commandArgs("", "",  false, "");

    visual::OscSender sender;

    vector<string> commands;    // list of extra commandline args

	try
	{
        // add args to parser
        cmd.add(ipAddrArg);
        cmd.add(portArg);
        cmd.add(commandArgs);

        // parse the commandline
        cmd.parse(argc, argv);

        // setup the osc sender
        sender.setup(ipAddrArg.getValue(), portArg.getValue());
        cout << "ip: " << ipAddrArg.getValue() << " port: " << portArg.getValue() << endl;

        // get all extra commandline args as a vector
        commands = commandArgs.getValue();
	}
	catch(TCLAP::ArgException &e)  // catch any exceptions
	{
	    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
    }

    // do nothing if there are no commands
    if(commands.empty())
    {
        cout << "No message sent" << endl;
        return EXIT_FAILURE;
    }

    string message, feedback;
    message = commands.front();
    commands.erase(commands.begin());   // pop off front arg

    // parse the leftover commandline args
    if(message == "file")
    {
        if(commands.empty())
        {
            cout << "error: missing file name for file command" << endl;
            return EXIT_FAILURE;
        }

        string filename;
        filename = commands.front();
        commands.erase(commands.begin());

        if(filename != "")
        {
            sender << osc::BeginMessage("/visual/file") << filename.c_str() << osc::EndMessage;
            sender.send();
        }
        feedback = "/visual/file " + filename;
    }
    else if(message == "quit")
    {
        sender << osc::BeginMessage("/visual/quit") << osc::EndMessage;
        sender.send();
        feedback = "/visual/quit ";
    }

    // feedback
    cout << "   Sent message: " << feedback << endl;

    return EXIT_SUCCESS;
}
