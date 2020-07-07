#ifndef GAME_H
#define GAME_H

#include <window.h>

class Game
{
public:
    Game();
    bool init();
    ~Game();

    void run();
private:
    Window* m_screen;
};

#endif // GAME_H
