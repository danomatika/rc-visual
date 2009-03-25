#include <iostream>
#include <unistd.h>
#include <string>

#include "Common.h"

#include "SdlContext.h"
#include "TestApp.h"
#include "Sprite_File.h"
#include "Sprite_Collection.h"

#include "ClassTests.h"

using namespace std;

ClassTests test;

int main(int argc, char *argv[])
{
    LOG << "starting testMain" << endl;

    //Sprite_File sfile;
    //sfile.loadXml("sprite_test.xml", NULL);

    test.testLog();

    //test.testOscListener();

    //test.testOscSender();

    //test.testXmlFile();

    // initialize SDL context
    SdlContext sdl(640, 480, 16, SdlContext::HARDWARE);
    //sdl.setFullscreen();
    sdl.init();

    // open sdl window
    sdl.createWindow("rc-visual test");

     // init app
    TestApp testApp;
    testApp.setFrameRate(30);
    testApp.setup();

    // main app loop
    testApp.mainLoop();

    // cleanup after exit from loop
    testApp.cleanup();

    // all is well ;)
    LOG << "Exited cleanly" << endl;
    return 0;
}
