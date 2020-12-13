#include "rendersystem.h"
#include "Systems/systems.h"

RenderSystem* RenderSystem::selfInstance = nullptr;

RenderSystem &RenderSystem::Instance()
{
    if(!selfInstance)
        selfInstance = new RenderSystem();
    return *selfInstance;
}

BaseRenderer *RenderSystem::GetRender()
{
    return renderer.get();
}

RenderSystem::RenderSystem()
{

}
