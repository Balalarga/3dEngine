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

    glm::ivec2 windowSize = {640, 480};
    bool running = true;
    struct
    {
        double updateFrames = 60.0;
        double renderFrames = 120.0;
    } timeData;
    GameObject* currentCamera;

};

#endif // GAME_H
