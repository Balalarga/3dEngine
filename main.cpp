#include <iostream>
#include "examplegame.h"
using namespace std;

int main(int argc, char *argv[]){

    TestGame game;
    game.Init();
    game.SetClearColor({0.2f, 0.2f, 0.2f});

    while(game.IsRunning()){
        game.Tick();
    }

    game.Destroy();
    return 0;
}
