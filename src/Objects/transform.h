#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform
{
public:
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale   {1, 1, 1};
    void Move(glm::vec3 dPosition){
        position.x += dPosition.x;
        position.y += dPosition.y;
        position.z += dPosition.z;
    }
    void Rotate(glm::vec3 dAngle){
        position.x += dAngle.x;
        position.y += dAngle.y;
        position.z += dAngle.z;
    }
    void Scale(glm::vec3 dScale){
        position.x += dScale.x;
        position.y += dScale.y;
        position.z += dScale.z;
    }
};

#endif // TRANSFORM_H
