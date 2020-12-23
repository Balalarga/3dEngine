#ifndef BASESHADER_H
#define BASESHADER_H

#include <string>
#include <glm/glm.hpp>
#include <map>

enum class ShaderType{
    Vertex, Fragment
};

class BaseShader
{
public:
    BaseShader(){}
    int GetId(){ return id; };

    virtual ~BaseShader(){}

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void SetMat4(const std::string& name, glm::mat4 val) = 0;
    virtual void SetMat3(const std::string& name, glm::mat3 val) = 0;
    virtual void SetVec4(const std::string& name, glm::vec4 val) = 0;
    virtual void SetVec3(const std::string& name, glm::vec3 val) = 0;
    virtual void SetVec2(const std::string& name, glm::vec2 val) = 0;
    virtual void SetValue(const std::string& name, float val) = 0;

protected:
    int id;
};

#endif // BASESHADER_H
