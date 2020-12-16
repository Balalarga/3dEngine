#include <iostream>
#include "sandboxgame.h"
using namespace std;

int main(int argc, char *argv[])
{

    SandboxGame* game;
    try
    {
        game = new SandboxGame();
    }
    catch (const string& error)
    {
        cout<<error;
        return -1;
    }

    game->Run();

    delete game;
    return 0;
}
