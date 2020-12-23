#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"
#include <map>

class Component;

class GameObject
{
public:
    virtual ~GameObject();
    virtual void FixedUpdate(float dt);
    virtual void FrameUpdate();

    template<typename T, typename... TArgs>
    T* AddComponent(TArgs&&... args)
    {
        if(HasComponent<T>())
            GetComponent<T>();
        T* component(new T(std::forward<TArgs>(args)...));
        component->parent = this;
        components[&typeid(*component)] = component;
        component->Init();
        return component;
    }

    template<class T>
    T* GetComponent()
    {
        if(HasComponent<T>())
            return static_cast<T*>(components[&typeid(T)]);
        return nullptr;
    }

    template<class T>
    bool HasComponent()
    {
        return components.find(&typeid(T)) != components.end();
    }

    Transform transform;

private:
    std::map<const std::type_info*, Component*> components;
};

#endif // GAMEOBJECT_H
