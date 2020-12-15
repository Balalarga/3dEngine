#include "gameobject.h"
#include "Components/basecomponent.h"

GameObject::~GameObject()
{
    for(auto& pair: components)
    {
        delete pair.second;
    }
};

void GameObject::Update(float dt)
{
    for(auto& pair: components)
    {
        pair.second->Update(dt);
    }
};

void GameObject::Draw()
{
    for(auto& pair: components)
        pair.second->Draw();
};
