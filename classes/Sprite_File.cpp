#include "Sprite_File.h"


Sprite_File::Sprite_File()
{
    file = NULL;
    current_line = 0;

    debug = false;
}

Sprite_File::~Sprite_File()
{
    //dtor
}

void loadXml(string filename, Sprite_Collection *dest)
{
    xmlChar *txt;
    xmlDocPtr xml_file;
    xmlNodePtr xml_ptr, sub;

    if(!(xml_file = xmlParseFile(filename.c_str())))
    {
        cout << "Sprite_File: XML file not parsed successfully" << endl;
        xmlFreeDoc(xml_file);
        return;
    }

    if(!(xml_ptr = xmlDocGetRootElement(xml_file)))
    {
        cout << "Sprite_File: XML file has no root element." << endl;
        xmlFreeDoc(xml_file);
        return;
    }

    if(xmlStrcmp(xml_ptr->name, (const xmlChar*) "data"))
    {
        cout << "Sprite_File: XML file of the wrong type, root node != data" << endl;
        xmlFreeDoc(xml_file);
        return;
    }

    sub = xml_ptr->children;
    while(sub != NULL)
    {
        if((!xmlStrcmp(sub->name, (const xmlChar*)"array" )))
        {
            txt = xmlGetProp(sub, (const xmlChar*)"name");
            printf("array %s:\n", txt);
            xmlFree(txt);
            txt = xmlNodeListGetString(xml_file, sub->children, 1);
            printf("%s\n", txt);
            xmlFree(txt);
        }
        sub = sub->next;
    }

    xmlFreeDoc(xml_file);

}

void Sprite_File::load(string filename, Sprite_Collection *dest)
{
    file = new ifstream(filename.c_str(), ios::in);

    if(file == NULL)    // open failed
    {
        cerr << "Sprite_File: error opening file \"" << filename << "\"" << endl;
        return;
    }

    dest->clear();

    cout << "Sprite_File: loading " << filename << endl;

    char c;
    string command;
    while(!file->eof()) // read the whole file
    {
        ignore();   // clear chars

        if(file->peek() == '!') // a control word?
        {
            c = file->get(); // eat '!'

            if(isalpha(file->peek()) > 0) // next char is a letter or part of a word
            {
                *file >> command;

                // grab the group, if it is ok, then add it
                if(command == "group")
                {
                    ignore();   // clear chars

                    cout << current_line << endl;
                    Sprite_Group *g = grabGroup();
                    if(g != NULL)
                    {
                        dest->add(g);
                        if(debug)
                        {
                            cout << "Sprite_File: added group \"" << g->getName() << "\"" << endl;
                            cout << "------------------------------------------------------" << endl;
                            g->print();
                            cout << endl;
                        }
                    }
                }
            }
        }
    }

    cout << "Sprite_File: done" << endl;
    file->close();
}

Sprite_Group *Sprite_File::grabGroup()
{
    char c;
    string command;
    Sprite_Group *sprite_group = NULL;
    bool dirty = false;
    int sprite_num = 1;

    while(!file->eof())
    {
        ignore();

        // name of group?
        if(sprite_group == NULL && isalpha(file->peek()) > 0)
        {
            string name;
            *file >> name;
            cout << name;

            if(name != "")
                sprite_group = new Sprite_Group(name);
            else
                if(debug)
                    cout << "Sprite_File: failed to read group name \"" << name << "\"on line " << current_line << endl;
        }

        ignore();

        if(file->peek() == '!') // a control word?
        {
            // havent read name yet
            if(sprite_group == NULL)
            {
                char *name = NULL;
                sprintf(name, "g%d", sprite_num);

                cout << "Sprite_File: no name for group at line " << current_line << ", calling it \"" << name << "\"" << endl;

                sprite_group = new Sprite_Group((string) name);
            }
            // somehow we skipped the "endgroup"
            if(file->peek() == 'g')
            {
                dirty = true;
                cout << "Sprite_File: found new group at line " << current_line << ", ignoring prev group" << endl;
                break;
            }

            c = file->get(); // eat '!'

            // next char is a letter or part of a word
            if(isalpha(file->peek()) > 0)
            {
                *file >> command;

                // end of group
                if(command == "endgroup")
                    break;

                // grab the sprite, if it is ok, then add it
                if(command == "sprite" && sprite_group != NULL)
                {
                    ignore();   // clear chars

                    Sprite *s = grabSprite();
                    if(s != NULL)
                    {
                        sprite_group->add(s);
                        if(debug)
                        {
                            cout << "Sprite_File: added sprite \"" << s->getName() << "\""<< endl;
                            //s->print();
                        }
                    }
                }
            }
        }
    }

    // bad group
    if(dirty || sprite_group == NULL)
        return NULL;

    return sprite_group;
}

