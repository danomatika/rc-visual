#include "Visual.h"

#define OSC_PD_ADDR     "/pd/visual"
#define OSC_PDKEY_ADDR  "/pd/devices/keyboard"

Visual::Visual()
{
    _sendAddr = "127.0.0.1";
    _sendPort = 8880;
    _recvAddr = "127.0.0.1";
    _recvPort = 9990;

    _iNotify = -1;
}

Visual::~Visual()
{
    //dtor
}

bool Visual::setup(int argc, char** argv)
{
    // args to grab
    gchar *mode         = NULL;
    gchar *filename     = NULL;
    gboolean bLoadtest  = false;
    gchar *s_addr       = NULL;
    gchar *r_addr       = NULL;

    // which commandline options?
    GOptionEntry options[] = {
        // long, short. flags(usually 0), arg, arg_data, description (short), arg_description (long)
        { "mode", 'm', 0, G_OPTION_ARG_STRING, &mode, "windowed or fullscreen mode", "'window' or 'fullscreen'" },
        { "file", 'f', 0, G_OPTION_ARG_STRING, &filename, "file to load" },
        { "test", 't', 0, G_OPTION_ARG_NONE, &bLoadtest, "test load the file and exit", "'true' or 'false'" },
        { "address", 'a', 0, G_OPTION_ARG_STRING, &s_addr, "ip addr to send osc to", "'127.0.0.1', '192.0.0.101', etc" },
        { "port", 'p', 0, G_OPTION_ARG_INT, &_sendPort, "port to send osc to", "'4440', '2388', etc" },
        { "listen", 'l', 0, G_OPTION_ARG_INT, &_recvPort, "port to recieve osc on", "'4440', '2388', etc" },
        { "notify", 'n', 0, G_OPTION_ARG_INT, &_iNotify, "tell pd to open a connection", "connection #" },
        { "receive", 'r', 0, G_OPTION_ARG_STRING, &r_addr, "ip addr to recv osc from (def: 127.0.0.1)", "'127.0.0.1', '192.0.0.101', etc" },
        { "debug", 'd', 0, G_OPTION_ARG_NONE, &_bDebug, "print debug messages", "'true' or 'false'" },
        { NULL }
    };

    // create context
    GOptionContext *ctx;
    ctx = g_option_context_new("simple visual sprite engine controlled over OSC");
    g_option_context_add_main_entries(ctx, options, "visual");
    g_option_context_parse(ctx, &argc, &argv, NULL);

    // no args, set defaults
    if(mode == NULL)
        mode = (gchar*) "window";

    // get values
    if(s_addr != NULL)  _sendAddr = (std::string) s_addr;
    if(r_addr != NULL)  _recvAddr = (std::string) r_addr;

    // load the file and print contents, do not start graphics
    if(bLoadtest)
    {
        // read file
        if(filename != NULL)
        {
            loadXmlFile((std::string) filename);
        }
        return false;
    }

    // read file
    if(filename != NULL)
    {
        if(!loadXmlFile((std::string) filename))
        {
            LOG << "Could not load file due to errors" << std::endl;
            return false;
        }
    }

    // check values
    if((std::string) mode != "window" && (std::string) mode != "fullscreen")
    {
        LOG << g_option_context_get_help(ctx, TRUE, NULL);
        return false;
    }

    // set background refresh color
    _background.set(0, 0, 0);

    // start osc listener
    this->setPort(_recvPort);
    this->startListening();

    // set send addr
    _oscSender.setAddr(_sendAddr, _sendPort);

    // tell pd to open a connection
    if(_iNotify >= 0)
    {
        LOG << "Notifying pd to open a connection" << std::endl;
        _oscSender << osc::BeginMessage(OSC_PD_ADDR) << "connect" << (float) _iNotify << _recvAddr.c_str() << osc::EndMessage;
        _oscSender.send();
    }

    return true;
}

void Visual::update()
{
    _scene.update();
}

void Visual::draw()
{
    _scene.draw();
}

void Visual::cleanup()
{
    // stop osc listener
    this->stopListening();

    // tell pd to close the connection
    if(_iNotify >= 0)
    {
        LOG << "Notifying pd to close the connection" << std::endl;
        _oscSender << osc::BeginMessage(OSC_PD_ADDR) << "disconnect" << (float) _iNotify << osc::EndMessage;
        _oscSender.send();
    }
}

bool Visual::loadXmlFile(std::string filename)
{
    TiXmlDocument xmlDoc;

    LOG << "loadXmlFile(): Loading \"" << filename << "\"" << std::endl;

    TiXmlElement* xmlPtr = dwf::Xml::loadFile(&xmlDoc, filename);
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "loadXmlFile(): Failed to load \"" << filename << "\":"
                  << dwf::Xml::getErrorString(xmlDoc) << std::endl;
        return false;
    }

    if(xmlPtr->ValueStr() != "visual")
    {
        LOG_ERROR << "loadXmlFile(): Doc root \"" << xmlPtr->ValueStr()
                  << "\" != \"visual\"" << std::endl;
        return false;
    }

    // clear the scene first
    _scene.clear();

    TiXmlElement* pElems = xmlPtr->FirstChildElement();
    if(!_scene.loadXml(pElems))
    {
        LOG_ERROR << "loadXmlFile(): Could not load xml scene" << std::endl;
        return false;
    }

    return true;
}

