#include "Visual.h"

Visual::Visual()
{
    //ctor
}

Visual::~Visual()
{
    //dtor
}

void Visual::setup()
{
    _background.set(255, 0, 255);
}

void Visual::update()
{
    pressure.update();
}

void Visual::draw()
{

    pressure.draw();
}

void Visual::cleanup()
{
}
