#ifndef GAME_H
#define GAME_H

#include "glIncludes.h"
#include "Objects/gameobject.h"
#include "Systems/RenderSystem/baserenderer.h"
#include <vector>

class Game
{
public:
    Game();
    bool IsRunning();
    void HandleEvents();
    void Tick();
    void Update();

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
    glm::ivec2 windowSize = {640, 480};
    bool running = true;
    struct FpsData
    {
        float fps = 60.f;
        float timeElapsed = 0.f;
    } fpsData;
};

#endif // GAME_H
