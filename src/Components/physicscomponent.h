#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "basecomponent.h"
#include "glIncludes.h"

class PhysicsComponent: public Component
{
public:
    void FixedUpdate(float dt) override;
    void AddVelocity(glm::bvec3 pos, float value);
    void SetVelocity(glm::bvec3 pos, float value);
    void ResetVelocity(glm::bvec3 pos);
    glm::fvec3 velocity {0.f, 0.f, 0.f};
    glm::fvec3 acceleration {0.f, 0.f, 0.f};
};

#endif // PHYSICSCOMPONENT_H
