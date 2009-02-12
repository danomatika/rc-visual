#ifndef SPRITE_GROUP_H
#define SPRITE_GROUP_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL/SDL.h>

#include "Sprite.h"

using namespace std;

// a group of sprites
class Sprite_Group
{
    public:

        Sprite_Group(string name);

        virtual ~Sprite_Group();

        void add(Sprite *sprite);

        int remove(string sprite_name);

        void render(SDL_Surface *screen);

        Sprite *getSprite(string name);

        string inline getName() {return group_name;};

        void print();

    protected:

    private:
        vector<Sprite*> sprite_group;    // sprite vector
        string group_name;  // name of this group
};

#endif // SPRITE_CONTROL_H
