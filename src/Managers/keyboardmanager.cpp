#include "keyboardmanager.h"

KeyboardManager* KeyboardManager::selfInstance = nullptr;

KeyboardManager &KeyboardManager::Instance()
{
    if(!selfInstance)
        selfInstance = new KeyboardManager;
    return *selfInstance;
}

void KeyboardManager::Handle(SDL_KeyboardEvent &e)
{

}

KeyboardManager::KeyboardManager()
{
}
