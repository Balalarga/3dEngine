#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "..//baserenderer.h"
#include "glIncludes.h"

class OpenGLRenderer: public BaseRenderer
{
public:
    OpenGLRenderer(std::string title, glm::ivec2 windowSize);
    ~OpenGLRenderer();

    void Clear() const override;
    void SwapBuffers() const override;
    void UpdateViewMatrix(const glm::fmat4 view) override;
    void FrameUpdate(const ObjectDescriptor& desc, const glm::fmat4 &modelMatrix) const override;

    ObjectDescriptor CreateDescriptor(MeshData &data) const override;
    void DeleteDescriptor(const ObjectDescriptor& desc) const override;


protected:
    void ClearColorChanged() override;

private:
    SDL_Window* window;
    SDL_GLContext context;
    glm::fmat4 viewMatrix;
};

#endif // OPENGLRENDERER_H
