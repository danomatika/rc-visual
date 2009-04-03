#include "BitmapSprite.h"

BitmapSprite::BitmapSprite() : Rectangle(), _frame(0)
{
    // default starting pos
    pos.x = 0;
    pos.y = 0;

    // default physical size
    h = 64;
    w = 64;

    // animate by default
    _bAdvanceFrames = false;

    // show by default
    _bIsVisible = true;
}

BitmapSprite::~BitmapSprite()
{
    // delete all frames to cleanup
    for(std::vector<Frame*>::iterator i = _sprite.begin(); i != _sprite.end(); ++i)
    {
        delete (*i);
    }
}

void BitmapSprite::draw()
{
    if(_sprite.empty() || !_bIsVisible) // do nothing if hidden
        return;

    int px = pos.x, py = pos.y; // upper right corner phys pos of virtual pixel

    // loop through pixels in the frame
    for(int y = 0; y < _spriteH; y++)
    {
        for(int x = 0; x < _spriteW; x++)
        {
            // render virtual pixel
            if(_sprite[_frame]->bitmap[x + y*_spriteW] == true)
                dwf::Graphics::drawRectFilled(px, py, _pixelW, _pixelH, &color, dwf::Graphics::CORNER);
            px += _pixelW;
        }
        px = _pixelW;
        py += _pixelH;
    }

    if(_bAdvanceFrames)  // go to next frame?
    {
        _frame ++;
        if(_frame >= _sprite.size())
            _frame = 0;
    }
}

void BitmapSprite::nextFrame()
{
    _frame++;
    if(_frame >= _sprite.size())
        _frame = 0;
}

void BitmapSprite::prevFrame()
{
    _frame--;
    if(_frame < 0)
        _frame = _sprite.size()-1;
}

void BitmapSprite::gotoFrame(uint frameIndex)
{
    if(frameIndex >= 0 && frameIndex > _sprite.size())
    {
        _frame = frameIndex;
        return;
    }

    LOG_WARN << "BitmapSprite \"" << _name << "\": invalid frame index: \"" << frameIndex << "\"" << std::endl;
}

void BitmapSprite::setSize(int physWidth, int physHeight)
{
    w = physWidth;
    h = physHeight;

    // recalc physical dimensions of one virtual pixel
    _pixelH = w/_spriteH;
    _pixelW = h/_spriteW;
}

void BitmapSprite::print(std::string indent)
{
    Rectangle::print(indent);
    LOG << "BitmapSprite" << std::endl;
    LOG << indent << "frames: " << _sprite.size() << std::endl;

    // loop through frames
    for(uint f = 0; f < _sprite.size(); f++)
    {
        // loop through pixels in the frame
        for(int y = 0; y < _spriteH; y++)
        {
            LOG << indent;

            for(int x = 0; x < _spriteW; x++)
            {
                // render virtual pixel
                if(_sprite[f]->bitmap[x + y*_spriteW] == true)
                    LOG << '*';
                else
                    LOG << '-';
            }
            LOG << std::endl;
        }
        LOG << std::endl;
    }

    LOG << indent << "animate: " << _bAdvanceFrames << std::endl;
    LOG << indent << "visible: " << _bIsVisible << std::endl;
}

