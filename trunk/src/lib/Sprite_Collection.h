#ifndef SPRITE_COLLECTION_H
#define SPRITE_COLLECTION_H

#include <iostream>
#include <vector>

#include <SDL/SDL.h>

#include "Sprite_Group.h"

using namespace std;

// a collection of sprite groups
class Sprite_Collection
{
    public:

        Sprite_Collection();

        virtual ~Sprite_Collection();

        void add(Sprite_Group *group);

        int remove(string group_name);

        void clear();

        void render();

        void nextGroup();

        void prevGroup();

        void gotoGroup(int index);

        void gotoGroup(string name);

        Sprite *getSprite(string name);

        Sprite_Group *getGroupCurrent();

        Sprite_Group *getGroup(string name);

    protected:

    private:
        vector<Sprite_Group*> sprite_collection;         // list of sprite groups
        int current_group;   // which group we are on

};

#endif // SPRITE_COLLECTION_H
