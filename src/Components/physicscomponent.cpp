#include "physicscomponent.h"

#include <iostream>
void PhysicsComponent::Update(float dt)
{
    parent->transform.Move(velocity*dt);
    if(acceleration.x || acceleration.y ||acceleration.z)
        velocity += acceleration*dt;
}
