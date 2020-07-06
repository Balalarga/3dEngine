#include "game.h"
#include <iostream>
using std::cout;

Game::Game():
    m_mainWindow(new Window("Game"))
{
}

bool Game::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout<<"SDL_Init error: "<<SDL_GetError();
        cout<<std::endl;
        return false;
    }
    return true;
}

void Game::run(){

}

Game::~Game()
{
    delete m_mainWindow;
    SDL_Quit();
}
