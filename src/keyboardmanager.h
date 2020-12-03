#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <SDL2/SDL.h>

class KeyboardManager
{
public:
    static KeyboardManager& Instance();
    void Handle(SDL_KeyboardEvent& e);

private:
    static KeyboardManager* selfInstance;
    KeyboardManager();
};

#endif // KEYBOARDMANAGER_H
