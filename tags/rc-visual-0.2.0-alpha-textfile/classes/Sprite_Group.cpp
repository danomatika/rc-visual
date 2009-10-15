#include "Sprite_Group.h"


Sprite_Group::Sprite_Group(string name)
{
    group_name = name;
}

Sprite_Group::~Sprite_Group()
{
    //dtor
}

void Sprite_Group::add(Sprite *sprite)
{
    if(sprite != NULL)
        sprite_group.push_back(sprite);
}

int Sprite_Group::remove(string sprite_name)
{
    // look through vector for sprite by name and remove it
    vector<Sprite*>::iterator c;
    int i = 0;
    for(c = sprite_group.begin(); c != sprite_group.end(); c++)
    {
        Sprite *s = sprite_group.at(i);
        if(s->getName() == sprite_name)
        {
            sprite_group.erase(c);
            return 0;   // found it
        }
        i++;
    }
    return -1;  // didnt find it
}

void Sprite_Group::render(SDL_Surface *screen)
{
    // loop through vector rendering stuff
    vector<Sprite*>::iterator c;
    int i = 0;
    for(c = sprite_group.begin(); c != sprite_group.end(); c++)
    {
        Sprite *s = sprite_group.at(i);
        s->render(screen);
        i++;
    }
}

Sprite *Sprite_Group::getSprite(string name)
{
    // loop through vector looking for sprite by name
    vector<Sprite*>::iterator c;
    int i = 0;
    for(c = sprite_group.begin(); c != sprite_group.end(); c++)
    {
        Sprite *s = sprite_group.at(i);
        if(s->getName() == name)
            return s;
        i++;
    }
    return NULL;
}

void Sprite_Group::print()
{
    cout << group_name << endl;

    vector<Sprite*>::iterator c;
    int i = 0;
    for(c = sprite_group.begin(); c != sprite_group.end(); c++)
    {
        Sprite *s = sprite_group.at(i);
        s->print();
        i++;
    }
}
