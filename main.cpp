#include <iostream>
#include <SDL2/SDL.h>

using namespace std;



int main(int argc, char** argv)
{
    cout<<"1\n";
    SDL_Init(SDL_INIT_EVERYTHING);
    cout<<"2\n";
    SDL_Window* window = SDL_CreateWindow("", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    cout<<"3\n";
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    cout<<"4\n";
    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_RenderPresent(render);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
