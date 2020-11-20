#include <iostream>
#include "game.h"
using namespace std;

int main(int argc, char *argv[]){

    Game::instance().init();


    while(Game::instance().isRunning()){

        Game::instance().handleEvents();

        Game::instance().draw();

        Game::instance().swapBuffer();

    }

    return 0;
}
