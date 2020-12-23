#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include "../baseshader.h"
#include <map>

class OpenglShader: public BaseShader
{
public:
    OpenglShader(std::map<ShaderType, std::string> shaders);

    void Bind();
    void Unbind();
    void SetMat4(const std::string& name, glm::mat4 val);
    void SetMat3(const std::string& name, glm::mat3 val);
    void SetVec4(const std::string& name, glm::vec4 val);
    void SetVec3(const std::string& name, glm::vec3 val);
    void SetVec2(const std::string& name, glm::vec2 val);
    void SetValue(const std::string& name, float val);

protected:
    bool CheckProgram() const;
    bool CheckShader(unsigned shader) const;
};

#endif // OPENGLSHADER_H
