#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"
#include "glIncludes.h"

class PhysicsComponent: public Component
{
public:
    void Update(float dt) override;
    glm::vec3 velocity{0.f, 0.f, 0.f};
    glm::vec3 acceleration{0.f, 0.f, 0.f};
};

#endif // PHYSICSCOMPONENT_H
