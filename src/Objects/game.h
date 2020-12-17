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
    void Run();
    void Stop();
    void UpdateCamera();
    bool IsRunning();

    virtual ~Game();
    virtual void OnTick();
    virtual void BeforeUpdate();
    virtual void AfterUpdate();
    virtual void BeforeDestroy();

protected:
    void HandleEvents();
    void Update(float dt);
    void Draw();

    bool running = true;
    struct
    {
        int updateFrames = 60;
        int renderFrames = 240;
    } timeData;
    GameObject* currentCamera;

};

#endif // GAME_H
