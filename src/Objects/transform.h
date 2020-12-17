#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
    const glm::fvec3& GetPos(){
        return position;
    }
    const glm::fvec3& GetScale(){
        return scale;
    }
    const glm::fvec3& GetRotation(){
        return rotation;
    }
    glm::fmat4 GetModelMatrix(){
        return modelMatrix;
    }

    void SetPos(glm::fvec3 pos){
        position = pos;
        UpdateModelMatrix();
    }
    void SetScale(glm::fvec3 scale){
        this->scale = scale;
        UpdateModelMatrix();
    }
    void SetRotation(glm::fvec3 rotation){
        this->rotation = rotation;
        UpdateModelMatrix();
    }

    void Move(glm::fvec3 dPosition)
    {
        position += dPosition;
        UpdateModelMatrix();
    }
    void Rotate(glm::fvec3 dAngle)
    {
        rotation += dAngle;
        UpdateModelMatrix();
    }
    void Scale(glm::fvec3 dScale)
    {
        scale += dScale;
        UpdateModelMatrix();
    }


private:
    glm::fvec3 position{0, 0, 0};
    glm::fvec3 rotation{0, 0, 0};
    glm::fvec3 scale   {1, 1, 1};
    glm::fmat4 modelMatrix = glm::fmat4(1.0f);
    void UpdateModelMatrix(){
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotation.x, {1, 0, 0});
        modelMatrix = glm::rotate(modelMatrix, rotation.y, {0, 1, 0});
        modelMatrix = glm::rotate(modelMatrix, rotation.z, {0, 0, 1});
    }
};

#endif // TRANSFORM_H
