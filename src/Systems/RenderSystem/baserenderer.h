#ifndef BASERENDERER_H
#define BASERENDERER_H

#include <string>
#include <glm/glm.hpp>
#include <list>
#include <vector>
#include "baseshader.h"

enum class DrawType{
    TRIANGLES,
    QUADS
};

struct MeshData{
    std::vector<glm::fvec3> verteces;
    std::vector<unsigned> indices;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    glm::fvec3 color = {1.f, 1.f, 1.f};
    DrawType drawType = DrawType::TRIANGLES;
};

struct ObjectDescriptor{
    unsigned vertexArrayObject = 0;
    BaseShader* shader = 0;
    unsigned vertexCount = 0;
    DrawType drawType = DrawType::TRIANGLES;
    glm::fvec3 color;
};

class BaseRenderer
{

public:
    void SetClearColor(glm::fvec3 c);
    BaseRenderer(std::string title, glm::ivec2 windowSize);

    virtual ~BaseRenderer();

    virtual void Clear() const = 0;
    virtual void SwapBuffers() const = 0;
    virtual void UpdateViewMatrix(const glm::fmat4 view) = 0;
    virtual void FrameUpdate(const ObjectDescriptor& desc, const glm::fmat4 &modelMatrix) const = 0;
    virtual ObjectDescriptor CreateDescriptor(MeshData &data) const = 0;
    virtual void DeleteDescriptor(const ObjectDescriptor& desc) const = 0;

protected:
    std::string windowTitle;
    glm::vec2 windowSize;
    glm::fvec3 clearColor{0.f, 0.f, 0.f};

    virtual void ClearColorChanged()
    {

    };
};

#endif // BASERENDERER_H
