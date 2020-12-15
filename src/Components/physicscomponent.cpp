#include "physicscomponent.h"

#include <iostream>
void PhysicsComponent::Update(float dt)
{
    parent->transform.Move(velocity*dt);
    if(acceleration.x || acceleration.y ||acceleration.z)
        velocity += acceleration*dt;
}

void PhysicsComponent::AddVelocity(glm::bvec3 pos, float value)
{
    if(pos.x)
        velocity.x += value;
    if(pos.y)
        velocity.y += value;
    if(pos.z)
        velocity.z += value;
}

void PhysicsComponent::ResetVelocity(glm::bvec3 pos)
{
    if(pos.x)
        velocity.x = 0;
    if(pos.y)
        velocity.y = 0;
    if(pos.z)
        velocity.z = 0;
}
