#ifndef OBJECTSYSTEM_H
#define OBJECTSYSTEM_H

#include "Objects/gameobject.h"
#include <string>
#include <unordered_map>

class ObjectSystem
{
public:
    static ObjectSystem& Instance();
    void Clear();

    template<typename T, typename... TArgs>
    T* Add(std::string name, TArgs&&... args)
    {
        T* object(new T(std::forward<TArgs>(args)...));
        auto pos = objects.find(name);
        if(pos == objects.end())
        {
            objects.insert({name, object});
            return object;
        }
        else
            delete object;
        return nullptr;
    }

    void Remove(std::string name);
    GameObject* Get(std::string name);
    template<class T>
    T* GetClass(std::string name)
    {
        GameObject* obj = Get(name);
        return dynamic_cast<T*>(obj);
    }
    void FrameUpdate();
    void FixedUpdate(double dt);


private:
    static ObjectSystem* selfInstance;
    ObjectSystem();
    std::unordered_map<std::string, GameObject*> objects;
};

#endif // OBJECTSYSTEM_H
