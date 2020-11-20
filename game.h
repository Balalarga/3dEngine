#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h> // Библиотека SDL 2

#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU

#include "cubemesh.h"
#include <vector>
using std::vector;

class Game
{
public:
    static Game& instance();
    void init();
    bool isRunning();
    void handleEvents();
    void draw();
    void swapBuffer();
    ~Game();

private:
    Game();
    static Game* selfInstance;
    SDL_Window *window; // задаем окно для SDL
    SDL_GLContext glcontext;
    int width = 640; // ширина окна
    int height = 480; // высота окна
    bool running = true;
    float xrf = 0, yrf = 0, zrf = 0; // углы поворота

    vector<CubeMesh> cubes;

};

#endif // GAME_H
