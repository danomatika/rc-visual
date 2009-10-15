#ifndef SPRITE_FILE_H
#define SPRITE_FILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "Sprite_Collection.h"

class Sprite_File
{
    public:

        Sprite_File();

        virtual ~Sprite_File();

        // original file loader
        void load(string filename, Sprite_Collection *dest);

        // xml file loader
        void loadXml(string filename, Sprite_Collection *dest);

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
