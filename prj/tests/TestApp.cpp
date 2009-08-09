#include "TestApp.h"

TestApp::TestApp()
{
    //ctor
}

TestApp::~TestApp()
{
    //dtor
}

void TestApp::setup()
{
    box.set(100, 100, 100, 100);
    _background.set(255, 0, 255);
}

void TestApp::update()
{
}

void TestApp::draw()
{
    box.draw();
}

void TestApp::cleanup()
{
}
