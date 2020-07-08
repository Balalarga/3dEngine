#ifndef GAME_H
#define GAME_H

#include <window.h>

class Game{
public:
    Game();
    ~Game();

    bool init();
    void start();

    void checkEvents();
private:
    Window* m_screen;
};

#endif // GAME_H
