#include "game.h"
#include "Utils/utils.h"
#include "Systems/systems.h"
#include "Components/components.h"

Game::Game()
{
    currentCamera = ObjectSystem::Instance().Add<GameObject>("mainCamera");
    currentCamera->AddComponent<CameraComponent>();
}

Game::~Game()
{
    ObjectSystem::Instance().Clear();
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
        switch(event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_d:
                currentCamera->transform.Move({0, 1, 0});
                break;
            case SDLK_a:
                currentCamera->transform.Move({0, -1, 0});
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
            break;
        }
    }
    UpdateCamera();
}

void Game::Tick()
{
    float frameTime = 1000.f/fpsData.fps;
    float frameStart = SDL_GetTicks();

    HandleEvents();
    Update();
    Draw();

    fpsData.timeElapsed = SDL_GetTicks() - frameStart;
    OnTick();
    if(frameTime > fpsData.timeElapsed)
    {
        SDL_Delay(frameTime - fpsData.timeElapsed);
    }
}

void Game::UpdateCamera()
{
    RenderSystem::Instance().GetRender()->
            UpdateViewMatrix(currentCamera->
                             GetComponent<CameraComponent>()->GetViewMatrix());
}

void Game::Draw(){
    RenderSystem::Instance().GetRender()->Clear();
    ObjectSystem::Instance().Draw();
    RenderSystem::Instance().GetRender()->SwapBuffers();
}

void Game::Update(){
    BeforeUpdate();

    ObjectSystem::Instance().Update(fpsData.timeElapsed/1000.f);

    AfterUpdate();
}


