/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#include "Sprite.h"

bool Sprite::loadImage(std::string filename)
{
    // create a texture from an image and add it to the vector
    Texture tex;
    if(!tex.loadImage(filename))
    {
        LOG_ERROR << "Sprite::loadImage(): failed to load \"" << filename << "\"" << std::endl;
        return false;
    }

    _vTextures.push_back(tex);

    return true;
}

void Sprite::nextFrame()
{
    if(_vTextures.size() == 0)
        return;

    _curTex++;

    if(_curTex > _vTextures.size()-1)
    {
        _curTex = 0;
    }
}

void Sprite::prevFrame()
{
    if(_vTextures.size() == 0)
        return;

    if(_curTex == 0)
    {
        _curTex = _vTextures.size()-1;
        return;
    }

     _curTex--;
}

void Sprite::goToFrame(uint8_t frame)
{
    if(_vTextures.size() == 0)
        return;

    if(frame > -1 && frame < _vTextures.size())
    {
        _curTex = frame;
    }
}

void Sprite::draw()
{
    if(_vTextures.size() == 0)
        return;

    glColor4fv(_color.rgba);
    _vTextures[_curTex].draw(_pos.x, _pos.y, _w, _h);
}
