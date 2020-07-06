#include <iostream>
#include <SDL2/SDL.h>

using namespace std;



int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

    bool running = true;

    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
