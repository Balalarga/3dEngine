#include "cameracomponent.h"
#include <glm/gtc/matrix_transform.hpp>

glm::fmat4 CameraComponent::GetViewMatrix()
{
    glm::fvec3 eye = parent->transform.GetPos();
    glm::fvec3 up = {0.f, -1.f, 0.f};
    glm::fvec3 to = {
        eye.x,
        eye.y,
        0.f
    };

    return glm::lookAt(eye, to, up);
}
