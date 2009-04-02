/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef CLASSTESTS_H
#define CLASSTESTS_H

// classes to test
#include "XmlFile.h"
#include "OscListener.h"
#include "OscSender.h"

class ClassTests
{
    public:

        ClassTests();

        virtual ~ClassTests();

        void testLog();

        void testXmlFile();

        static void processOSC(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);

        void testOscListener();

        void testOscSender();
};

#endif // CLASSTESTS_H
