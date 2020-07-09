#ifndef WINDOW_H
#define WINDOW_H

#include "glLibs.h"

#include <string>
#include <memory>
using std::string;

class Window{
public:
    Window(const char *title);
    ~Window();
    void swap();
    bool isOpen();
    void clear();
    void close();
    void setClearColor(const glm::vec4& color);

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    glm::vec4 m_clearColor;

    string m_title;
    glm::ivec2 m_size;
    bool m_opened;
};

#endif // WINDOW_H
