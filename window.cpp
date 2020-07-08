#include "window.h"
#include <iostream>
using std::cout;

Window::Window(const char* title)
{
    m_width = 640;
    m_height = 640;
    m_title = title;
    m_window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_width, m_height,
                                SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
    if(!m_window){
        cout<<"Window couldn't be created\n";
        return;
    }
    m_glContext = SDL_GL_CreateContext(m_window);
    m_opened = false;
}

void Window::clear(){
    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap(){
    SDL_GL_SwapWindow(m_window);
}

bool Window::isOpen()
{
    return m_opened;
}

void Window::setClearColor(const glm::vec4& color){
    m_clearColor = color;
}

Window::~Window()
{
}
