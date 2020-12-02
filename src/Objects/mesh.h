#ifndef MESH_H
#define MESH_H

#include "transform.h"

struct Color{
    float r, g, b;
};

class Mesh{
public:
    virtual ~Mesh(){};
    virtual void Draw() = 0;
    virtual void Update(){};

    Color color{1.f, 1.f, 1.f};
    Transform transform;

};

#endif // MESH_H
