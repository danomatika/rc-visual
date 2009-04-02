#include "BitmapSprite.h"

BitmapSprite::BitmapSprite() : curFrame(0)
{
    //ctor
}

BitmapSprite::~BitmapSprite()
{
    //dtor
}

void BitmapSprite::draw()
{
    if(_frames.empty())
        return;
}
