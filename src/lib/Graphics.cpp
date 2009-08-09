#include "Graphics.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "SdlContext.h"

#include "Log.h"

bool Graphics::isTypeUnknown()
{
    bool ret = SdlContext::getType() == SdlContext::UNKOWN;
    return ret;
}

bool Graphics::isTypeSDL()
{
    bool ret = SdlContext::getType() == SdlContext::SOFTWARE || SdlContext::getType() == SdlContext::HARDWARE;
    return ret;
}

bool Graphics::isTypeOGL()
{
    bool ret = SdlContext::getType() == SdlContext::OPENGL;
    return ret;
}

int Graphics::getWidth()
{
    return SdlContext::getWidth();
}

int Graphics::getHeight()
{
    return SdlContext::getHeight();
}

SDL_Surface* Graphics::getSDLScreen()
{
    return SdlContext::getScreen();
}

void Graphics::enableOGLAlphaBlending()
{
    if(!isTypeOGL())
        return;

    // blending
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::disableOGLBlending()
{
    if(!isTypeOGL())
        return;

    glDisable(GL_BLEND);
}

void Graphics::enableOGLRaster2D()
{
    if(!isTypeOGL())
        return;

    int vPort[4];

    glGetIntegerv(GL_VIEWPORT, vPort);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, vPort[2], vPort[3], 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void Graphics::disableOGLRaster2D()
{
    if(!isTypeOGL())
        return;

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
/*
bool Graphics::initGLEW()
{
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        LOG_ERROR << "Graphics: Could not initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return false;
    }

    LOG_DEBUG << "Graphics: Using GLEW Version: " <<  glewGetString(GLEW_VERSION) << std::endl;
    return true;
}
*/
std::string Graphics::getErrorString(int error)
{
    std::string errorString;

    if(!isTypeOGL())
    {
        errorString = (char*) gluErrorString(error);
        return errorString;
    }

    errorString = SDL_GetError();
    return errorString;
}

void Graphics::drawViewPort()
{
/*
    enable2D();

    float w = equt::equtGet(equt::EQUT_STATE_WIN_WIDTH);
    float h = equt::equtGet(equt::EQUT_STATE_WIN_HEIGHT);
    glColor3f(1.0, 1.0, 1.0);

    // viewport outline
    glBegin(GL_LINE_LOOP);
        glVertex2i(0, 0);
        glVertex2i(w, 0);
        glVertex2i(w, h);
        glVertex2i(0, h);
    glEnd();

    // center cross hairs
    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(w, h);
        glVertex2i(0, h);
        glVertex2i(w, 0);
    glEnd();

    disable2D();
*/
}
