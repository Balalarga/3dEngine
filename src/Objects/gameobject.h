#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glIncludes.h"
#include "transform.h"
#include "color.h"
#include <map>

class Component;

class GameObject
{
public:
    virtual ~GameObject();
    virtual void Update(float dt);
    virtual void Draw();

    template<typename T, typename... TArgs>
    T* AddComponent(TArgs&&... args)
    {
        T* component(new T(std::forward<TArgs>(args)...));
        component->parent = this;
        components[&typeid(*component)] = component;
        component->Init();
        return component;
    }

    template<class T>
    T* GetComponent()
    {
        return static_cast<T*>(components[&typeid(T)]);
    }

    template<class T>
    bool HasComponent()
    {
        return components.find(&typeid(T)) != components.end();
    }

    Color color{1.f, 1.f, 1.f};
    Transform transform;

private:
    std::map<const std::type_info*, Component*> components;
};

#endif // GAMEOBJECT_H
