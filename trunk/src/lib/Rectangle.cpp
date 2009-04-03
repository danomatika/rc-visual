#include "Rectangle.h"

Rectangle::Rectangle() : dwf::Objecti(), color(255, 255, 255, 255), _name("")
{}

Rectangle::Rectangle(int x, int y, int W, int H, int vx, int vy):
    dwf::Objecti(x, y, W, H, vx, vy), color(255, 255, 255, 255), _name("") {}

/// copy constructor
Rectangle::Rectangle(const Rectangle& from) : dwf::Objecti(from)
{
    color = from.color;
    _name = from._name;
}

/// copy operator
void Rectangle::operator=(Rectangle& from)
{
    // from http://krishnakoney.blogspot.com/2008/05/copy-constructors-assignment-operator.html
    (dwf::Objecti&) *this = from; // call Object copy operator
    color = from.color;
    _name = from._name;
}

bool Rectangle::loadXml(const TiXmlElement* xmlPtr)
{
    if(!xmlPtr)
        return false;
    // get name
    dwf::Xml::getAttrString(xmlPtr, "name", _name);

    // get pos, size, vel
    const TiXmlElement* pElems = xmlPtr->FirstChildElement();
    std::string elemName;
    while(pElems != NULL)
    {
        elemName = pElems->ValueStr();

        if(elemName == "pos")
        {
            dwf::Xml::getAttrInt(pElems, "x", &pos.x);
            dwf::Xml::getAttrInt(pElems, "y", &pos.y);
        }
        else if(elemName == "size")
        {
            dwf::Xml::getAttrInt(pElems, "w", &w);
            dwf::Xml::getAttrInt(pElems, "h", &h);
        }
        else if(elemName == "vel")
        {
            dwf::Xml::getAttrInt(pElems, "x", &vel.x);
            dwf::Xml::getAttrInt(pElems, "y", &vel.y);
        }
        else if(elemName =="color")
        {
            dwf::Xml::getAttrInt(pElems, "r", (int*) &color.R);
            dwf::Xml::getAttrInt(pElems, "g", (int*) &color.G);
            dwf::Xml::getAttrInt(pElems, "b", (int*) &color.B);
            dwf::Xml::getAttrInt(pElems, "a", (int*) &color.A);
        }

        pElems = pElems->NextSiblingElement();
    }

    return true;
}

void Rectangle::draw()
{
    dwf::Graphics::drawRectFilled(pos.x, pos.y, w, h, &color);
}

void Rectangle::print(std::string indent)
{
    LOG << indent << "name: \"" << _name << "\"" << std::endl
        << indent << "x: " << pos.x << " y: " << pos.y << std::endl
        << indent << "w: " << w << " h: " << h << std::endl
        << indent << "vx: " << vel.x << " vy: " << vel.y << std::endl
        << indent << "r: " << color.R << " g: " << color.G
            << " b: " << color.B << " a: " << color.A << std::endl;
}
