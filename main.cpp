#include <iostream>
#include "sandboxgame.h"
using namespace std;

int main(int argc, char *argv[])
{
    GameConfig config;
    config.renderType = GameConfig::RenderType::OpenGL;
    config.title = "Sandbox game";
    config.windowSize = {1200, 800};


    SandboxGame* game;
    try
    {
        game = new SandboxGame(config);
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
