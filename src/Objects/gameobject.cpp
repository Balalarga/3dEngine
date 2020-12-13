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

void GameObject::Move(glm::vec3 dPosition)
{
    transform.position += dPosition;
}

void GameObject::Rotate(glm::vec3 dAngle)
{
    transform.rotation += dAngle;
}

void GameObject::Scale(glm::vec3 dScale)
{
    transform.scale += dScale;
}
