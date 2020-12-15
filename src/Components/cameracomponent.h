#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include <glm/glm.hpp>
#include "basecomponent.h"

class CameraComponent: public Component
{
public:
    glm::mat4 GetViewMatrix();
};

#endif // CAMERACOMPONENT_H
