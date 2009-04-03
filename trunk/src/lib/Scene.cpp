#include "Scene.h"

Scene::Scene() : _curGroup(0)
{
    //ctor
}

Scene::~Scene()
{
    clear();
}

void Scene::add(Group* grp)
{
    if(grp != NULL)
    {
        _groups.push_back(grp);
    }
}

void Scene::nextGroup()
{
    _curGroup++;

    if(_curGroup >= _groups.size())
    {
        _curGroup = 0;
    }
}

void Scene::prevGroup()
{
    if(_curGroup == 0)
    {
        _curGroup = _groups.size()-1;
    }
    else
    {
        _curGroup--;
    }
}

void Scene::gotoGroup(int group)
{
    if(group < 0 || group >= (int) _groups.size())
        return;

    _curGroup = group;
}

void Scene::gotoGroup(std::string group)
{
    // find index of group if it exists and set current group to index
    int index = 0;
    for(std::vector<Group*>::iterator g = _groups.begin(); g != _groups.end(); ++g)
    {
        if((*g)->getName() == group)
        {
            _curGroup = index;
            return;
        }
        index++;
    }
}

void Scene::clear()
{
    for(std::vector<Group*>::iterator g = _groups.begin(); g != _groups.end(); ++g)
    {
        delete (*g);
    }
}

void Scene::draw()
{
    if(_groups.empty())
        return;

    _groups[_curGroup]->draw();
/*
    for(std::vector<Group*>::iterator g = _groups.begin(); g != _groups.end(); ++g)
    {
        (*g)->draw();
    }
*/
}

void Scene::update()
{
    if(_groups.empty())
        return;

    _groups[_curGroup]->draw();
/*
    for(std::vector<Group*>::iterator g = _groups.begin(); g != _groups.end(); ++g)
    {
        (*g)->update();
    }
*/
}

bool Scene::loadXml(TiXmlElement* xmlPtr)
{
    if(!xmlPtr)
        return false;

    TiXmlElement* pElems = xmlPtr;
    while(pElems != NULL)
    {
        if(pElems->ValueStr() == "group")
        {
            LOG << "Group \"" << pElems->Attribute("name") << "\"" << std::endl;

            Group* g = new Group();
            if(!g->loadXml(pElems))
            {
                LOG_WARN << "Scene: could not load group, ignoring" << std::endl;
                delete g;
            }
            else
            {
                g->print("  ");
                add((Group*) g);
            }
        }
        else
        {
            LOG_WARN << "Scene: Ignoring unknown element \"" << pElems->ValueStr() << "\"" << std::endl;
        }

        pElems = pElems->NextSiblingElement();
    }

    return true;
}
