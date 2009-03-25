#include "Sprite_Collection.h"


Sprite_Collection::Sprite_Collection()
{
    current_group = 0;
}

Sprite_Collection::~Sprite_Collection()
{
    //dtor
}

void Sprite_Collection::add(Sprite_Group *group)
{
    if(group != NULL)
        sprite_collection.push_back(group);
}

int Sprite_Collection::remove(string group_name)
{
     // look through vector for sprite by name and remove it
    vector<Sprite_Group*>::iterator c;
    int i = 0;
    for(c = sprite_collection.begin(); c != sprite_collection.end(); c++)
    {
        Sprite_Group *g = sprite_collection.at(i);
        if(g->getName() == group_name)
        {
            sprite_collection.erase(c);
            return 0;   // found it
        }
        i++;
    }
    return -1;  // didnt find it
}

void Sprite_Collection::clear()
{
    sprite_collection.clear();
    current_group = 0;
}

void Sprite_Collection::render()
{
    if(!sprite_collection.empty())
    {
        Sprite_Group *g = sprite_collection.at(current_group);
        g->render();
    }
}

void Sprite_Collection::nextGroup()
{
    current_group++;

    if(current_group >= (int) sprite_collection.size())
        current_group = 0;
}

void Sprite_Collection::prevGroup()
{
     current_group--;

    if(current_group < 0)
        current_group = (int) sprite_collection.size()-1;
}

void Sprite_Collection::gotoGroup(int index)
{
    if(index < 0 || index >= (int) sprite_collection.size())
        current_group = index;
}

void Sprite_Collection::gotoGroup(string name)
{
   // loop through vector looking for group by name
    vector<Sprite_Group*>::iterator c;
    int i = 0;
    for(c = sprite_collection.begin(); c != sprite_collection.end(); c++)
    {
        Sprite_Group *g = sprite_collection.at(i);
        if(g->getName() == name)
        {
            current_group = i;
            return;
        }
        i++;
    }
}

Sprite *Sprite_Collection::getSprite(string name)
{
    return sprite_collection[current_group]->getSprite(name);
}

Sprite_Group *Sprite_Collection::getGroup(string name)
{
    // loop through vector looking for group by name
    vector<Sprite_Group*>::iterator c;
    int i = 0;
    for(c = sprite_collection.begin(); c != sprite_collection.end(); c++)
    {
        Sprite_Group *g = sprite_collection.at(i);
        if(g->getName() == name)
            return g;
        i++;
    }
    return NULL;
}

Sprite_Group *Sprite_Collection::getGroupCurrent()
{
    Sprite_Group *g = sprite_collection.at(current_group);
        return g;
}
