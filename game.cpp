#include "game.h"
#include <iostream>
using namespace std;

Game* Game::selfInstance = nullptr;

Game &Game::instance()
{
    if(!selfInstance)
        selfInstance = new Game();
    return *selfInstance;
}

void Game::init()
{

    // Инициализация SDL

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
        exit(1);
    }

    // Включаем двойной буфер, настраиваем цвета

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    // Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

    window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

    if(window == NULL){	// если не получилось создать окно, то выходим
        exit(1);
    }

    // Инициализация OpenGL

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); // включаем тест глубины
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
    glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим

    for(int i = 0; i < 1; i++){
        glm::vec3 pos;
        pos.x = 1*i;
        pos.y = 7;
        pos.x = 7;
        CubeMesh cube(1, pos);
        cubes.push_back(cube);
    }
}

bool Game::isRunning()
{
    return running;
}

void Game::handleEvents()
{
    SDL_Event event; // события SDL

    while ( SDL_PollEvent(&event) ){ // начинаем обработку событий
        switch(event.type){ // смотрим:
            case SDL_QUIT: // если произошло событие закрытия окна, то завершаем работу программы
                running = false;
            break;

            case SDL_KEYDOWN: // если нажата клавиша
                switch(event.key.keysym.sym){ // смотрим какая
                    case SDLK_ESCAPE: // клавиша ESC
                        running = false; // завершаем работу программы
                    break;
                }
            break;
        }
    }
}

void Game::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto& i : cubes){
        glPushMatrix();
        i.draw();
        glPopMatrix();
    }
}

void Game::swapBuffer()
{
    glFlush();
    SDL_GL_SwapWindow(window);
}

Game::~Game()
{
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit(); // завершаем работу SDL и выходим
}

Game::Game()
{

}
