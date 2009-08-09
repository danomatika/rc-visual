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

#include <lo/lo.h>
#include <glib.h> // for GOptions commandline parsing
// http://www.eikke.com/articles/goption-parsing.html

using namespace std;

lo_address osc_send;

int main(int argc, char *argv[])
{
    // args to grab
    gchar *sIpAddr  = NULL;
    gchar *sPort    = NULL;
    gchar *sMsg     = NULL;

    // which commandline options?
    GOptionEntry options[] =
    {
        // long, short. flags(usually 0), arg, arg_data, description (short), arg_description (long)
        { "ip", 'i', 0, G_OPTION_ARG_STRING, &sIpAddr, "ip address to send to", "'127.0.0.1', '192.168.0.100', etc" },
        { "port", 'p', 0, G_OPTION_ARG_STRING, &sPort, "port to send to", "'4000'" },
        { NULL }
    };

    // create context
    GOptionContext *ctx;
    ctx = g_option_context_new("message");
    g_option_context_add_main_entries(ctx, options, "rc-visual-send");
    g_option_context_parse(ctx, &argc, &argv, NULL);

    // are there enough args and a message?
    if(argc <= 1)
    {
        cout << g_option_context_get_help(ctx, TRUE, NULL);
        cout << "Messages:" << endl
             << "   file    filename.xml" << endl
             << "   quit" << endl;
        return 0;
    }

    // grab devname, assume its the last argument
    sMsg = argv[argc-1];

    // is there an ip?
    if(sIpAddr == NULL)
    {
        sIpAddr = (gchar*) "127.0.0.1";
    }

    // is ther a port?
    if(sPort == NULL)
    {
        sPort = (gchar*) "9990";
    }

    osc_send = lo_address_new(sIpAddr, sPort);


    istringstream ss((string) sMsg);
    string msg, feedback;
    ss >> msg;

    if(msg == "file")
    {
        string filename;
        ss >> filename;

        if(filename != "")
        {
            lo_send(osc_send, "/visual/file", "s", filename.c_str());
        }
        feedback = "/visual/file " + filename;
    }

    else if(msg == "quit")
    {
        lo_send(osc_send, "/visual/quit", "");
        feedback = "/visual/quit ";
    }

    // feedback
    cout << "   Sent message: " << feedback << endl;

    // free the GOptions
    g_option_context_free(ctx);

    return 0;
}
