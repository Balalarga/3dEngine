#include "inputsystem.h"
#include <SDL2/SDL.h>
#include "Utils/utils.h"

InputSystem* InputSystem::selfInstance = nullptr;

InputSystem::InputSystem()
{

}

InputSystem &InputSystem::Instance()
{
    if(!selfInstance)
        selfInstance = new InputSystem;
    return *selfInstance;
}

void InputSystem::HandleEvent(SDL_Event &event)
{
    mouse.delta.x = 0;
    mouse.delta.y = 0;

    auto& b = keys[event.key.keysym.scancode];
    if(event.type == SDL_KEYDOWN)
    {
        if(b.pressed)
            b.repeated = true;
        else
            b.pressed = true;
    }
    else if (event.type == SDL_KEYUP)
    {
        b.pressed = false;
        b.repeated = false;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        mouse.buttons[event.button.button] = true;
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        mouse.buttons[event.button.button] = false;
    }
    else if (event.type == SDL_MOUSEWHEEL)
    {
        mouse.wheel.x = event.wheel.x;
        mouse.wheel.y = event.wheel.y;
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
        mouse.delta.x = event.motion.xrel;
        mouse.delta.y = event.motion.yrel;
        mouse.position.x = event.motion.x;
        mouse.position.y = event.motion.y;
    }
}

glm::fvec2 InputSystem::GetMousePos()
{
    return mouse.position;
}

bool InputSystem::IsModPressed(Mode mod)
{
    return modes[int(mod)];
}

bool InputSystem::IsMousePressed(Mouse button)
{
    return mouse.buttons[int(button)];
}

bool InputSystem::IsKeyPressed(Key key)
{
    return keys[int(key)].pressed;
}

bool InputSystem::IsKeyRepeated(Key key)
{
    return keys[int(key)].repeated;
}