bool BitmapSprite::loadXml(TiXmlElement* xmlPtr)
{
    if(!xmlPtr || xmlPtr->ValueStr() != "bitmapsprite")
        return false;

    // check name
    if(!xmlPtr->Attribute("name"))
    {
        LOG << "Sprite_File: ignoring this sprite, name is either missing "
             << "or not the first attribute" << std::endl;
        return false;
    }

    const char* name = xmlPtr->Attribute("name");
    if(name != NULL)
    {
        _name = (std::string) name;
    }

    // loop through attributes
    int numFrames = 0;
    TiXmlAttribute* a = xmlPtr->FirstAttribute();
    a = a->Next();
    while(a != NULL)
    {
        if((std::string) a->Name() == "width")
        {
            _spriteW = a->IntValue();
        }

        else if((std::string) a->Name() == "height")
        {
            _spriteH = a->IntValue();
        }

        else if((std::string) a->Name() == "frames")
        {
            numFrames = a->IntValue();
        }

        else
        {
            LOG << "Sprite_File: ignoring unknown attribute \""
                 << a->Name() << "\" in sprite element" << std::endl;
        }

        a = a->Next();
    }
/*
    LOG << "   sprite: " << name
         << " w: " << _spriteW
         << " h: " << _spriteH
         << " f: " << numFrames
         << std::endl;
*/
    // loop through elements
    int index = 0;
    TiXmlElement* ptr = xmlPtr->FirstChildElement();
    while(ptr != NULL)
    {
        a = ptr->FirstAttribute();

        if(ptr->ValueStr() == "frame")
        {
//            LOG << "       frame "<< index << std::endl;
            if(!getFrame(ptr))
            {
//                LOG_ERROR << "Sprite_File: Failed to getFrame"<< std::endl;
                return false;
            }
            index++;
        }

        else if(ptr->ValueStr() == "color")
        {
            while(a != NULL)
            {
                if((std::string) a->Name() == "R")
                {
                    color.R = (unsigned char) a->IntValue();
                }

                else if((std::string) a->Name() == "G")
                {
                    color.G = (unsigned char) a->IntValue();
                }

                else if((std::string) a->Name() == "B")
                {
                    color.B = (unsigned char) a->IntValue();
                }

                else if((std::string) a->Name() == "A")
                {
                    color.A = (unsigned char) a->IntValue();
                }

                else
                {
                    LOG << "Sprite_File: ignoring unknown attribute \""
                         << a->Name() << "\" in color element" << std::endl;
                }

                a = a->Next();
            }
/*
            LOG << "       color"
                 << " R: " << color.R
                 << " G: " << color.G
                 << " B: " << color.B
                 << " A: " << color.A
                 << std::endl;
*/
        }

        else if(ptr->ValueStr() == "size")
        {
            while(a != NULL)
            {
                if((std::string) a->Name() == "width")
                {
                    w = a->IntValue();
                }

                else if((std::string) a->Name() == "height")
                {
                    h = a->IntValue();
                }

                else
                {
                    LOG << "Sprite_File: ignoring unknown attribute \""
                         << a->Name() << "\" in size element" << std::endl;
                }

                a = a->Next();
            }
/*
            LOG << "       size"
                 << " width: "  << w
                 << " height: " << h
                 << std::endl;
*/
            setSize(w, h);
        }

        else if(ptr->ValueStr() == "position")
        {
            while(a != NULL)
            {
                if((std::string) a->Name() == "x")
                {
                    pos.x = a->IntValue();
                }

                else if((std::string) a->Name() == "y")
                {
                    pos.y = a->IntValue();
                }

                else
                {
                    LOG << "Sprite_File: ignoring unknown attribute \""
                         << a->Name() << "\" in position element" << std::endl;
                }

                a = a->Next();
            }
/*
            LOG << "       position"
                 << " x: " << pos.x
                 << " y: " << pos.y
                 << std::endl;
*/
        }

        else if(ptr->ValueStr() == "animate")
        {
            bool yesno;
            if((std::string) a->Name() == "yesno")
            {
                yesno = a->IntValue();
            }

//            LOG << "       animate: " << yesno << std::endl;
            _bAdvanceFrames = (bool) yesno;
        }

        else if(ptr->ValueStr() == "visible")
        {
            bool yesno;
            if((std::string) a->Name() == "yesno")
            {
                yesno = a->IntValue();
            }

//            LOG << "       visible: " << yesno << std::endl;
            _bIsVisible = (bool) yesno;
        }

        ptr = ptr->NextSiblingElement();
    }

    return true;
}

bool BitmapSprite::getFrame(TiXmlElement* xmlPtr)
{
    if(!xmlPtr || xmlPtr->ValueStr() != "frame")
        return false;

    std::stringstream frameStream(xmlPtr->GetText());
    std::string line;
    Frame* frame = new Frame;
    int numPixels = 0;

    while(!frameStream.eof())
    {
        frameStream >> line;
//        LOG << "       " << line << std::endl;

        std::stringstream chars(line);

        char c;
        chars >> c;
        while(!chars.eof())
        {
            switch(c)
            {
                case '*':
                    frame->bitmap.push_back(true);
                    ++numPixels;
                    break;
                case '-':
                    frame->bitmap.push_back(false);
                    ++numPixels;
                    break;
            }
            chars >> c;
        }
    }

    if(numPixels != _spriteW * _spriteH)
    {
        LOG_WARN << "BitmapSprite:: Add frame failed, sprite of size " << numPixels
                 << " does not equal the virtual size of " << (int) (_spriteW * _spriteH)
                 << std::endl;
        return false;
    }

    _sprite.push_back(frame);

    return true;
}
