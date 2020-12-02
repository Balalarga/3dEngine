#ifndef GAME_H
#define GAME_H

#include "glIncludes.h"

#include "cubemesh.h"
#include "camera.h"
#include <vector>

class Game
{
public:
    static Game& Instance();
    void Init();
    bool IsRunning();
    void HandleEvents();
    void Tick();
    void Draw();
    void Update();
    void SwapBuffer();
    void Destroy();

private:
    Game();
    static Game* selfInstance;
    SDL_Window *window;
    SDL_GLContext glcontext;
    int width = 640;
    int height = 480;
    bool running = true;
    struct FpsData{
        float fps = 60.f;
        float timeElapsed = 0.f;
    } fpsData;
    Camera* camera;

};

#endif // GAME_H
