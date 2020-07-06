#include "window.h"
#include <iostream>
using std::cout;

Window::Window(const char* title)
{
    m_window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                640, 480,
                                SDL_WINDOW_HIDDEN);
    if(!m_window){
        cout<<"Window couldn't be created\n";
        return;
    }
    m_glContext = SDL_GL_CreateContext(m_window);
}
