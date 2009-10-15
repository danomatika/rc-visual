#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Osc_Server.h"
#include "ArpNow.h"
#include "Vel.h"
#include "RunMan.h"

int which = 2;

#define FPS 30
#define ESCAPE 27

GLint winx = 800;
GLint winy = 600;
string port = "5555";

lo_address osc_send;    // osc send address to pd
Osc_Server server;
ArpNow Arp;
Vel V;
RunMan Run;

bool fullscreen = false;
bool game_mode = true;
bool debug = false;

/* Osc Server callbacks */
////////////////////////////////////
void setup_server(string port);

void server_error_callback(int num, const char *msg, const char *path);

int generic_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int visual_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int quit_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

int track_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data);

/* glut callbacks */
///////////////////////////////////

// initScene: initialize gl Scene
void initScene();

// renderScene: draws to gl
void renderScene(void);

// changeSize: recompute perspective
void changeSize(int w, int h);

// keyboard() gets called when a key is pressed
void keyboard(unsigned char key, int x, int y);

// special keys
void specialkeys(int key, int x, int y);

// idle() get called periodicaly
void idle();

/////////////////////////////////////

// main : initialize Glut window and create!
int main(int argc, char **argv)
{
    if(argc > 1)
    {
        if(argc >= 3 && (string) argv[2] == "debug")
            debug = true;

        if((string) argv[1] == "full")
            game_mode = true;
        else if((string) argv[1] == "window")
            game_mode = false;
        else if((string) argv[1] == "debug")
            debug = true;
        else
            cout << "Usage: visual [opt] " << endl << endl
                 << "display options: full or window" << endl;
    }

    // start osc server
    cout << "Start OSC server, listen on port " << port << endl;
    setup_server(port);
    server.startListening();
    Arp.setup(800, 600);
    V.setup(800, 600);
    Run.setup(800, 600);

    cout << "Start Glut" << endl;
	glutInit(&argc, argv);							// start glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// set gl display mode

    if(!game_mode)
    {
        glutInitWindowPosition(300, 0);					// set window pos
        glutInitWindowSize(winx, winy);					// set window size!
        glutCreateWindow("Visual");					// start window!
        if(fullscreen) glutFullScreen();
    }
    else
    {
        // 640x480, 16bit pixel depth, 60Hz refresh rate
        glutGameModeString("800x600:16@15");

        // start fullscreen game mode
        glutEnterGameMode();
    }

	initScene();

	glutDisplayFunc(renderScene);					// display scene
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(keyboard);                     // connect keyboard functi	glutSpecialFunc(specialkeys);
	glutMainLoop();									// loop display!

	return 0;
}

// initScene: initialize gl Scene
void initScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
}

/* idle() get called periodicaly */
void idle()
{
	glutPostRedisplay(); /* redraw the screen */
}

/* keyboard() gets called when a key is pressed */
void keyboard(unsigned char key, int x, int y)
{
      switch(key)
      {
        case ESCAPE:
            server.stopListening();
            exit(0);
            break;

        default:
            lo_send(osc_send, "/pd/devices/keys", "c", key);
      }
    //  cout << (int) key << endl;
}

void specialkeys(int key, int x, int y)
{
    switch(key)
      {
        case GLUT_KEY_RIGHT:
            cout << 'r' << endl;
            lo_send(osc_send, "/pd/devices/keys", "c", 'r');
            break;

        default:
        int mod = glutGetModifiers();
            if(mod == GLUT_ACTIVE_SHIFT)
                lo_send(osc_send, "/pd/devices/keys", "c", key);
            break;
      }
    //   cout << (int) key << endl;
}

// changeSize: recompute perspective
void changeSize(int w, int h)
{
  	glViewport((w-winx)/2,(h-winy)/2, -1, -1);
  	glMatrixMode(GL_PROJECTION);
  	gluOrtho2D(0, w, 0, h);

  	winx = w;
  	winy = h;
}

// renderScene: draws to gl
void renderScene(void)
{
  	glClear(GL_COLOR_BUFFER_BIT);
/*
    switch(which)
    {
        case 0: Arp.draw();
                break;

        case 1: V.draw();
                break;

        case 2: Run.draw();
    }
*/
  	//glutSwapBuffers();

	//usleep(1000000/FPS);
	//glFlush();
	glutSwapBuffers();
}

void setup_server(string port)
{
    server.setup(port.c_str(), server_error_callback);

    // add address handling callbacks
    if(debug) server.addRecvMethod(NULL, NULL, generic_handler);
    server.addRecvMethod("/visual", "sf", visual_handler);
    server.addRecvMethod("/visual/quit", "s", quit_handler);
    server.addRecvMethod("/visual/track", "i", track_handler);

    osc_send = lo_address_new("127.0.0.1", "8880");
}

void server_error_callback(int num, const char *msg, const char *path)
{
    cout << "visual: server error " << endl;
}

int generic_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    cout << "Message recieved: " << path;

    for (int i = 0; i < argc; i++)
    {
        cout << " ";
        //printf("arg %d '%c' ", i, types[i]);
        lo_arg_pp((lo_type) types[i], argv[i]);
    }
    cout << endl;

    return 1;
}

/*  visual  */
int visual_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    switch(which)
    {
        case 0: Arp.update((string) &argv[0]->s, argv[1]->f);
                break;

        case 1: V.update((string) &argv[0]->s, argv[1]->f);
                break;

        case 2: Run.update((string) &argv[0]->s, argv[1]->f);
                break;
    }

    return 1;
}

/*  quit  */
int quit_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    if((string) &argv[0]->s == "quit")
        server.stopListening();
        exit(0);

    return 1;
}

/*  track  */
int track_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    which = argv[0]->i;

    return 1;
}
