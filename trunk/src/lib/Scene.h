#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Common.h"

#include "Group.h"

class Scene
{
    public:

        Scene();

        virtual ~Scene();

        void add(Group* grp);

        void nextGroup();

        void prevGroup();

        void gotoGroup(int group);

        void gotoGroup(std::string group);

        void clear();

        void draw();

        void update();

        bool loadXml(TiXmlElement* xmlPtr);

        inline bool isEmpty()  {return _groups.empty();}
        inline Group* getGroup() {return _groups[_curGroup];}

    protected:

        std::vector<Group*> _groups;
        uint _curGroup;    /// current group
};

#endif // SCENE_H
