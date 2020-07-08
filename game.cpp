#include "game.h"
#include <iostream>
using std::cout;

Game::Game(){
}

bool Game::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout<<"SDL_Init error: "<<SDL_GetError();
        cout<<std::endl;
        return false;
    }
    m_screen = new Window("Game");
    return true;
}

void Game::start(){
    while(m_screen->isOpen()){
        m_screen->clear();
        checkEvents();

        m_screen->swap();
    }
}

void Game::checkEvents(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT)
            m_screen->close();
    }
}

Game::~Game(){
    delete m_screen;
    SDL_Quit();
}
