#ifndef SPRITE_FILE_H
#define SPRITE_FILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Sprite_Collection.h"

class Sprite_File
{
    public:

        Sprite_File();

        virtual ~Sprite_File();

        void load(string filename, Sprite_Collection *dest);

        void inline printDebug(bool yesno) {debug = yesno;};

    protected:

    private:

        Sprite *grabSprite();

        Sprite_Group *grabGroup();

        void eatLine();

        void eatSpaces();

        void ignore();

        ifstream *file;
        int current_line;

        bool debug;
};

#endif // SPRITE_FILE_H
