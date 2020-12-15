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
        object->AddComponent<MeshComponent>(FileSystem::ReadObj("../data/cube.obj"));
        currentCamera->transform.Move({0.f, 0.f, 2.5f});
    }
};

#endif // SANDBOXGAME_H
