#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "keycodes.h"


class InputSystem
{
struct Button{
    enum class State{
        Released,
        Pressed,
        Repeated
    } state;
};

public:
    static InputSystem& Instance();

    void HandleEvent(SDL_Event& event);
    bool isKeyPressed(Key key);
    bool isKeyRepeated(Key key);
    bool isModPressed(Mode mod);
    bool isMousePressed(Mouse button);

private:
    InputSystem();
    static InputSystem* selfInstance;

    Button keyboard[static_cast<int>(Key::SIZE_OF_ENUM)];
    Button modifires[static_cast<int>(Mode::SIZE_OF_ENUM)];
    Button mouse[static_cast<int>(Mouse::SIZE_OF_ENUM)];
};

#endif // INPUTSYSTEM_H
