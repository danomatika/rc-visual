

#include <iostream>
#include <cstdlib>

#include <SDL/SDL.h>
#include <SDL_gfxPrimitives.h>
#include <lo/lo.h>

#include <glib.h> // for GOptions commandline parsing
// http://www.eikke.com/articles/goption-parsing.html

#include "Sprite.h"
#include "Sprite_Group.h"
#include "Sprite_Collection.h"
#include "Sprite_File.h"
#include "Osc_Server.h"

Osc_Server server;
lo_address osc_send;
string send_addr = "127.0.0.1";
string send_port = "8880";
string recv_addr = "127.0.0.1";
string recv_port = "9990";
string osc_key_addr = "/pd/devices/keyboard";
string osc_pd_addr = "/pd/visual";

SDL_Surface *screen;

Sprite_Collection sprite_collection;
Sprite_File file;

Uint32 frame_rate = 200;   // 5 fps = 1000 ms / 5
bool bDone = false;
gboolean debug = false;
gboolean iNotify = -1;

// Osc Server callbacks
////////////////////////////////////
void setup_server(string port);

void server_error_callback(int num, const char *msg, const char *path);

int generic_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int file_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int quit_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int group_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int framerate_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);



int size_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int pos_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int color_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int frame_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int hide_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int animate_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);
/*
#include "Common.h"
#include "SdlContext.h"
#include "Visual.h"
*/
using namespace std;

