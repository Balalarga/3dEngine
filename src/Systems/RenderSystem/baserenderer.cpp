#include "baserenderer.h"

BaseRenderer::BaseRenderer(std::string title, glm::ivec2 windowSize):
    windowTitle(title),
    windowSize(windowSize)
{

}

BaseRenderer::~BaseRenderer()
{

}

void BaseRenderer::SetClearColor(glm::vec3 c)
{
    clearColor = c;
    ClearColorChanged();
}
