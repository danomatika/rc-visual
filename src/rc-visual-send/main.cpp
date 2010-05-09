/*==============================================================================

	main.cpp

	rc-visual-send: send control OSC messages to rc-visual
  
	Copyright (C) 2008, 2010  Dan Wilcox <danomatika@gmail.com>

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
#include <config.h>		// automake config defines

#include <oscframework/oscframework.h>
#include <tclap/tclap.h>

using namespace std;
using namespace osc;

#define OSC_BASE_ADDR   (string) "/"+PACKAGE

#define DEFAULT_IP	"127.0.0.1"
#define DEFAULT_PORT 9990

#define NUM_ACTIONS 4

string actions[NUM_ACTIONS] = { "file", "reload", "scene", "quit" };

int main(int argc, char *argv[])
{
	try {
    
    // the commandline parser
    TCLAP::CommandLine cmd("send control OSC messages to rc-visual", VERSION);
    
    // constraints    
    vector<string> allowedActions;
    for(int i = 0; i < NUM_ACTIONS; ++i)
        allowedActions.push_back(actions[i]);
    TCLAP::ValuesConstraint<string> actionConstraint(allowedActions);
    
    stringstream itoa;
    itoa << DEFAULT_PORT;

    // options to parse
    // short id, long id, description, required?, default value, short usage type description
    TCLAP::ValueArg<string> ipOpt("i","ip",(string) "IP address to send to; default is '"+DEFAULT_IP+"'", false, DEFAULT_IP, "string");
    TCLAP::ValueArg<int> 	portOpt("p","port",(string) "Port to send to; default is '"+itoa.str()+"'", false, DEFAULT_PORT, "int");
    TCLAP::SwitchArg		quietOpt("q", "quiet", "Don't print a summary", false);

    // commands to parse
    // name, description, required?, default value, short usage type description
    TCLAP::UnlabeledValueArg<string> actionCmd("action", "Action to perform", true, "", &actionConstraint);
    TCLAP::UnlabeledValueArg<string> targetCmd("target", "Target, depends on action", false, "", "target");
    
    // add args to parser (in reverse order)
    cmd.add(quietOpt);
    cmd.add(portOpt);
    cmd.add(ipOpt);
    
    // add commands
    cmd.add(actionCmd);
    cmd.add(targetCmd);

    // parse the commandline
    cmd.parse(argc, argv);
    
    // setup the osc sender
    osc::OscSender sender(ipOpt.getValue(), portOpt.getValue());
    
     // compose the message
    string address = (string) OSC_BASE_ADDR + "/" + actionCmd.getValue();
    if(actionCmd.getValue() == "file")
    {
    	if(targetCmd.getValue() == "")
        {
        	cerr << "missing file to load" << endl;
        	return EXIT_FAILURE;
        }
        
        sender << osc::BeginMessage(address);
        sender << targetCmd.getValue();
    }
    else if(actionCmd.getValue() == "scene")
    {
    	/// transport commands
    	if(targetCmd.getValue() == "prev" || targetCmd.getValue() == "next")
        {
    		address += "/" + targetCmd.getValue();
        	sender << osc::BeginMessage(address);
        }
        // choose a scene by name
        else
        {
            sender << osc::BeginMessage(address);
            sender << targetCmd.getValue();
        }
    }
    else
    {
        sender << osc::BeginMessage(address);
    }

    sender << osc::EndMessage();
    
    // send the message
    sender.send();

	// feedback
    if(!quietOpt.getValue())
	{
    	cout << "Target ip: " << ipOpt.getValue() << " port: " << portOpt.getValue() << endl;
    	cout << "Sent message " << address << endl;
	}
	} catch(TCLAP::ArgException &e)  // catch any exceptions
	{
	    cerr << "CommandLine error: " << e.error() << " for arg " << e.argId() << endl;
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
