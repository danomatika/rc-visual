#ifndef VISUAL_H
#define VISUAL_H

#include "Application.h"

#include "Rectangle.h"
#include "Pressure.h"

class Visual : public Application
{
    public:

        Visual();

        virtual ~Visual();

        void setup();

        void update();

        void draw();

        void cleanup();

    protected:

        Pressure pressure;

    private:

};

#endif // VISUAL_H
