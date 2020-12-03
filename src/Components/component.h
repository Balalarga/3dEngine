#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component{
public:
    virtual ~Component(){}
    virtual void Init(){}
    virtual void Update(float dt){}
    virtual void Draw(){}
    GameObject* parent;
};

#endif // COMPONENT_H
