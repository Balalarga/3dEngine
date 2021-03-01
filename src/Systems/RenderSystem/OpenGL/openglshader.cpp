#include "openglshader.h"
#include "Utils/utils.h"
#include "glIncludes.h"

#include <vector>
using namespace std;

OpenglShader::OpenglShader(std::map<ShaderType, std::string> shaders)
{
    id = glCreateProgram();
    vector<unsigned> attachedShaders;
    GLenum type = 0;
    for(auto& i: shaders)
    {
        if(i.first == ShaderType::Vertex)
            type = GL_VERTEX_SHADER;
        else if(i.first == ShaderType::Fragment)
            type = GL_FRAGMENT_SHADER;

        unsigned shader = glCreateShader(type);
        const char* source = i.second.c_str();
        glShaderSource(shader, 1, &source, 0);
        glCompileShader(shader);
        if(!CheckShader(shader))
        {
            glDeleteShader(shader);
        }
        else
        {
            glAttachShader(id, shader);
            attachedShaders.push_back(shader);
        }
    }
    glLinkProgram(id);
    if(!CheckProgram())
    {
        cout<<"Shader program link error\n";
        for(auto& i: attachedShaders)
            glDetachShader(id, i);
    }
    for(auto& i: attachedShaders)
        glDeleteShader(i);
}

void OpenglShader::Bind()
{
    binded = true;
    glUseProgram(id);
}

void OpenglShader::Unbind()
{
    binded = false;
    glUseProgram(0);
}

void OpenglShader::SetMat4(const std::string &name, glm::mat4 val)
{
    if(!binded)
        Bind();
    int loc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
    if(!binded)
        Unbind();
}

void OpenglShader::SetMat3(const std::string &name, glm::mat3 val)
{
    if(!binded)
        Bind();
    int loc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(val));
    if(!binded)
        Unbind();
}

void OpenglShader::SetVec4(const std::string &name, glm::vec4 val)
{
    if(!binded)
        Bind();
    int loc = glGetUniformLocation(id, name.c_str());
    glUniform4fv(loc, 1, glm::value_ptr(val));
    if(!binded)
        Unbind();
}

void OpenglShader::SetVec3(const std::string &name, glm::vec3 val)
{
    if(!binded)
        Bind();
    int loc = glGetUniformLocation(id, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(val));
    if(!binded)
        Unbind();
}

void OpenglShader::SetVec2(const std::string &name, glm::vec2 val)
{
    if(!binded)
        Bind();
    int loc = glGetUniformLocation(id, name.c_str());
    glUniform2fv(loc, 1, glm::value_ptr(val));
    if(!binded)
        Unbind();
}

void OpenglShader::SetValue(const std::string &name, float val)
{
    if(!binded)
        Bind();
    int loc = glGetUniformLocation(id, name.c_str());
    glUniform1f(loc, val);

    if(!binded)
        Unbind();
}

bool OpenglShader::CheckShader(unsigned shader) const
{
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        cout<<"Shader error\n";
        for(auto i: errorLog)
        {
            cout<<i;
        }
        cout<<endl;

        glDeleteShader(shader);
        return false;
    }
    return true;
}


bool OpenglShader::CheckProgram() const
{
    GLint isLinked = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(id, maxLength, &maxLength, &errorLog[0]);
        cout<<"Program error\n";
        for(auto i: errorLog)
        {
            cout<<i;
        }
        cout<<endl;

        glDeleteProgram(id);
        return false;
    }
    return true;
}
