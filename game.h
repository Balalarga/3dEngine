#ifndef GAME_H
#define GAME_H

#include <window.h>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;
};

const glm::vec3 DARK_GREEN = {0.05f, 0.45f, 0.1f};
const glm::vec3 LIGHT_GREEN = {0.1f, 0.8f, 0.15f};

const Vertex CUBE_VERTICIES[] = {
    { {-1, +1, -1}, DARK_GREEN},
    { {+1, +1, -1}, DARK_GREEN},
    { {+1, -1, -1}, DARK_GREEN},
    { {-1, -1, -1}, DARK_GREEN},
    { {-1, +1, +1}, LIGHT_GREEN},
    { {+1, +1, +1}, LIGHT_GREEN},
    { {+1, -1, +1}, LIGHT_GREEN},
    { {-1, -1, +1}, LIGHT_GREEN},
};
const uint16_t CUBE_INDICIES[] = {
    0, 1, 2,
    0, 2, 3,
    2, 1, 5,
    2, 5, 6,
    3, 2, 6,
    3, 6, 7,
    0, 3, 7,
    0, 7, 4,
    1, 0, 4,
    1, 4, 5,
    6, 5, 4,
    6, 4, 7,
};
class Game{
public:
    Game();
    ~Game();

    bool init();
    void start();

    void checkEvents();
    void draw();
private:
    Window* m_screen;
};

#endif // GAME_H
