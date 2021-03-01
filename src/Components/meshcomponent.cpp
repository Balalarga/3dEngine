#include "meshcomponent.h"
#include "Objects/gameobject.h"
#include "Utils/utils.h"

MeshComponent::MeshComponent(MeshData& data):
    data(data)
{
    descriptor = RenderSystem::Instance().GetRender()->CreateDescriptor(data);
}

MeshComponent::~MeshComponent()
{
    RenderSystem::Instance().GetRender()->DeleteDescriptor(descriptor);
}

void MeshComponent::FrameUpdate()
{
    RenderSystem::Instance().GetRender()->FrameUpdate(descriptor, parent->transform.GetModelMatrix());
}

