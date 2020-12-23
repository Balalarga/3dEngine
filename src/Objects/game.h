#ifndef GAME_H
#define GAME_H

#include "glIncludes.h"
#include "gameobject.h"
#include "Systems/RenderSystem/baserenderer.h"
#include <vector>

struct GameConfig
{
    enum class RenderType{
        OpenGL,
        DirectX11,
        DirectX12,
        Vulkan
    } renderType;
    std::string title;
    glm::ivec2 windowSize;
    glm::fvec3 clearColor = {.1f, .1f, .1f};
};

class Game
{
public:
    Game(const GameConfig& config);
    void Run();
    void Stop();
    void UpdateCamera();
    bool IsRunning();

    virtual ~Game();
    virtual void FrameUpdate();
    virtual void FixedUpdate(float dt);
    virtual void Destroy();

protected:
    void HandleEvents();
    void SystemFixedUpdate(float dt);
    void SystemFrameUpdate();

    bool running = true;
    struct
    {
        int updateFrames = 60;
        int renderFrames = 240;
    } frameData;
    GameObject* currentCamera;

};

#endif // GAME_H
