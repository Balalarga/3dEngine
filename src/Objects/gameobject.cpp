#include "gameobject.h"
#include "Components/basecomponent.h"

GameObject::~GameObject()
{
    for(auto& pair: components)
    {
        delete pair.second;
    }
};

void GameObject::FixedUpdate(float dt)
{
    for(auto& pair: components)
    {
        pair.second->FixedUpdate(dt);
    }
};

void GameObject::FrameUpdate()
{
    for(auto& pair: components)
        pair.second->FrameUpdate();
};
