#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "baserenderer.h"
#include "glIncludes.h"

class OpenGLRenderer: public BaseRenderer
{
public:
    OpenGLRenderer(std::string title, glm::ivec2 windowSize);
    ~OpenGLRenderer();

    void Clear() const override;
    void SwapBuffers() const override;
    void UpdateViewMatrix(const glm::mat4 view) override;
    void Draw(const ObjectDescriptor& desc, const glm::mat4 &modelMatrix) const override;

    ObjectDescriptor CreateDescriptor(MeshData &data) const override;

protected:
    void ClearColorChanged() override;
    bool CheckShader(GLint shader) const;
    bool AddShader(GLuint program, GLenum type, const char* source) const;

private:
    SDL_Window* window;
    SDL_GLContext context;
    glm::mat4 viewMatrix;
};

#endif // OPENGLRENDERER_H
