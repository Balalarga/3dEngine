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
    for(auto i: objects)
    {
        delete i.second;
    }
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

void ObjectSystem::Draw()
{
    for(auto i: objects)
        i.second->Draw();
}

void ObjectSystem::Update(double dt)
{
    for(auto i: objects)
    {
        i.second->Update(dt);
    }
}

ObjectSystem::ObjectSystem()
{
}
