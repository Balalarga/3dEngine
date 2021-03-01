#include "objectsystem.h"

ObjectSystem* ObjectSystem::selfInstance = nullptr;

ObjectSystem& ObjectSystem::Instance()
{
    if(!selfInstance)
        selfInstance = new ObjectSystem;
    return *selfInstance;
}

void ObjectSystem::Clear()
{
    for(auto& i: objects)
    {
        delete i.second;
    }
    if(mainLight)
        delete mainLight;
}

void ObjectSystem::AddAmbientLight(glm::vec3 color)
{
    ambientColor = color;
}

LightObject *ObjectSystem::AddDiffuseLight(glm::vec3 pos, glm::vec3 color)
{
    mainLight = new LightObject(color);
    mainLight->transform.Move(pos);

    return mainLight;
}

void ObjectSystem::Remove(std::string name)
{
    auto pos = objects.find(name);
    if(pos != objects.end())
    {
        objects.erase(pos);
        delete pos->second;
    }
}

GameObject *ObjectSystem::Get(std::string name)
{
    auto pos = objects.find(name);
    if(pos != objects.end())
        return pos->second;
    return nullptr;
}

void ObjectSystem::FrameUpdate()
{
    for(auto& i: objects)
        i.second->FrameUpdate();
}

void ObjectSystem::FixedUpdate(double dt)
{
    for(auto& i: objects)
    {
        i.second->FixedUpdate(dt);
    }
}

ObjectSystem::~ObjectSystem()
{
    Clear();
}

ObjectSystem::ObjectSystem()
{
}
