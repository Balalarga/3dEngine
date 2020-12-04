#include "game.h"
#include "Objects/objectmanager.h"
#include "Components/meshcomponent.h"
#include <iostream>
using namespace std;

Game* Game::selfInstance = nullptr;

Game::Game()
{

}

Game &Game::Instance()
{
    if(!selfInstance)
        selfInstance = new Game();
    return *selfInstance;
}

void Game::Init()
{

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

    window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

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
    camera->Move({0, 0, -5});
}

bool Game::IsRunning()
{
    return running;
}

void Game::HandleEvents()
{
    SDL_Event event;
    while ( SDL_PollEvent(&event) ){
        switch(event.type){
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.scancode){
            case SDL_SCANCODE_ESCAPE:
                running = false;
                break;
            case SDL_SCANCODE_LEFT:
                camera->Move({-0.1, 0, 0});
                break;
            case SDL_SCANCODE_RIGHT:
                camera->Move({0.1, 0, 0});
                break;
            case SDL_SCANCODE_UP:
                camera->Move({0, 0.1, 0});
                break;
            case SDL_SCANCODE_DOWN:
                camera->Move({0, -0.1, 0});
                break;
            }
            break;
        case SDL_KEYUP:
            break;
        }
    }
}

void Game::Tick()
{
    float frameTime = 1000.f/fpsData.fps;
    float frameStart = SDL_GetTicks();

    Game::Instance().HandleEvents();
    Game::Instance().Update();
    Game::Instance().Draw();

    fpsData.timeElapsed = SDL_GetTicks() - frameStart;
    if(frameTime > fpsData.timeElapsed){
        SDL_Delay(frameTime - fpsData.timeElapsed);
    }
}

void Game::Draw()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(camera->transform.position.x,
                 camera->transform.position.y,
                 camera->transform.position.z);
    ObjectManager::Instance().Draw();
    SwapBuffer();
}

void Game::Update(){
    ObjectManager::Instance().Update(fpsData.timeElapsed);
}

void Game::SwapBuffer()
{
    glFlush();
    SDL_GL_SwapWindow(window);
}

void Game::Destroy()
{
    ObjectManager::Instance().Clear();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::SetClearColor(Color c)
{
    clearColor = c;
}

