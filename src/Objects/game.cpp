#include "game.h"
#include "Utils/utils.h"
#include "Systems/systems.h"
#include "Components/components.h"

Game::Game()
{
    currentCamera = ObjectSystem::Instance().Add<GameObject>("mainCamera");
    currentCamera->AddComponent<CameraComponent>();
    currentCamera->AddComponent<PhysicsComponent>();
}

Game::~Game()
{
    ObjectSystem::Instance().Clear();
}

void Game::OnTick()
{

}

void Game::BeforeUpdate()
{

}

void Game::AfterUpdate()
{

}

void Game::BeforeDestroy()
{

}

bool Game::IsRunning()
{
    return running;
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            running = false;
        }
        else
        {
            InputSystem::Instance().HandleEvent(event);
        }
    }
}

void Game::Run()
{
    auto frameTime = 1000.f/timeData.renderFrames;
    auto updateTime = 1000.f/timeData.updateFrames;

    Uint32 prevTime = 0;
    while(running){

        Uint32 iterStart = SDL_GetTicks();
        HandleEvents();

        if(prevTime > 0 && prevTime <= updateTime)
            Update(prevTime/1000.f);

        Draw();

        Uint32 iterEnd = SDL_GetTicks();
        if(iterEnd < frameTime)
        {
            SDL_Delay(frameTime - iterEnd);
        }
        prevTime = SDL_GetTicks()-iterStart;
    }
}

void Game::Stop()
{
    running = false;
}

void Game::UpdateCamera()
{
    RenderSystem::Instance().GetRender()->
            UpdateViewMatrix(currentCamera->
                             GetComponent<CameraComponent>()->GetViewMatrix());
}

void Game::Draw()
{
    RenderSystem::Instance().GetRender()->Clear();
    ObjectSystem::Instance().Draw();
    RenderSystem::Instance().GetRender()->SwapBuffers();
}

void Game::Update(float dt)
{
    BeforeUpdate();

    ObjectSystem::Instance().Update(dt);

    AfterUpdate();
}
