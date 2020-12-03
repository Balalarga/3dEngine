#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "gameobject.h"
#include <string>
#include <unordered_map>

class ObjectManager
{
public:
    static ObjectManager& Instance();
    void Clear();
    GameObject* Add(std::string name, GameObject*&& object);
    void Remove(std::string name);
    GameObject* Get(std::string name);
    void Draw();
    void Update(double dt);


private:
    static ObjectManager* selfInstance;
    ObjectManager();
    std::unordered_map<std::string, GameObject*> objects;
};

#endif // OBJECTMANAGER_H
