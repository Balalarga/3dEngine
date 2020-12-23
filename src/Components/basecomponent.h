#ifndef COMPONENT_H
#define COMPONENT_H

#include "Objects/gameobject.h"

class Component
{
public:
    virtual ~Component()
    {

    }
    virtual void Init()
    {

    }
    virtual void FixedUpdate(float dt)
    {

    }
    virtual void FrameUpdate()
    {

    }
    GameObject* parent;
};

#endif // COMPONENT_H
