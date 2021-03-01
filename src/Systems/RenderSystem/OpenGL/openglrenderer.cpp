#include "openglrenderer.h"
#include "Systems/FileSystem/filesystem.h"
#include "Systems/objectsystem.h"
#include "Utils/utils.h"
#include "openglshader.h"

OpenGLRenderer::OpenGLRenderer(std::string title, glm::ivec2 windowSize):
    BaseRenderer(title, windowSize)
{
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::string err = "Unable to init SDL: ";
        err += SDL_GetError();
        throw err;
    }

    unsigned windowFlags = SDL_WINDOW_OPENGL;
    if(windowSize.x == 0 &&
            windowSize.y == 0)
    {
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    }

    //SDL_SetRelativeMouseMode(SDL_TRUE);

    window = SDL_CreateWindow(windowTitle.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowSize.x, windowSize.y,
                              windowFlags);
    if(!window)
    {
        std::string err = "Unable to create window: ";
        err += SDL_GetError();
        throw err;
    }

    context = SDL_GL_CreateContext(window);
    if(!context)
    {
        std::string err = "Unable to create opengl context: ";
        err += SDL_GetError();
        throw err;
    }

    glewExperimental = GL_TRUE;
    if(glewInit()){
        std::string err = "Unable to init glew: ";
        throw err;
    }

    const unsigned char* rendererName = glGetString(GL_RENDERER);
    const unsigned char* glVersion = glGetString(GL_VERSION);
    cout<<"Renderer: "<<rendererName<<endl;
    cout<<"OpenGL version supported: "<<glVersion<<endl;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_FLAT);

    viewMatrix = glm::lookAt(glm::fvec3(0.0f, 0.0f, 2.5f),
                             glm::fvec3(0.0f, 0.0f, 0.0f),
                             glm::fvec3(0.0f, -1.0f, 0.0f)
                             );
}

OpenGLRenderer::~OpenGLRenderer()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void OpenGLRenderer::SwapBuffers() const
{
    SDL_GL_SwapWindow(window);
}

void OpenGLRenderer::UpdateViewMatrix(const glm::fmat4 view)
{
    viewMatrix = view;
}

void OpenGLRenderer::FrameUpdate(const ObjectDescriptor& desc, const glm::fmat4& modelMatrix) const
{
    glBindVertexArray(desc.vertexArrayObject);
    desc.shader->Bind();

    desc.shader->SetMat4("model", modelMatrix);
    desc.shader->SetMat4("view", viewMatrix);
    desc.shader->SetVec3("color", desc.color);
    desc.shader->SetVec3("ambientColor", ObjectSystem::Instance().ambientColor);
    if(ObjectSystem::Instance().mainLight)
    {
        desc.shader->SetVec3("diffuseColor", ObjectSystem::Instance().mainLight->color);
        desc.shader->SetVec3("diffusePos", ObjectSystem::Instance().mainLight->transform.GetPos());
    }

    GLenum mode = desc.drawType == DrawType::TRIANGLES ? GL_TRIANGLES : GL_QUADS;

    glDrawElements(mode, desc.vertexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    desc.shader->Unbind();
}

void OpenGLRenderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

ObjectDescriptor OpenGLRenderer::CreateDescriptor(MeshData& data) const
{
    GLuint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 data.vertices.size()*sizeof(Vertex),
            &data.vertices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    GLuint ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 data.indices.size()*sizeof(data.indices[0]),
            &data.indices.front(), GL_STATIC_DRAW);


    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    if(!data.vShaderPath.empty())
        vertexShaderSource = FileSystem::ReadFile(data.vShaderPath).c_str();
    else
    {
        vertexShaderSource = R"(
#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec3 oNormal;
out vec3 oFragPos;

void main() {
   gl_Position = projection * view * model * vec4(pos, 1.0f);
   oFragPos = vec3(model * vec4(pos, 1.0));
   oNormal = normal;
}


                             )";
    }

    if(!data.fShaderPath.empty())
        fragmentShaderSource = FileSystem::ReadFile(data.fShaderPath).c_str();
    else
    {
        fragmentShaderSource = R"(
#version 410

in vec3 fragPos;
in vec3 normal;

uniform vec3 color;
uniform vec3 lightColor;

out vec4 frag_color;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = ambient * color;
    frag_color = vec4(result, 1.0);
}

                               )";
    }

    ObjectDescriptor desc;
    desc.vertexCount = data.indices.size();
    desc.vertexArrayObject = vertexArrayObject;
    desc.drawType = data.drawType;
    desc.color = data.color;
    desc.shader = new OpenglShader({{ShaderType::Vertex, vertexShaderSource},
                                    {ShaderType::Fragment, fragmentShaderSource}});

    glm::fmat4 projection = glm::perspective(
                80.f,
                windowSize.x/windowSize.y,
                0.1f, 100.0f);


    desc.shader->SetMat4("projection", projection);

    return desc;
}

void OpenGLRenderer::DeleteDescriptor(const ObjectDescriptor &desc) const
{
    glDeleteProgram(desc.shader->GetId());
    glDeleteVertexArrays(1, &desc.vertexArrayObject);

    delete desc.shader;
}

void OpenGLRenderer::ClearColorChanged()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
}
