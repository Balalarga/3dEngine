#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
    const glm::vec3& GetPos(){
        return position;
    }
    const glm::vec3& GetScale(){
        return scale;
    }
    const glm::vec3& GetRotation(){
        return rotation;
    }
    glm::mat4 GetModelMatrix(){
        return modelMatrix;
    }

    void SetPos(glm::vec3 pos){
        position = pos;
        UpdateModelMatrix();
    }
    void SetScale(glm::vec3 scale){
        this->scale = scale;
        UpdateModelMatrix();
    }
    void SetRotation(glm::vec3 rotation){
        this->rotation = rotation;
        UpdateModelMatrix();
    }

    void Move(glm::vec3 dPosition)
    {
        position += dPosition;
        UpdateModelMatrix();
    }
    void Rotate(glm::vec3 dAngle)
    {
        rotation += dAngle;
        UpdateModelMatrix();
    }
    void Scale(glm::vec3 dScale)
    {
        scale += dScale;
        UpdateModelMatrix();
    }


private:
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale   {1, 1, 1};
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    void UpdateModelMatrix(){
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotation.x, {1, 0, 0});
        modelMatrix = glm::rotate(modelMatrix, rotation.y, {0, 1, 0});
        modelMatrix = glm::rotate(modelMatrix, rotation.z, {0, 0, 1});
    }
};

#endif // TRANSFORM_H