int main(int argc, char** argv)
{
/*
    // initialize SDL context
    SdlContext sdl(640, 480, 16, SdlContext::HARDWARE);
    //sdl.setFullscreen();
    sdl.init();

    // open sdl window
    sdl.createWindow("rc-visual test");

     // init app
    Visual visualApp;
    visualApp.setFrameRate(30);
    visualApp.setup();

    // main app loop
    visualApp.mainLoop();

    // cleanup after exit from loop
    visualApp.cleanup();

    // all is well ;)
    LOG << "Exited cleanly" << endl;

    return 0;
}
*/
    // args to grab
    gchar *mode         = NULL;
    gchar *filename     = NULL;
    gboolean loadtest   = false;
    gchar *s_addr       = NULL;
    gchar *s_port       = NULL;
    gchar *r_addr       = NULL;
    gchar *r_port       = NULL;

    // which commandline options?
    GOptionEntry options[] = {
        // long, short. flags(usually 0), arg, arg_data, description (short), arg_description (long)
        { "mode", 'm', 0, G_OPTION_ARG_STRING, &mode, "windowed or fullscreen mode", "'window' or 'fullscreen'" },
        { "file", 'f', 0, G_OPTION_ARG_STRING, &filename, "file to load" },
        { "test", 't', 0, G_OPTION_ARG_NONE, &loadtest, "test load the file and exit", "'true' or 'false'" },
        { "address", 'a', 0, G_OPTION_ARG_STRING, &s_addr, "ip addr to send osc to", "'127.0.0.1', '192.0.0.101', etc" },
        { "port", 'p', 0, G_OPTION_ARG_STRING, &s_port, "port to send osc to", "'4440', '2388', etc" },
        { "listen", 'l', 0, G_OPTION_ARG_STRING, &r_port, "port to recieve osc on", "'4440', '2388', etc" },
        { "notify", 'n', 0, G_OPTION_ARG_INT, &iNotify, "tell pd to open a connection", "connection #" },
        { "receive", 'r', 0, G_OPTION_ARG_STRING, &r_addr, "ip addr to recv osc from (def: 127.0.0.1)", "'127.0.0.1', '192.0.0.101', etc" },
        { "debug", 'd', 0, G_OPTION_ARG_NONE, &debug, "print debug messages", "'true' or 'false'" },
        { NULL }
    };

    // create context
    GOptionContext *ctx;
    ctx = g_option_context_new("simple visual sprite engine controlled over OSC");
    g_option_context_add_main_entries(ctx, options, "visual");
    g_option_context_parse(ctx, &argc, &argv, NULL);

    // no args, set defaults
    if(mode == NULL)
        mode = (gchar*) "window";

    // get values
    if(s_addr != NULL)  send_addr = (string) s_addr;
    if(s_port != NULL)  send_port = (string) s_port;
    if(r_addr != NULL)  recv_addr = (string) r_addr;
    if(r_port != NULL)  recv_port = (string) r_port;

    // load the file and print contents, do not start graphics
    if(loadtest)
    {
        debug = true;
        file.printDebug(true);
        // read file
        if(filename != NULL)
            file.loadXml((string) filename, &sprite_collection);
        return 0;
    }

    // read file
    if(filename != NULL)
    {
        if(!file.loadXml((string) filename, &sprite_collection))
        {
            cout << "Could not load file due to errors" << endl;
            return 0;
        }
        Sprite_Group *g = sprite_collection.getGroupCurrent();
        cout << "Current group = " << g->getName() << endl;
    }

    // print file contents as if loads
    if(debug)   file.printDebug(true);

    // check values
    if((string) mode != "window" && (string) mode != "fullscreen")
    {
        cout << g_option_context_get_help(ctx, TRUE, NULL);
        return 0;
    }

    // initialize SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Unable to init SDL: %s" << SDL_GetError() << endl;
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // start osc server
    cout << "Starting OSC server, listening on port " << recv_port << endl;
    setup_server(recv_port.c_str());
    server.startListening();

    // hide the cursor
    SDL_ShowCursor(SDL_DISABLE);

    // create a new window
    cout << "Setting 640x480 @ 8 bit " << mode << endl;
    Uint32 video_flags = 0;
    if((string) mode == "window")
        video_flags = SDL_HWSURFACE|SDL_DOUBLEBUF;
    else if((string) mode == "fullscreen")
        video_flags = SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN;

    screen = SDL_SetVideoMode(640, 480, 8, video_flags);
    if(!screen)
    {
        cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
        return 1;
    }

    // tell pd to open a connection
    if(iNotify >= 0)
    {
        cout << "Notifying pd to open a connection" << endl;
        lo_send(osc_send, osc_pd_addr.c_str(), "sfs", "connect", (float) iNotify, recv_addr.c_str());
    }

    Uint32 ticks = 0;
    // program main loop
    while(!bDone)
    {
        // do message processing while waiting for next frame
        while(SDL_GetTicks() - ticks < frame_rate)
        {
            // message processing loop
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                // check for messages
                switch (event.type)
                {
                    // exit if the window is closed
                    case SDL_QUIT:
                        bDone = true;
                        break;

                    // check for keypresses
                    case SDL_KEYDOWN:
                    {
                        switch(event.key.keysym.sym)
                        {
                            // exit if ESCAPE is pressed
                            case SDLK_ESCAPE:
                                bDone = true;
                                break;
                            // send keys on osc
                            default:
                                lo_send(osc_send, osc_key_addr.c_str(), "c", event.key.keysym.sym);
                                break;
                        }
                    }

                    // check for mouse movement
                    case SDL_MOUSEMOTION:
                    {
                        //lo_send(osc_send, osc_addr.c_str(), "ii", event.motion.x, event.motion.y);
                        //cout << osc_addr + "/ka" << "mouse moved: " << event.motion.x << " " << event.motion.y << endl;
                    }

                    case SDL_MOUSEBUTTONDOWN:
                    {
                        //lo_send(osc_send, osc_addr.c_str(), "ii",
                        string button;
                        switch(event.button.button)
                        {
                            case SDL_BUTTON_LEFT:
                                button = "MOUSE_LEFT";
                                break;
                            case SDL_BUTTON_MIDDLE:
                                button = "MOUSE_MIDDLE";
                                break;
                            case SDL_BUTTON_RIGHT:
                                button = "MOUSE_RIGHT";
                                break;
                        }
                        //cout << "mouse button: " << button.c_str() << endl;

                    }

                } // end switch
            } // end of message processing

            usleep(20000);  // 20 msec
        }

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        sprite_collection.render(screen);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        // DRAWING DONE

        // update ticks
        ticks = SDL_GetTicks();
    } // end main loop

    server.stopListening();

    // tell pd to close the connection
    if(iNotify >= 0)
    {
        cout << "Notifying pd to close the connection" << endl;
        lo_send(osc_send, osc_pd_addr.c_str(), "sf", "disconnect", (float) iNotify);
    }

    // all is well ;)
    cout << "Exited cleanly" << endl;
    return 0;
}

