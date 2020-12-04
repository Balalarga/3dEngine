#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "glIncludes.h"
#include "component.h"
#include <vector>

using std::vector;

class MeshComponent: public Component
{
public:
    MeshComponent(vector<glm::vec3> vertecies);
    void Draw() override;

    vector<glm::vec3> vertecies;
};

#endif // MESHCOMPONENT_H
