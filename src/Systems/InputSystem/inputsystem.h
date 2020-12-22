#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "keycodes.h"
#include <glm/glm.hpp>

struct KeyState{
    bool pressed = false;
    bool repeated = false;
};

class InputSystem
{

public:
    static InputSystem& Instance();

    void HandleEvent(SDL_Event& event);
    bool IsKeyPressed(Key key);
    bool IsKeyRepeated(Key key);
    bool IsModPressed(Mode mod);
    bool IsMousePressed(Mouse button);
    glm::fvec2 GetMousePos();

protected:
    InputSystem();
    static InputSystem* selfInstance;

    KeyState keys[int(Key::SIZE_OF_ENUM)];
    bool modes[int(Mode::SIZE_OF_ENUM)];
    struct MouseData{
        glm::ivec2 wheel = {0, 0};
        glm::ivec2 position = {0, 0};
        glm::ivec2 delta = {0, 0};
        bool buttons[int(Mouse::SIZE_OF_ENUM)];
    } mouse;
};

#endif // INPUTSYSTEM_H
