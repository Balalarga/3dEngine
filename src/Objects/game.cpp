#include "game.h"
#include "Components/physicscomponent.h"
#include "Components/meshcomponent.h"
#include "Systems/objectsystem.h"
#include "Utils/utils.h"
#include "Systems/systems.h"

Game::Game()
{
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
}

void Game::Tick()
{
    float frameTime = 1000.f/fpsData.fps;
    float frameStart = SDL_GetTicks();

    HandleEvents();
    Update();
    RenderSystem::Instance().GetRender()->Clear();
    ObjectSystem::Instance().Draw();
    RenderSystem::Instance().GetRender()->SwapBuffers();
    fpsData.timeElapsed = SDL_GetTicks() - frameStart;
    OnTick();
    if(frameTime > fpsData.timeElapsed)
    {
        SDL_Delay(frameTime - fpsData.timeElapsed);
    }
}

void Game::Update(){
    BeforeUpdate();

    ObjectSystem::Instance().Update(fpsData.timeElapsed/1000.f);

    AfterUpdate();
}


