#ifndef GAME_H
#define GAME_H

#include "glIncludes.h"
#include "gameobject.h"
#include "Systems/RenderSystem/baserenderer.h"
#include <vector>

class Game
{
public:
    Game();
    bool IsRunning();
    void Tick();
    void UpdateCamera();

    virtual ~Game();
    virtual void OnTick()
    {

    }
    virtual void BeforeUpdate()
    {

    }
    virtual void AfterUpdate()
    {

    }
    virtual void BeforeDestroy()
    {
    }

protected:
    void HandleEvents();
    void Update();
    void Draw();

    glm::ivec2 windowSize = {640, 480};
    bool running = true;
    struct FpsData
    {
        float fps = 120.f;
        float timeElapsed = 0.f;
    } fpsData;
    GameObject* currentCamera;

};

#endif // GAME_H
