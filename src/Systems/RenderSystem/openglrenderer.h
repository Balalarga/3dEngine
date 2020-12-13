#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "baserenderer.h"
#include "glIncludes.h"

class OpenGLRenderer: public BaseRenderer
{
public:
    OpenGLRenderer(std::string title, glm::ivec2 windowSize);
    ~OpenGLRenderer();
    void SwapBuffers() const override;
    void Draw(const ObjectDescriptor& desc) const override;
    void Clear() const override;
    ObjectDescriptor CreateDescriptor(MeshData &data) const override;

protected:
    void clearColorChanged() override;
    bool checkShader(GLint shader) const;

private:
    SDL_Window* window;
    SDL_GLContext context;
};

#endif // OPENGLRENDERER_H
