#include "SdlContext.h"

// statics
SDL_Surface* SdlContext::_screen = NULL;
SdlContext::Type SdlContext::_type = SdlContext::UNKOWN;
int SdlContext::_iWidth = 0;
int SdlContext::_iHeight = 0;
int SdlContext::_iDepth = 0;

SdlContext::SdlContext(int w, int h, int depth, Type type)
{
    _iWidth = w;
    _iHeight = h;
    _iDepth = depth;
    _ui32VideoFlags = 0;
    _type = type;
    _mode = WINDOW;

    LOG_DEBUG << "w " << _iWidth << " h " << _iHeight << std::endl;
}

SdlContext::~SdlContext()
{
    //dtor
}

bool SdlContext::init()
{
    // initialize SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR << "Unable to init SDL Video: %s" << SDL_GetError() << std::endl;
        return false;
    }

    LOG << "Setting: ";
    switch(_type)
    {
        case SOFTWARE:
            LOG << "SDL_SWSURFACE";
            break;
        case HARDWARE:
            LOG << "SDL_HWSURFACE";
            break;
        case OPENGL:
            LOG << "SDL_OPENGL";
            break;
    }
    LOG << " " << _iWidth << "x" << _iHeight << " @ " << _iDepth << " bit ";
    switch(_mode)
    {
        case WINDOW:
            LOG << "window";
            break;
        case FULLSCREEN:
            LOG << "fullscreen";
            break;
    }
    LOG << std::endl;

    // init window
    bool bRet;
    if(_type == OPENGL)
        bRet = initOpenGL();
    else
        bRet = initSDL();

    if(!bRet)
    {
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    return true;
}

bool SdlContext::createWindow(std::string title)
{
    // create a new window
    _screen = SDL_SetVideoMode(_iWidth, _iHeight, _iDepth, _ui32VideoFlags);
    if(!_screen)
    {
        LOG_ERROR << "Unable to set video: " << SDL_GetError() << std::endl;
        return false;
    }

    _sTitle = title;
    SDL_WM_SetCaption(_sTitle.c_str(), NULL);

    return true;
}

bool SdlContext::initSDL()
{
    // set proper flags for mode
    _ui32VideoFlags = _type|SDL_DOUBLEBUF|_mode;

    return true;
}

bool SdlContext::initOpenGL()
{
    // set proper flags for mode
    _ui32VideoFlags = _type|_mode;

    // use openGL doublerbuffer
    if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
    {
        LOG_ERROR << "Unable to init GL doublebuffer:" << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
