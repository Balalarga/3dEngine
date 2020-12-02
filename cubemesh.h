#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "mesh.h"
#include "glIncludes.h"

class CubeMesh: public Mesh
{
public:
    CubeMesh(int size, glm::vec3 pos = {0, 0, 0});
    void Draw() override;

private:
    glm::vec3 pos;
    int size = 1;
};

#endif // CUBEMESH_H
