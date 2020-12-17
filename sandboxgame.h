#ifndef SANDBOXGAME_H
#define SANDBOXGAME_H


#include "Objects/game.h"
#include "Components/components.h"
#include "Systems/systems.h"

#include <vector>
#include <iostream>

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
                    ("My game", glm::ivec2{1200, 700});
        }
        catch (const std::string error)
        {
            throw error;
        }
        RenderSystem::Instance().GetRender()->SetClearColor({.1f, .1f, .1f});


        auto object = ObjectSystem::Instance().Add<GameObject>("object1");
        auto mesh1 = FileSystem::ReadObj("../data/cube.obj");
        object->AddComponent<MeshComponent>(mesh1);
        object->transform.Move({-4, 0, 0});

        auto object2 = ObjectSystem::Instance().Add<GameObject>("object2");
        mesh1.color = {1.f, 0.f, 1.f};
        object2->AddComponent<MeshComponent>(mesh1);
        object->transform.Move({4, 0, 0});

        currentCamera->transform.Move({0.f, 0.f, 5.f});
    }

    void OnTick() override
    {

    }

    void BeforeUpdate() override
    {
        auto cameraPhysics = currentCamera->GetComponent<PhysicsComponent>();
        bool cameraMoved = false;
        if(InputSystem::Instance().isKeyPressed(Key::A))
        {
            cameraPhysics->SetVelocity({1, 0, 0}, -10);
            cameraMoved = true;
        }
        else if(InputSystem::Instance().isKeyPressed(Key::D))
        {
            cameraPhysics->SetVelocity({1, 0, 0}, 10);
            cameraMoved = true;
        }
        else
        {
            cameraPhysics->ResetVelocity({1, 0, 0});
            cameraMoved = true;
        }

        if(InputSystem::Instance().isKeyPressed(Key::W))
        {
            cameraPhysics->SetVelocity({0, 1, 0}, 10);
            cameraMoved = true;
        }
        else if(InputSystem::Instance().isKeyPressed(Key::S))
        {
            cameraPhysics->SetVelocity({0, 1, 0}, -10);
            cameraMoved = true;
        }
        else
        {
            cameraPhysics->ResetVelocity({0, 1, 0});
            cameraMoved = true;
        }
        if(InputSystem::Instance().isKeyPressed(Key::ESCAPE))
            Stop();
        if(cameraMoved)
            UpdateCamera();
    }
    void AfterUpdate() override
    {

    }
};

#endif // SANDBOXGAME_H
