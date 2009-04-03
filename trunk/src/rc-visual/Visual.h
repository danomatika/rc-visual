#ifndef VISUAL_H
#define VISUAL_H

#include <glib.h> // for GOptions commandline parsing
// http://www.eikke.com/articles/goption-parsing.html

#include "Common.h"

#include "Rectangle.h"
#include "Scene.h"

class Visual : public dwf::Application, public dwf::OscListener
{
    public:

        Visual();

        virtual ~Visual();

        void setup() {}

        bool setup(int argc, char** argv);

        void update();

        void draw();

        void cleanup();

        bool loadXmlFile(std::string filename);

    protected:

        void process(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);

        Scene _scene;

        dwf::OscSender _oscSender;

        std::string _sendAddr;
        int _sendPort;
        std::string _recvAddr;
        int _recvPort;
        std::string _oscKeyAddr;
        std::string _oscPdAddr;

        gboolean _bDebug;
        gboolean _iNotify;
};

#endif // VISUAL_H
