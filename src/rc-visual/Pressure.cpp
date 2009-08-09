#include "Pressure.h"

#include <cmath>

Pressure::Pressure()
{
    srand(time(NULL));
    for(int i = 0; i < NUM_MOLECULES; i++)
    {
        Rectangle r(rand()%(Graphics::getWidth()-50)+25,
                    rand()%(Graphics::getHeight()-50)+25,
                    50, 50);
        molecules.push_back(r);
        LOG << "Pressure: Molecule added: " << r << std::endl;
    }
}

Pressure::~Pressure()
{
    //dtor
}

void Pressure::update()
{

}

void Pressure::draw()
{

    for(int i = 0; i < NUM_MOLECULES; i++)
    {
        molecules[i].draw();
    }
}