void setup_server(string port)
{
    server.setup(port.c_str(), server_error_callback);

    // add address handling callbacks
    if(debug)
        server.addRecvMethod(NULL, NULL, generic_handler);
    server.addRecvMethod("/visual/file", "s", file_handler);
    server.addRecvMethod("/visual/quit", NULL, quit_handler);
    server.addRecvMethod("/visual/group", "s", group_handler);
    server.addRecvMethod("/visual/framerate", "i", framerate_handler);

    // sprite manipulation
    server.addRecvMethod("/visual/size", "sii", size_handler); // name, width, height
    server.addRecvMethod("/visual/pos", "sii", pos_handler); // name, x, y
    server.addRecvMethod("/visual/color", "siiii", color_handler); // name, r, g, b, a
    server.addRecvMethod("/visual/frame", "ss", frame_handler); // name, "next" or "prev" frame
    server.addRecvMethod("/visual/visible", "si", hide_handler); // name, boolean to display
    server.addRecvMethod("/visual/animate", "si", animate_handler); // name, boolean to animate


    osc_send = lo_address_new(send_addr.c_str(), send_port.c_str());
    cout << "Sending OSC to " << send_addr << " at port " << send_port << endl;
}

void server_error_callback(int num, const char *msg, const char *path)
{
    cout << "visual: server error " << endl;
}

int generic_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    cout << "Message received: " << path;

    for (int i = 0; i < argc; i++)
    {
        cout << " ";
        //printf("arg %d '%c' ", i, types[i]);
        lo_arg_pp((lo_type) types[i], argv[i]);
    }
    cout << endl;

    return 1;
}

//  load file
int file_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    //file.loadXML(&argv[0]->s, &sprite_collection);

    return 1;
}

//  quit
int quit_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    bDone = true;

    return 1;
}

//  group
int group_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{

    if((string) &argv[0]->s == "next")
        sprite_collection.nextGroup();
    if((string) &argv[0]->s == "prev")
        sprite_collection.prevGroup();
    else
        sprite_collection.gotoGroup((string) &argv[0]->s);

    Sprite_Group *g = sprite_collection.getGroupCurrent();
    cout << "Change Group: " << &argv[0]->s << ", current group = " << g->getName() << endl;
    g->print();

    return 1;
}

int framerate_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    if(argv[0]->i == 0) // reset to 5
        frame_rate = 200;
    else if(argv[0]->i < 0 || argv[0]->i > 60)   // limit range to 1 - 60
        exit(0);
    else    // within rage
        frame_rate = 1000/argv[0]->i;   // delay = 1000 ms / fps

    return 1;
}


int size_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    Sprite *s;
    if((s = sprite_collection.getSprite((string) &argv[0]->s)) != NULL)
            s->setSize(argv[1]->i, argv[2]->i);

    return 1;
}

int pos_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    Sprite *s;
    if((s = sprite_collection.getSprite((string) &argv[0]->s)) != NULL)
        s->setPos(argv[1]->i, argv[2]->i);

    return 1;
}

int color_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    Sprite *s;
    if((s = sprite_collection.getSprite((string) &argv[0]->s)) != NULL)
        s->setColor((uint8_t) argv[1]->i, (uint8_t) argv[2]->i, (uint8_t) argv[3]->i, (uint8_t) argv[4]->i);

    return 1;
}

int frame_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    Sprite *s;
    if((s = sprite_collection.getSprite((string) &argv[0]->s)) != NULL)
    {
        if((string) &argv[1]->s == "next")
            s->nextFrame();
        else if((string) &argv[1]->s == "prev")
            s->prevFrame();
    }

    return 1;
}

int hide_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    Sprite *s;
    if((s = sprite_collection.getSprite((string) &argv[0]->s)) != NULL)
        s->visible(argv[1]->i);

    return 1;
}

int animate_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    Sprite *s;
    if((s = sprite_collection.getSprite((string) &argv[0]->s)) != NULL)
        s->animate(argv[1]->i);

    return 1;
}


