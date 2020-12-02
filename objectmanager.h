#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "mesh.h"
#include <string>
#include <unordered_map>

class ObjectManager
{
public:
    static ObjectManager& Instance();
    void Clear();
    Mesh* Add(std::string name, Mesh*&& object);
    void Remove(std::string name);
    Mesh* Get(std::string name);
    void Draw();
    void Update(double dt);


private:
    static ObjectManager* selfInstance;
    ObjectManager();
    std::unordered_map<std::string, Mesh*> objects;
};

#endif // OBJECTMANAGER_H
