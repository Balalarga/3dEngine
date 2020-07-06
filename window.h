#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
using std::string;

class Window
{
public:
    Window(const char *title);

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;

    string m_title;
    unsigned int m_width;
    unsigned int m_height;
};

#endif // WINDOW_H
