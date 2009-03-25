/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#include "ClassTests.h"

ClassTests::ClassTests()
{}

ClassTests::~ClassTests()
{}

void ClassTests::testLog()
{
    LOG << std::endl << "This is a normal log message" << std::endl;
    LOG_DEBUG << "This is a debug log message" << std::endl;
    LOG_WARN << "This is a warning message" << std::endl;
    LOG_ERROR << "This is an error message" << std::endl << std::endl;
}

void ClassTests::testXmlFile()
{
    LOG << "Begin testXmlFile()" << std::endl;

    XmlFile xmlFile;
    std::string file = "sprite_test.xml";

    if(!xmlFile.loadFile(file))
    {
        LOG << "    Failed to load \"" << file << "\"" << std::endl;
        return;
    }

    LOG << "    Loaded \"" << file << "\"" << std::endl;

    if(xmlFile.getElementName() != "test")
    {
        LOG << "    Doc Root \"" << xmlFile.getElementName() << "\" != \"test\"" << std::endl;
        return;
    }

    xmlFile.gotoChildElement();
}

void ClassTests::processOSC(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
{
    LOG << " Recieved OSC message to osc addr \"" << m.AddressPattern() << "\"" << std::endl;
}

void ClassTests::testOscListener()
{
    OscListener listener(7000);
    listener.processFunc(&processOSC);
    listener.startListening();
    sleep(20);
    listener.stopListening();
}

void ClassTests::testOscSender()
{
    OscSender sender("127.0.0.1", 8000);
    sender << osc::BeginMessage( "/test1" )
           << 0 << 10 << "hello" << osc::EndMessage;
    sender.send();
    sleep(10);
    sender << osc::BeginMessage( "/test2" )
           << 1 << "world" << osc::EndMessage;
    sender.send();
}