Sprite *Sprite_File::grabSprite()
{
    char c;
    string command;
    Sprite *sprite = NULL;
    bool *list = NULL;
    int list_len = 0;
    bool dirty = false;

    while(!file->eof())
    {
        // name, width, height, num frames of sprite?
        if(sprite == NULL && isalpha(file->peek()) > 0)
        {
            string name;
            int w, h, n_f;
            *file >> name >> w >> h >> n_f;
            sprite = new Sprite(name, w, h, n_f);

            if(name != " " || w > 1 || h > 1 || n_f > 1)
            {
                sprite = new Sprite(name, w, h, n_f);
                list = new bool[w*h*n_f];
                list_len = w*h*n_f;
            }
            else
            {
                dirty = true;
                if(debug)
                    cout << "Sprite_File: bad sprite info on line " << current_line << endl
                         << "   name = " << name << " width = " << w << " height = " << h << " num frames = " << n_f << endl;
            }
        }

        ignore();

        if(file->peek() == '!') // a control word?
        {
            // somehow we skipped the "endsprite"
            if(file->peek() == 's')
            {
                dirty = true;
                cout << "Sprite_File: found new sprite at line " << current_line << ", ignoring prev sprite" << endl;
                break;
            }

            // somehow we skipped the "endsprite" AND the "endgroup"
            if(file->peek() == 'g')
            {
                dirty = true;
                break;
            }

            c = file->get(); // eat '!'

            // next char is a letter or part of a word
            if(isalpha(file->peek()) > 0)
            {
                *file >> command;

                // end of group
                if(command == "endsprite")
                    break;
            }
        }

        ignore();

        // sprite itself, graphical chars but not alphanum
        if(isgraph(file->peek()) > 0 && isalnum(file->peek()) == 0)
        {
            int index = 0;
            while(isalpha(file->peek()) == 0) // go until alphanum
            {
                c = file->get();
                if(c == '*' || c == '-')
                {
                    // dont add to bool list if too many
                    if(index < list_len)
                    {
                        switch(c)
                        {
                            case '*':
                                list[index] = true;
                                break;
                            case '-':
                                list[index] = false;
                                break;
                        }
                    }
                    index++;
                }
                ignore();   // clear chars
            }
            // too few pixels?
            if(index < list_len)
            {
                cout << "Sprite_Field: not enough pixels in sprite \"" << sprite->getName() <<" \" on line " << current_line << ", ignoring this sprite" << endl;
                dirty = true;
            }
            else if(index > list_len)   // too many pixels?
            {
                cout << "Sprite_Field: too many pixels in sprite \"" << sprite->getName() << "\" on line " << current_line << ", ignoring any extra" << endl;
            }

            sprite->setSprite(list);
        }

        ignore();

        // sprite options, sprite info is loaded and not a control char
        if(sprite != NULL && isalpha(file->peek()) > 0)
        {
                *file >> command;

                if(command == "color")
                {
                    int r, g, b, a;
                    *file >> r >> g >> b >> a;

                    sprite->setColor(r, g, b, a);
                }
                else if(command == "size")
                {
                    int w, h;
                    *file >> w >> h;

                    if(w > 0 && h > 0)
                        sprite->setSize(w, h);
                    else
                        if(debug)
                            cout << "Sprite_File: bad sprite size on line " << current_line << endl
                                 << " width = " << w << " height = " << h << endl;
                }
                else if(command == "pos")
                 {
                    int x, y;
                    *file >> x >> y;

                    if(x >= 0 && y >= 0)
                        sprite->setPos(x, y);
                    else
                        if(debug)
                            cout << "Sprite_File: bad sprite pos on line " << current_line << endl
                                 << " width = " << x << " height = " << y << endl;
                }
                else if(command == "animate")
                {
                    bool run;
                    *file >> run;

                    sprite->animate(run);
                }
                else if(command == "visible")
                {
                    bool show;
                    *file >> show;

                    sprite->visible(show);
                }
                else
                    cout << "Sprite_File: unrecognized command \"" << command << "\" on line " << current_line << endl;
        }
        ignore();   // clear chars
    }

    // bad group
    if(dirty || sprite == NULL)
        return NULL;

    return sprite;
}

// ignore comments and whitespace, handles endlines
void Sprite_File::ignore()
{
    char c;
    bool commented = false;

    // ignore until we reach a noncommented printable char
    while(!file->eof())
    {
        // graphical char
        if(isgraph(file->peek()) > 0)
        {
            // a comment char
            if(file->peek() == '#')
            {
                if(!commented)
                    commented = true;
            }
            // an uncommented char, not '#'
            else
            {
                if(!commented)
                    break;
            }

        }
        else if(file->peek() == '\n')
        {
            current_line++;
            if(commented)
                commented = false;
        }

        c = file->get();
        //cout << c;
    }
}

