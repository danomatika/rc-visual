#include "Group.h"

#include "BitmapSprite.h"

Group::Group()
{
    //ctor
}

Group::~Group()
{
    for(std::vector<Rectangle*>::iterator o = _objects.begin(); o != _objects.end(); ++o)
    {
        delete (*o);
    }
}

void Group::add(Rectangle* obj)
{
    if(obj != NULL)
    {
        _objects.push_back(obj);
    }
}

Rectangle* Group::getObject(std::string name)
{
    // loop through vector looking for sprite by name
    for(std::vector<Rectangle*>::iterator o = _objects.begin(); o != _objects.end(); ++o)
    {
        if((*o)->getName() == name)
            return (*o);
    }
    return NULL;
}

void Group::draw()
{
    for(std::vector<Rectangle*>::iterator o = _objects.begin(); o != _objects.end(); ++o)
    {
        (*o)->draw();
    }
}

void Group::update()
{
    for(std::vector<Rectangle*>::iterator o = _objects.begin(); o != _objects.end(); ++o)
    {
        (*o)->update();
    }
}

void Group::print(std::string indent)
{
    LOG << indent << "Group \"" << _name << "\"" << std::endl;
    for(std::vector<Rectangle*>::iterator o = _objects.begin(); o != _objects.end(); ++o)
    {
        (*o)->print(indent+"    ");
    }
}

bool Group::loadXml(TiXmlElement* xmlPtr)
{
    if(!xmlPtr)
        return false;

    // get name
    dwf::Xml::getAttrString(xmlPtr, "name", _name);

    TiXmlElement* pElems = xmlPtr->FirstChildElement();
    while(pElems != NULL)
    {
        if(pElems->ValueStr() == "bitmapsprite")
        {
            LOG << "BitmapSprite" << std::endl;

            BitmapSprite* s = new BitmapSprite();
            if(!s->loadXml(pElems))
            {
                LOG_WARN << "Group \"" << _name << "\": could not load bitmapsprite, ignoring" << std::endl;
                delete s;
            }
            else
            {
                //s->print();
                LOG << std::endl;
                add((Rectangle*) s);
            }
        }


        else if(pElems->ValueStr() == "rectangle")
        {
            LOG << "Rectangle" << std::endl;

            Rectangle* r = new Rectangle();
            if(!r->loadXml(pElems))
            {
                LOG_WARN << "Group \"" << _name << "\": Could not load rectangle, ignoring" << std::endl;
                delete r;
            }
            else
            {
                LOG_DEBUG << "Group \"" << _name << "\": Loading rectangle" << std::endl;
                //r->print();
                add((Rectangle*) r);
            }
        }
        else
        {
            LOG_WARN << "Group \"" << _name << "\": Ignoring unknown element \"" << pElems->ValueStr() << "\"" << std::endl;
        }

        pElems = pElems->NextSiblingElement();
    }

    return true;
}
