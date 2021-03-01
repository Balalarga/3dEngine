#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "gameobject.h"

class LightObject : public GameObject
{
public:
    LightObject(glm::vec3 color);
    glm::vec3 color;
};

#endif // LIGHTOBJECT_H
