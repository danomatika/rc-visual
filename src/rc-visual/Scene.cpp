/*==============================================================================

	Scene.cpp

	rc-visual: a simple, osc-controlled 2d graphics engine
  
	Copyright (C) 2007, 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "Scene.h"

#include "objects/Objects.h"

Scene::Scene(string name, string parentOscAddress) : XmlObject("scene"),
	OscObject(parentOscAddress+"/"+name),
	_name(name), _background(0, 0, 0, 255), _fps(-1)
{
    // attach variables to Xml
    addXmlAttribute("R", "background", XML_TYPE_BYTE, &_background.R);
    addXmlAttribute("G", "background", XML_TYPE_BYTE, &_background.G);
    addXmlAttribute("B", "background", XML_TYPE_BYTE, &_background.B);
    addXmlAttribute("A", "background", XML_TYPE_BYTE, &_background.A);

    addXmlAttribute("name", "scene", XML_TYPE_STRING, &_name);
    addXmlAttribute("fps", "scene", XML_TYPE_UINT, &_fps);
	
	LOG << "SCENE " << parentOscAddress+"/"+name << endl;
}

Scene::~Scene()
{
    clear();
}

void Scene::addObject(DrawableObject* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "Scene \"" << _name << "\": Cannot add NULL object" << endl;
        return;
    }

    addXmlObject(object);
    addOscObject(object);

    _objectList.push_back(object);
}

void Scene::removeObject(DrawableObject* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "Scene \"" << _name << "\": Cannot remove NULL object" << endl;
        return;
    }

    vector<DrawableObject*>::iterator iter;
    iter = find(_objectList.begin(), _objectList.end(), object);
    if(iter != _objectList.end())
    {
        removeXmlObject((*iter));
        removeOscObject((*iter));

        _objectList.erase(iter);
    }
}

void Scene::clear()
{
    /// delete all the objects
    for(unsigned int i = 0; i < _objectList.size(); ++i)
    {
        DrawableObject* o = _objectList.at(i);

        removeXmlObject(o);
        removeOscObject(o);

        delete o;
    }
    _objectList.clear();
}

void Scene::setup()
{
	for(unsigned int i = 0; i < _objectList.size(); ++i)
    {
    	_objectList.at(i)->setup();
  	}
}

void Scene::draw()
{
    vector<DrawableObject*>::iterator iter;
    for(iter = _objectList.begin(); iter != _objectList.end(); ++iter)
    {
        // remove any NULL objects
        if((*iter) == NULL)
        {
            _objectList.erase(iter);
            LOG_ERROR << "Scene \"" << _name << "\": Removed NULL object" << endl;
        }
        else
            (*iter)->draw();
    }
}

/* ***** XML CALLBACKS ***** */

bool Scene::readXml(TiXmlElement* e)
{
    string objName;

    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "pixel")
        {
            if((objName = Xml::getAttrString(child, "name")) != "")
            {
                Pixel* p = new Pixel(objName, getOscRootAddress());
                p->loadXml(child);
                addObject(p);
				
				LOG_DEBUG << "Scene \"" << _name << "\": Loaded pixel \"" << objName << "\" \""
						  << p->getOscRootAddress() << "\"" << std::endl;
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load pixel without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "line")
        {
            if((objName = Xml::getAttrString(child, "name")) != "")
            {						  
				Line* l = new Line(objName, getOscRootAddress());
                l->loadXml(child);
                addObject(l);
				
				LOG_DEBUG << "Scene \"" << _name << "\": Loaded line \"" << objName << "\" \""
						  << l->getOscRootAddress() << "\"" << std::endl;
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load line without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "rect")
        {
            if((objName = Xml::getAttrString(child, "name")) != "")
            {
                Rect* r = new Rect(objName, getOscRootAddress());
                r->loadXml(child);
                addObject(r);
				
				LOG_DEBUG << "Scene \"" << _name << "\": Loaded rect \"" << objName << "\" \""
						  << r->getOscRootAddress() << "\"" << std::endl;
			}
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load rect without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "bitmap")
        {
            if((objName = Xml::getAttrString(child, "name")) != "")
            {
                Bitmap* b = new Bitmap(objName, getOscRootAddress());
                b->loadXml(child);
                addObject(b);
				
				LOG_DEBUG << "Scene \"" << _name << "\": Loaded bitmap \"" << objName << "\" \""
						  << b->getOscRootAddress() << "\"" << std::endl;
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load bitmap without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "sprite")
        {
            if((objName = Xml::getAttrString(child, "name")) != "")
            {
                Sprite* s = new Sprite(objName, getOscRootAddress());
                s->loadXml(child);
                addObject(s);
				
				LOG_DEBUG << "Scene \"" << _name << "\": Loaded sprite \"" << objName << "\" \""
						  << s->getOscRootAddress() << "\"" << std::endl;
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load sprite without name, line "
                         << child->Row() << endl;
            }
        }
        
        else if(child->ValueStr() == "image")
        {
            if((objName = Xml::getAttrString(child, "name")) != "")
            {
                Image* i = new Image(objName, getOscRootAddress());
                i->loadXml(child);
                addObject(i);
				
				LOG_DEBUG << "Scene \"" << _name << "\": Loaded image \"" << objName << "\" \""
						  << i->getOscRootAddress() << "\"" << std::endl;
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load image without name, line "
                         << child->Row() << endl;
            }
        }
		
		else if(child->ValueStr() == "text")
        {
            if((objName = Xml::getAttrString(child, "name")) != "")
            {
                Text* t = new Text(objName, getOscRootAddress());
                t->loadXml(child);
                addObject(t);
				
				LOG_DEBUG << "Scene \"" << _name << "\": Loaded text \"" << objName << "\" \""
						  << t->getOscRootAddress() << "\"" << std::endl;
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load rect without name, line "
                         << child->Row() << endl;
            }
        }

		else if(child->ValueStr() != "background")
        {
            LOG_WARN << "Scene \"" << _name << "\": ignoring unknown element \""
                     << child->ValueStr() << "\"" << endl;
        }


        child = child->NextSiblingElement();
    }

    return true;
}
