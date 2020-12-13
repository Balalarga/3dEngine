#ifndef SANDBOXGAME_H
#define SANDBOXGAME_H


#include "Objects/game.h"
#include "Components/components.h"
#include "Systems/systems.h"

#include <vector>
using namespace std;

class SandboxGame: public Game
{
public:
    SandboxGame()
    {
        try
        {
            RenderSystem::Instance().
                    CreateRenderer<OpenGLRenderer>
                    ("My game", glm::ivec2{640, 480});
        }
        catch (const std::string error)
        {
            throw error;
        }
        RenderSystem::Instance().GetRender()->SetClearColor({.1f, .1f, .1f});
        Configurate();
    }

    void OnTick() override
    {

    }
    void BeforeUpdate() override
    {

    }
    void AfterUpdate() override
    {

    }
    void Configurate()
    {
        auto object = ObjectSystem::Instance().Add<GameObject>("object1");
        MeshData meshData;
        meshData.verteces = {
            {0.0f, 1.0f, 0.0f},
            {1.0f, 1.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f, 0.0f},
        };
        meshData.indices = {0, 1, 2, 0, 3, 4};
        object->AddComponent<MeshComponent>(meshData);
    }
};

#endif // SANDBOXGAME_H
