#ifndef TESTAPP_H
#define TESTAPP_H

#include "Application.h"

#include "Rectangle.h"

class TestApp : public Application
{
    public:

        TestApp();

        virtual ~TestApp();

        void setup();

        void update();

        void draw();

        void cleanup();

    protected:

        Rectangle box;

    private:

};

#endif // TESTAPP_H
