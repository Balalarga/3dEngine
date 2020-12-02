#ifndef CAMERA_H
#define CAMERA_H

#include "mesh.h"

class Camera: public Mesh
{
public:
    Camera();
    void Draw() override;


};

#endif // CAMERA_H
