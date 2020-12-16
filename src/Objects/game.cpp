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
    auto cameraPhysics = currentCamera->GetComponent<PhysicsComponent>();
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
                if(cameraPhysics)
                    cameraPhysics->SetVelocity({1, 0, 0}, 10);
                break;
            case SDLK_a:
                if(cameraPhysics)
                    cameraPhysics->SetVelocity({1, 0, 0}, -10);
                break;
            case SDLK_w:
                if(cameraPhysics)
                    cameraPhysics->SetVelocity({0, 1, 0}, 10);
                break;
            case SDLK_s:
                if(cameraPhysics)
                    cameraPhysics->SetVelocity({0, 1, 0}, -10);
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_d:
            case SDLK_a:
                if(cameraPhysics)
                    cameraPhysics->ResetVelocity({1, 0, 0});
                break;
            case SDLK_w:
            case SDLK_s:
                if(cameraPhysics)
                    cameraPhysics->ResetVelocity({0, 1, 0});
                break;
            }
            break;
        }
    }
    UpdateCamera();
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
//        if(iterEnd < frameTime){
//            SDL_Delay(frameTime - iterEnd);
//        }
        prevTime = SDL_GetTicks()-iterStart;
//        if(prevTime > 0)
//            cout<<"FPS: "<<1000.f/prevTime<<endl;
    }
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
