#include "game.h"
#include "Utils/utils.h"
#include "Systems/systems.h"
#include "Components/components.h"

Game::Game(const GameConfig& config)
{
    if(config.renderType == GameConfig::RenderType::OpenGL)
        RenderSystem::Instance().
                CreateRenderer<OpenGLRenderer>
                (config.title, config.windowSize);
    RenderSystem::Instance().GetRender()->SetClearColor(config.clearColor);

    currentCamera = ObjectSystem::Instance().Add<GameObject>("mainCamera");
    currentCamera->AddComponent<CameraComponent>();
    currentCamera->AddComponent<PhysicsComponent>();
    currentCamera->transform.Move({0.f, 0.f, 5.f});
}

Game::~Game()
{
    ObjectSystem::Instance().Clear();
}

void Game::FrameUpdate()
{

}

void Game::FixedUpdate(float dt)
{

}

void Game::Destroy()
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
    auto frameTime = 1000.f/frameData.renderFrames;
    auto updateTime = 1000.f/frameData.updateFrames;

    Uint32 prevTime = 0;
    while(running){

        Uint32 iterStart = SDL_GetTicks();
        HandleEvents();

        if(prevTime > 0 && prevTime <= updateTime)
        {
            SystemFixedUpdate(prevTime/1000.f);
            FixedUpdate(prevTime/1000.f);
        }
        SystemFrameUpdate();

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

void Game::SystemFrameUpdate()
{
    RenderSystem::Instance().GetRender()->Clear();
    ObjectSystem::Instance().FrameUpdate();
    RenderSystem::Instance().GetRender()->SwapBuffers();
}

void Game::SystemFixedUpdate(float dt)
{
    ObjectSystem::Instance().FixedUpdate(dt);
}
