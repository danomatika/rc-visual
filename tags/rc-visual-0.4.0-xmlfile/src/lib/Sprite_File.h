#ifndef SPRITE_FILE_H
#define SPRITE_FILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// TinyXml++: http://code.google.com/p/ticpp/
// examples: http://www.uwplatt.edu/csse/tools/visual-studio/ticpp/
#include "tinyxml.h"
#define TIXML_USE_STL

#include "Sprite_Collection.h"
#include "Log.h"

class Sprite_File
{
    public:

        Sprite_File();

        virtual ~Sprite_File();

        // original file loader
        void load(string filename, Sprite_Collection *dest);

        // xml file loader
        bool loadXml(string filename, Sprite_Collection *dest);

        void inline printDebug(bool yesno) {debug = yesno;};

    protected:

    private:

        // returns true if successful read, false it bad read
        bool getGroup(TiXmlElement *xml_ptr, Sprite_Group *group);

        bool getSprite(TiXmlElement *xml_ptr, Sprite *sprite);

        bool getFrame(TiXmlElement *xml_ptr, Sprite* sprite);

        // OLD BELOW
/*
        Sprite *grabSprite();

        Sprite_Group *grabGroup();

        void eatLine();

        void eatSpaces();

        void ignore();
*/
        ifstream *file;
        int current_line;

        bool debug;
};

#endif // SPRITE_FILE_H
