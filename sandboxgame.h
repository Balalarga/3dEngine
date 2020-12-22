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
    SandboxGame(const GameConfig& config):
        Game(config)
    {
        auto object = ObjectSystem::Instance().Add<GameObject>("object1");
        auto mesh1 = FileSystem::ReadObj("../data/cube.obj");
        object->AddComponent<MeshComponent>(mesh1);
        object->transform.Move({-4, 0, 0});

        auto object2 = ObjectSystem::Instance().Add<GameObject>("object2");
        mesh1.color = {1.f, 0.f, 1.f};
        object2->AddComponent<MeshComponent>(mesh1);
        object->transform.Move({4, 0, 0});
    }

    void FixedUpdate(float dt) override
    {
        auto cameraPhysics = currentCamera->GetComponent<PhysicsComponent>();
        bool cameraMoved = false;
        if(InputSystem::Instance().IsKeyPressed(Key::A))
        {
            cameraPhysics->SetVelocity({1, 0, 0}, -1);
            cameraMoved = true;
        }
        else if(InputSystem::Instance().IsKeyPressed(Key::D))
        {
            cameraPhysics->SetVelocity({1, 0, 0}, 1);
            cameraMoved = true;
        }
        else
        {
            cameraPhysics->ResetVelocity({1, 0, 0});
            cameraMoved = true;
        }

        if(InputSystem::Instance().IsKeyPressed(Key::W))
        {
            cameraPhysics->SetVelocity({0, 1, 0}, 1);
            cameraMoved = true;
        }
        else if(InputSystem::Instance().IsKeyPressed(Key::S))
        {
            cameraPhysics->SetVelocity({0, 1, 0}, -1);
            cameraMoved = true;
        }
        else
        {
            cameraPhysics->ResetVelocity({0, 1, 0});
            cameraMoved = true;
        }
        if(InputSystem::Instance().IsKeyPressed(Key::ESCAPE))
            Stop();
        if(cameraMoved)
            UpdateCamera();
    }
};

#endif // SANDBOXGAME_H
