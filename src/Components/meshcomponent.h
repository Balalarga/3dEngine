#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "glIncludes.h"
#include "basecomponent.h"
#include <vector>
#include "Systems/RenderSystem/rendersystem.h"

using std::vector;

class MeshComponent: public Component
{
public:
    MeshComponent(MeshData &data);
    ~MeshComponent();
    void FrameUpdate() override;

    MeshData& data;
    ObjectDescriptor descriptor;
};

#endif // MESHCOMPONENT_H
