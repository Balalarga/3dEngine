#ifndef BASERENDERER_H
#define BASERENDERER_H

#include <string>
#include <glm/glm.hpp>
#include <list>
#include <vector>

enum class DrawType{
    TRIANGLES,
    QUADS
};

struct MeshData{
    std::vector<glm::vec3> verteces;
    std::vector<unsigned> indices;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    DrawType drawType = DrawType::TRIANGLES;
};

struct ObjectDescriptor{
    unsigned vertexArrayObject = 0;
    unsigned shaderProgram = 0;
    unsigned vertexCount = 0;
    DrawType drawType = DrawType::TRIANGLES;
};

class BaseRenderer
{

public:
    void SetClearColor(glm::vec3 c);
    BaseRenderer(std::string title, glm::ivec2 windowSize);

    virtual ~BaseRenderer();
    virtual void Clear() const = 0;
    virtual void SwapBuffers() const = 0;
    virtual void Draw(const ObjectDescriptor& desc, const glm::mat4 &modelMatrix) const = 0;
    virtual ObjectDescriptor CreateDescriptor(MeshData &data) const = 0;


protected:
    std::string windowTitle;
    glm::vec2 windowSize;
    glm::vec3 clearColor{0.f, 0.f, 0.f};
    std::list<ObjectDescriptor> descriptors;

    virtual void ClearColorChanged()
    {

    };
};

#endif // BASERENDERER_H