/*
    server.addRecvMethod("/visual/file", "s", file_handler);
    server.addRecvMethod("/visual/quit", NULL, quit_handler);
    server.addRecvMethod("/visual/group", "s", group_handler);
    server.addRecvMethod("/visual/framerate", "i", framerate_handler);

    // sprite manipulation
    server.addRecvMethod("/visual/size", "sii", size_handler); // name, width, height
    server.addRecvMethod("/visual/pos", "sii", pos_handler); // name, x, y
    server.addRecvMethod("/visual/color", "siiii", color_handler); // name, r, g, b, a
    server.addRecvMethod("/visual/frame", "ss", frame_handler); // name, "next" or "prev" frame
    server.addRecvMethod("/visual/visible", "si", hide_handler); // name, boolean to display
    server.addRecvMethod("/visual/animate", "si", animate_handler); // name, boolean to animate
*/
void Visual::process(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
{
    osc::ReceivedMessageArgumentIterator arg = m.ArgumentsBegin();
   // osc::ReceivedMessageArgument arg = argItr;

    // print message?
    if(_bDebug)
    {
        LOG << "OSC " << m.AddressPattern() << " " << m.TypeTags() << std::endl;
    }

    // visual manipulation
    if((std::string) m.AddressPattern() == "/visual/file" && (std::string) m.TypeTags() == "s")
    {
        std::string filename = arg->AsString();

        // read file
        if(filename != "")
        {
            if(!this->loadXmlFile(filename))
            {
                LOG << "Could not load file due to errors" << std::endl;
                return;
            }
        }
    }
    else if((std::string) m.AddressPattern() == "/visual/quit")
    {
        // stop the application
        this->stop();
    }
    else if((std::string) m.AddressPattern() == "/visual/group" && (std::string) m.TypeTags() == "s")
    {
        // change to a different group
        _scene.gotoGroup(arg->AsString());
    }
    else if((std::string) m.AddressPattern() == "/visual/framerate" && (std::string) m.TypeTags() == "i")
    {
        this->setFrameRate(arg->AsInt32());
    }

    // object manipulation
    else if((std::string) m.AddressPattern() == "/visual/size" && (std::string) m.TypeTags() == "sii")
    {
        // set the size
        if(!_scene.isEmpty())
        {
            // get object
            Rectangle* object = _scene.getGroup()->getObject(arg->AsString());
            if(object != NULL)
            {
                int w = arg->AsInt32();
                arg++;
                int h = arg->AsInt32();
                object->setSize(w, h);
            }
        }
    }
    else if((std::string) m.AddressPattern() == "/visual/pos" && (std::string) m.TypeTags() == "sii")
    {
        // set the pos
        if(!_scene.isEmpty())
        {
            // get object
            Rectangle* object = _scene.getGroup()->getObject(arg->AsString());
            if(object != NULL)
            {
                arg++;
                int x = arg->AsInt32();
                arg++;
                int y = arg->AsInt32();
                object->setPos(x, y);
            }
        }
    }
    else if((std::string) m.AddressPattern() == "/visual/color" && (std::string) m.TypeTags() == "siii")
    {
        // set the pos
        if(!_scene.isEmpty())
        {
            // get object
            Rectangle* object = _scene.getGroup()->getObject(arg->AsString());
            if(object != NULL)
            {
                arg++;
                int r = arg->AsInt32();
                arg++;
                int g = arg->AsInt32();
                arg++;
                int b = arg->AsInt32();
                object->color.set(r, g, b);
            }
        }
    }
    else if((std::string) m.AddressPattern() == "/visual/frame"
        && ((std::string) m.TypeTags() == "ss" || (std::string) m.TypeTags() == "si"))
    {
        // set the frame
        if(!_scene.isEmpty())
        {
            // get object
            Rectangle* object = _scene.getGroup()->getObject(arg->AsString());
            if(object != NULL)
            {
                // next, prev
                if((std::string) m.TypeTags() == "ss")
                {
                    arg++;
                    std::string what = arg->AsString();

                    if(what == "next")
                    {
                        object->nextFrame();
                    }
                    else if(what == "prev")
                    {
                        object->prevFrame();
                    }
                }
                // frame num
                else if((std::string) m.TypeTags() == "si")
                {
                    arg++;
                    int i = arg->AsInt32();
                    object->gotoFrame(i);
                }
            }
        }
    }
    else if((std::string) m.AddressPattern() == "/visual/visible" && (std::string) m.TypeTags() == "si")
    {
        // set the visible
        if(!_scene.isEmpty())
        {
            // get object
            Rectangle* object = _scene.getGroup()->getObject(arg->AsString());
            if(object != NULL)
            {
                arg++;
                bool b = arg->AsBool();
                object->setVisible(b);
            }
        }
    }
    else if((std::string) m.AddressPattern() == "/visual/animate" && (std::string) m.TypeTags() == "si")
    {
        // set the animate
        if(!_scene.isEmpty())
        {
            // get object
            Rectangle* object = _scene.getGroup()->getObject(arg->AsString());
            if(object != NULL)
            {
                arg++;
                bool b = arg->AsBool();
                object->setAnimate(b);
            }
        }
    }
}
