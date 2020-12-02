#include "game.h"
#include "Objects/objectmanager.h"
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

    for(int i = 0; i < 100; i++){
        glm::vec3 pos{i, i, -10};
        ObjectManager::Instance().Add("cube1", new CubeMesh(1, pos));
    }
//    camera = dynamic_cast<Camera*>(ObjectManager::Instance().Add("camera", new Camera));
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
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_LEFT:
//                camera->transform.Move({0, -1, 0});
                break;
            case SDLK_RIGHT:
//                camera->transform.Move({0, 1, 0});
                break;
            case SDLK_UP:
//                camera->transform.Move({1, 0, 0});
                break;
            case SDLK_DOWN:
//                camera->transform.Move({-1, 0, 0});
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glTranslatef(camera->transform.position.x,
//                 camera->transform.position.y,
//                 camera->transform.position.z);
    ObjectManager::Instance().Draw();
    SwapBuffer();
}

void Game::Update(){

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

