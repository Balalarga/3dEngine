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

    while(game->IsRunning())
    {
        game->Tick();
    }

    delete game;
    return 0;
}
