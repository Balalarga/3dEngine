#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <GLEW/glew.h>

#include <string>
#include <memory>
using std::string;

using SDLWindowPtr = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;
using SDLGLContextPtr = std::unique_ptr<SDL_GLContext, void(*)(SDL_GLContext)>;

class Window
{
public:
    Window(const char *title);
    ~Window();
    void swap();
    bool isOpen();
    void clear();
    void setClearColor(const glm::vec4& color);

private:

    SDLWindowPtr m_window(nullptr, SDL_DestroyWindow);
    SDL_GLContext m_glContext;
    glm::vec4 m_clearColor;

    string m_title;
    unsigned int m_width;
    unsigned int m_height;
    bool m_opened;
};

#endif // WINDOW_H
