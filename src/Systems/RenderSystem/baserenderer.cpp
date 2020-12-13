#include "baserenderer.h"

BaseRenderer::BaseRenderer(std::string title, glm::ivec2 windowSize):
    windowTitle(title),
    windowSize(windowSize)
{

}

void BaseRenderer::SetClearColor(glm::vec3 c)
{
    clearColor = c;
    clearColorChanged();
}
