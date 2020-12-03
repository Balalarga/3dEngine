#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components/component.h"
#include "transform.h"
#include "color.h"
#include <map>

class GameObject
{
public:
    virtual ~GameObject(){
        for(auto& pair: components){
            delete pair.second;
        }
    };
    virtual void Update(float dt){
        for(auto& pair: components){
            pair.second->Update(dt);
        }
    };
    virtual void Draw(){
        for(auto& pair: components){
            pair.second->Draw();
        }};
    template<typename T, typename... TArgs>
    T* addComponent(TArgs&&... args){
        T* component(new T(std::forward<TArgs>(args)...));
        component->owner = this;
        components[&typeid(*component)] = component;
        component->init();
        return component;
    }
    template<class T>
    T* getComponent(){
        return static_cast<T*>(components[&typeid(T)]);
    }
    template<class T>
    bool hasComponent(){
        return components.find(&typeid(T)) != components.end();
    }

    Color color{1.f, 1.f, 1.f};
    Transform transform;

private:
    std::map<const std::type_info*, Component*> components;
};

#endif // GAMEOBJECT_H
