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
        auto mesh = FileSystem::ReadObj("../data/cube.obj");
        auto object = ObjectSystem::Instance().Add<GameObject>("object1");
        object->AddComponent<MeshComponent>(mesh);
        object->transform.Move({-4, 0, 0});

        auto object2 = ObjectSystem::Instance().Add<GameObject>("object2");
        mesh.color = {1.f, 0.f, 1.f};
        object2->AddComponent<MeshComponent>(mesh);
        object->transform.Move({4, 0, 0});
    }

    void FixedUpdate(float dt) override
    {
        auto cameraPhysics = currentCamera->GetComponent<PhysicsComponent>();
        bool cameraMoved = false;
        if(InputSystem::Instance().IsKeyPressed(Key::A))
        {
            cameraPhysics->SetVelocity({1, 0, 0}, -cameraSpeed);
            cameraMoved = true;
        }
        else if(InputSystem::Instance().IsKeyPressed(Key::D))
        {
            cameraPhysics->SetVelocity({1, 0, 0}, cameraSpeed);
            cameraMoved = true;
        }
        else
        {
            cameraPhysics->ResetVelocity({1, 0, 0});
            cameraMoved = true;
        }

        if(InputSystem::Instance().IsKeyPressed(Key::W))
        {
            if(InputSystem::Instance().IsKeyPressed(Key::A))
            {
                double sqrtSpeed = 0.707*cameraSpeed;
                cameraPhysics->SetVelocity({0, 1, 0}, sqrtSpeed);
                cameraPhysics->SetVelocity({1, 0, 0}, -sqrtSpeed);
            }
            else if(InputSystem::Instance().IsKeyPressed(Key::D))
            {
                double sqrtSpeed = 0.707*cameraSpeed;
                cameraPhysics->SetVelocity({1, 0, 0}, sqrtSpeed);
                cameraPhysics->SetVelocity({0, 1, 0}, sqrtSpeed);
            }
            else
                cameraPhysics->SetVelocity({0, 1, 0}, cameraSpeed);
            cameraMoved = true;
        }
        else if(InputSystem::Instance().IsKeyPressed(Key::S))
        {
            if(InputSystem::Instance().IsKeyPressed(Key::A))
            {
                double sqrtSpeed = 0.707*cameraSpeed;
                cameraPhysics->SetVelocity({0, 1, 0}, -sqrtSpeed);
                cameraPhysics->SetVelocity({1, 0, 0}, -sqrtSpeed);
            }
            else if(InputSystem::Instance().IsKeyPressed(Key::D))
            {
                double sqrtSpeed = 0.707*cameraSpeed;
                cameraPhysics->SetVelocity({1, 0, 0}, sqrtSpeed);
                cameraPhysics->SetVelocity({0, 1, 0}, -sqrtSpeed);
            }
            else
                cameraPhysics->SetVelocity({0, 1, 0}, -cameraSpeed);
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
    double cameraSpeed = 5;
};

#endif // SANDBOXGAME_H
