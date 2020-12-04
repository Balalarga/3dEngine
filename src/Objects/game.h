#ifndef GAME_H
#define GAME_H

#include "glIncludes.h"
#include "Objects/camera.h"
#include <vector>

class Game
{
public:
    Game();
    virtual ~Game();
    void Init();
    bool IsRunning();
    void HandleEvents();
    void Tick();
    void Draw();
    void Update();
    void SwapBuffer();
    void Destroy();
    void SetClearColor(Color c);

    virtual void onTick(){}
    virtual void beforeUpdate(){}
    virtual void afterUpdate(){}
    virtual void beforeDestroy(){}

protected:
    SDL_Window *window;
    SDL_GLContext glcontext;
    Color clearColor{0.f, 0.f, 0.f};
    int width = 640;
    int height = 480;
    bool running = true;
    struct FpsData{
        float fps = 60.f;
        float timeElapsed = 0.f;
    } fpsData;
    GameObject* camera;
};

#endif // GAME_H
