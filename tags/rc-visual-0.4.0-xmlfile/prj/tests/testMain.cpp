#include <iostream>
#include <unistd.h>
#include <string>

#include "Sprite_File.h"
#include "Sprite_Collection.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "starting testMain" << endl;

    Sprite_File sfile;
    sfile.loadXml("sprite_test.xml", NULL);

    cout << "Exited cleanly" << endl;
    return 0;
}
