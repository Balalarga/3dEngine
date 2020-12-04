#include <iostream>
#include "game.h"
using namespace std;

int main(int argc, char *argv[]){

    Game::Instance().Init();
    Game::Instance().SetClearColor({0.2f, 0.2f, 0.2f});

    while(Game::Instance().IsRunning()){
        Game::Instance().Tick();
    }

    Game::Instance().Destroy();
    return 0;
}
