#include "window.h"
#include <iostream>
using std::cout;

Window::Window(const char* title){
    m_size = {640, 480};
    m_title = title;
    m_window= SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_size.x, m_size.y,
                                SDL_WINDOW_OPENGL);
    if(!m_window){
        cout<<"Window couldn't be created\n";
        return;
    }
    m_glContext = SDL_GL_CreateContext(m_window);
    m_opened = true;
}

void Window::clear(){
    glClearColor(m_clearColor.x, m_clearColor.y,
                 m_clearColor.z, m_clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close(){
    m_opened = false;
}

void Window::swap(){
    SDL_GL_SwapWindow(m_window);
}

bool Window::isOpen(){
    return m_opened;
}

void Window::setClearColor(const glm::vec4& color){
    m_clearColor = color;
}

Window::~Window(){
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
}
