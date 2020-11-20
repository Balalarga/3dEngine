#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "mesh.h"
#include <glm/vec3.hpp>

class CubeMesh: public Mesh
{
public:
    CubeMesh(int size, glm::vec3 pos = {0, 0, 0});
    void draw() override;

private:
    glm::vec3 pos = {0, 0, 7};
    int size = 1;
};

#endif // CUBEMESH_H
