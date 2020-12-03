#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "gameobject.h"
#include "glIncludes.h"

class CubeMesh: public GameObject
{
public:
    CubeMesh(int size, glm::vec3 pos = {0, 0, 0});
    void Draw() override;

private:
    glm::vec3 pos;
    int size = 1;
};

#endif // CUBEMESH_H
