
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Common.h"
#include "Object.h"

/**
    \class Rectangle
    \brief a colored gl rectangle
**/
class Rectangle : public dwf::Objecti
{
    public:

        dwf::Color4ub color;

        Rectangle();

        Rectangle(int x, int y, int W, int H, int vx=0, int vy=0);

        Rectangle(const Rectangle& from);

        void operator=(Rectangle& from);

        virtual ~Rectangle() {}

        // variable set or gets
        void setColor(dwf::Color4ub& color_) {color = color_;}
        void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255)
            {color.set(r, g, b, a);}
        inline std::string getName() {return _name;}
        inline void setName(std::string name) {_name = name;}

        // osc templates
        virtual void setVisible(bool b) {}
        virtual void setAnimate(bool b) {}
        void nextFrame() {}
        void prevFrame() {}
        void gotoFrame(uint frameIndex) {}

        bool loadXml(const TiXmlElement* xmlPtr);

        virtual void update() {}

        /// draws from the center
        virtual void draw();

        virtual void print(std::string indent="");

    protected:

        std::string _name;
};

#endif // RECTANGLE_H
