#ifndef OBJECT_H
#define OBJECT_H

#include "Common.h"

/// base object
class Object : public dwf::Objecti
{
    public:

        Object();

        virtual ~Object();

        virtual void update() {}

        virtual void draw() {}

        // osc templates
        virtual void setFrame()   {}
        virtual void setVisible() {}
        virtual void setAnimate() {}

        virtual void print(std::string indent="") {}

    protected:

    private:

};

#endif // OBJECT_H
