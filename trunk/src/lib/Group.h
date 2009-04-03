#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include "Common.h"
#include "Rectangle.h"

// a group of objects
class Group
{
    public:

        Group();

        virtual ~Group();

        void add(Rectangle* obj);

        Rectangle* getObject(std::string name);

        void draw();

        void update();

        bool loadXml(TiXmlElement* xmlPtr);

        std::string getName() {return _name;}

        void print(std::string indent="");

    protected:

        std::string _name;
        std::vector<Rectangle*> _objects;
};

#endif // GROUP_H
