#include "objectmanager.h"
#include "../glIncludes.h"

ObjectManager* ObjectManager::selfInstance = nullptr;

ObjectManager& ObjectManager::Instance(){
    if(!selfInstance)
        selfInstance = new ObjectManager;
    return *selfInstance;
}

void ObjectManager::Clear()
{
    for(auto i: objects){
        delete i.second;
    }
}

GameObject *ObjectManager::Add(std::string name, GameObject *&&object)
{
    auto pos = objects.find(name);
    if(pos == objects.end()){
        objects.insert({name, object});
        return object;
    }else
        delete object;
    return nullptr;
}

void ObjectManager::Remove(std::string name)
{
    auto pos = objects.find(name);
    if(pos != objects.end()){
        objects.erase(pos);
        delete pos->second;
    }
}

GameObject *ObjectManager::Get(std::string name)
{
    auto pos = objects.find(name);
    if(pos != objects.end())
        return pos->second;
    return nullptr;
}

void ObjectManager::Draw()
{
    for(auto i: objects){
        glPushMatrix();
        i.second->Draw();
        glPopMatrix();
    }
}

void ObjectManager::Update(double dt)
{
    for(auto i: objects){
        i.second->Update(dt);
    }
}

ObjectManager::ObjectManager()
{
}
