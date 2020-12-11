#include "game.h"
#include "Components/physicscomponent.h"
#include "Components/meshcomponent.h"
#include "Managers/objectmanager.h"
#include "Utils/utils.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        Log::info("Unable to init SDL, error: ");
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
//    SDL_SetRelativeMouseMode(SDL_TRUE);

    window = SDL_CreateWindow("GameEngine",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == NULL){
        exit(1);
    }

    glcontext = SDL_GL_CreateContext(window);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    vector<glm::vec3> points{
        {-1, 0, 0}, {0,  1, 0}, {1, 0, 0},
        {-1, 0, 0}, {0, -1, 0}, {1, 0, 0},
    };
    auto object = ObjectManager::Instance().Add<GameObject>("object1");
    object->AddComponent<MeshComponent>(points);

    camera = ObjectManager::Instance().Add<Camera>("camera");
    camera->AddComponent<PhysicsComponent>();
    camera->Move({0, 0, -10});
}

bool Game::IsRunning()
{
    return running;
}

void Game::HandleEvents()
{
    SDL_Event event;
    auto cameraPhycics = camera->GetComponent<PhysicsComponent>();
    while ( SDL_PollEvent(&event) ){
        switch(event.type){
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_a:
                cameraPhycics->velocity.x = 10;
                break;
            case SDLK_d:
                cameraPhycics->velocity.x = -10;
                break;
            case SDLK_w:
                cameraPhycics->velocity.z = 10;
                break;
            case SDLK_s:
                cameraPhycics->velocity.z = -10;
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_a:
            case SDLK_d:
                cameraPhycics->velocity.x = 0;
                break;
            case SDLK_w:
            case SDLK_s:
                cameraPhycics->velocity.z = 0;
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
    Draw();

    fpsData.timeElapsed = SDL_GetTicks() - frameStart;
    if(frameTime > fpsData.timeElapsed){
        SDL_Delay(frameTime - fpsData.timeElapsed);
    }
    onTick();
}

void Game::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(camera->transform.position.x,
                 camera->transform.position.y,
                 camera->transform.position.z);
    glRotatef(camera->transform.rotation.x, 1.f, 0.f, 0.f);
    glRotatef(camera->transform.rotation.y, 0.f, 1.f, 0.f);
    glRotatef(camera->transform.rotation.z, 0.f, 0.f, 1.f);
    ObjectManager::Instance().Draw();
    SwapBuffer();
}

void Game::Update(){
    beforeUpdate();

    ObjectManager::Instance().Update(fpsData.timeElapsed/1000.f);

    afterUpdate();
}

void Game::SwapBuffer()
{
    glFlush();
    SDL_GL_SwapWindow(window);
}

void Game::Destroy()
{
    beforeDestroy();
    ObjectManager::Instance().Clear();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::SetClearColor(Color c)
{
    clearColor = c;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
}

