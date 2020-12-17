#include "inputsystem.h"

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
    if(event.type == SDL_KEYDOWN)
    {
        Button& b = keyboard[event.key.keysym.sym];
        if(b.state == Button::State::Pressed)
        {
            b.state = Button::State::Repeated;
        }
        else
            b.state = Button::State::Pressed;
    }
    else if (event.type == SDL_KEYUP)
    {
        Button& b = keyboard[event.key.keysym.sym];
        b.state = Button::State::Released;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        Button& b = mouse[event.button.button];
        b.state = Button::State::Released;
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        Button& b = mouse[event.button.button];
        if(b.state == Button::State::Pressed)
        {
            b.state = Button::State::Repeated;
        }
        else
            b.state = Button::State::Pressed;
    }
    else if (event.type == SDL_MOUSEWHEEL)
    {

    }
    else if (event.type == SDL_MOUSEMOTION)
    {

    }
}

bool InputSystem::isModPressed(Mode mod)
{
    return modifires[static_cast<int>(mod)].state == Button::State::Pressed;
}

bool InputSystem::isMousePressed(Mouse button)
{
    return mouse[static_cast<int>(button)].state == Button::State::Pressed ||
            mouse[static_cast<int>(button)].state == Button::State::Repeated;
}

bool InputSystem::isKeyPressed(Key key)
{
    return keyboard[static_cast<int>(key)].state == Button::State::Pressed ||
            keyboard[static_cast<int>(key)].state == Button::State::Repeated;
}

bool InputSystem::isKeyRepeated(Key key)
{
    return keyboard[static_cast<int>(key)].state == Button::State::Repeated;
}
