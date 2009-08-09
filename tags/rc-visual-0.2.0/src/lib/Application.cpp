#include "Application.h"

Application::Application() : _bRun(true), _fFrameRate(0), _ui32Ticks(0)
{
    _fFrameRateMs = 0; // no timing
}

Application::~Application()
{}

void Application::mainLoop()
{
    // program main loop
    while(_bRun)
    {
        update();   // call the user update function
        _events();  // handle events and do framerate idling
        _draw();  // render a frame

        // update ticks
        _ui32Ticks = SDL_GetTicks();
    }
}

void Application::setFrameRate(float frameRate)
{
    if(frameRate < 0)
        return;

    _fFrameRate = frameRate;

    // no delay?
    if(frameRate == 0)
    {
        _fFrameRateMs = 0;
        return;
    }

    _fFrameRateMs = 1000/_fFrameRate;   // delay = 1000 ms / fps
}

// ##### private functions #####

void Application::_draw()
{
    // clear background
    if(Graphics::isTypeOGL())
    {
        glClearColor(_background.R/255, _background.G/255, _background.B/255, _background.A/255);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        // clear screen
        SDL_FillRect(Graphics::getSDLScreen(), 0,
            SDL_MapRGB(Graphics::getSDLScreen()->format, _background.R, _background.G, _background.B));
    }

    // user render function
    draw();

    // swap buffers
    if(Graphics::isTypeOGL())
    {
        SDL_GL_SwapBuffers();
    }
    else
    {
        SDL_Flip(Graphics::getSDLScreen());
    }
}

void Application::_events()
{
    // do message processing while waiting for next frame
    while(SDL_GetTicks() - _ui32Ticks < _fFrameRateMs)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch(event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    _bRun = false;
                    break;

                // check for keypresses
                case SDL_KEYDOWN:
                {
                    switch(event.key.state)
                    {
                        case SDL_PRESSED:
                            switch(event.key.keysym.sym)
                            {
                                // exit if ESCAPE is pressed
                                case SDLK_ESCAPE:
                                    _bRun = true;
                                    break;

                                default:
                                    keyPressed(event.key.keysym.sym, event.key.keysym.mod);
                                    break;
                            }
                            break;

                        case SDL_RELEASED:
                            keyReleased(event.key.keysym.sym, event.key.keysym.mod);
                            break;
                    }
                }

                // check for mouse movement
                case SDL_MOUSEMOTION:
                {
                    mouseMotion(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                {
                    switch(event.button.state)
                    {
                        case SDL_PRESSED:
                            mousePressed(event.button.button, event.button.x, event.button.y);
                            break;

                        case SDL_RELEASED:
                            mouseReleased(event.button.button, event.button.x, event.button.y);
                            break;
                    }
                    break;
                }

            } // end switch
        } // end of message processing

        usleep(20000);  // 20 msec for the scheduler
    }
}
