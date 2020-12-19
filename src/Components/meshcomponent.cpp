#include "meshcomponent.h"
#include "Objects/gameobject.h"
#include "Utils/utils.h"

MeshComponent::MeshComponent(MeshData& data)
{
    verteces = data.verteces;
    descriptor = RenderSystem::Instance().GetRender()->CreateDescriptor(data);
}

MeshComponent::~MeshComponent()
{
    RenderSystem::Instance().GetRender()->DeleteDescriptor(descriptor);
}

void MeshComponent::Draw()
{
    RenderSystem::Instance().GetRender()->Draw(descriptor, parent->transform.GetModelMatrix());
}

