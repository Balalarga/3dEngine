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

    template<typename T, typename... TArgs>
    T* Add(std::string name, TArgs&&... args){
        T* object(new T(std::forward<TArgs>(args)...));
        auto pos = objects.find(name);
        if(pos == objects.end()){
            objects.insert({name, object});
            return object;
        }else
            delete object;
        return nullptr;
    }

    void Remove(std::string name);
    GameObject* Get(std::string name);
    template<class T>
    T* GetClass(std::string name){
        GameObject* obj = Get(name);
        return dynamic_cast<T*>(obj);
    }
    void Draw();
    void Update(double dt);


private:
    static ObjectManager* selfInstance;
    ObjectManager();
    std::unordered_map<std::string, GameObject*> objects;
};

#endif // OBJECTMANAGER_H
