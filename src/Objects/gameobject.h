#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components/component.h"
#include "glIncludes.h"
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
        glPushMatrix();

        glTranslatef(transform.position.x,
                     transform.position.y,
                     transform.position.z);
        glRotatef(transform.rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(transform.rotation.z, 0.0f, 0.0f, 1.0f);

        glColor3f(color.r,
                  color.g,
                  color.b);

        for(auto& pair: components)
            pair.second->Draw();

        glPopMatrix();
    };

    template<typename T, typename... TArgs>
    T* AddComponent(TArgs&&... args){
        T* component(new T(std::forward<TArgs>(args)...));
        component->parent = this;
        components[&typeid(*component)] = component;
        component->Init();
        return component;
    }

    template<class T>
    T* HetComponent(){
        return static_cast<T*>(components[&typeid(T)]);
    }

    template<class T>
    bool HasComponent(){
        return components.find(&typeid(T)) != components.end();
    }
    void Move(glm::vec3 dPosition){
        transform.position += dPosition;
    }
    void Rotate(glm::vec3 dAngle){
        transform.rotation += dAngle;
    }
    void Scale(glm::vec3 dScale){
        transform.scale += dScale;
    }
    Color color{1.f, 1.f, 1.f};
    Transform transform;

private:
    std::map<const std::type_info*, Component*> components;
};

#endif // GAMEOBJECT_H
