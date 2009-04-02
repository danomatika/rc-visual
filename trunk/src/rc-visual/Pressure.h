#ifndef PRESSURE_H
#define PRESSURE_H

#include <vector>

#include "Common.h"
#include "Rectangle.h"

#define NUM_MOLECULES 5

class Pressure
{
    public:

        Pressure();

        virtual ~Pressure();

        void update();

        void draw();

    protected:

    private:

//        Color background;
        std::vector<Rectangle> molecules;
};

class Molecule : public Rectangle
{
    public:

        Molecule();

        virtual ~Molecule();

        void checkCollision(int x, int y, Molecule& mol)
        {
            /*
            const int dx = _iPosX - mol.getPosX();
            const int dy = _iPosY - mol.getPosY();
            const int dist = _iWidth + mol.getWidth();

            if(dx * dx + dy * dy < dist * dist)
            {
                // collision

            }
*/
        }
};



#endif // PRESSURE_H
