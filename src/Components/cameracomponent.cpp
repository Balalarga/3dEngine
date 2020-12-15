#include "cameracomponent.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 CameraComponent::GetViewMatrix()
{
    glm::vec3 eye = parent->transform.GetPos();
    glm::vec3 up = {0.f, -1.f, 0.f};
    glm::vec3 to = {
        eye.x,
        eye.y,
        0.f
    };

    return glm::lookAt(eye, to, up);
}
