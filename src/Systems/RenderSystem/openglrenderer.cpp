#include "openglrenderer.h"
#include "Systems/FileSystem/filesystem.h"
#include "Utils/utils.h"
#include "Shader/openglshader.h"

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

    //    SDL_SetRelativeMouseMode(SDL_TRUE);

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
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

void OpenGLRenderer::Draw(const ObjectDescriptor& desc, const glm::fmat4& modelMatrix) const
{
    desc.shader->SetMat4("model", modelMatrix);
    desc.shader->SetMat4("view", viewMatrix);
    desc.shader->SetVec3("color", desc.color);

    desc.shader->Bind();
    glBindVertexArray(desc.vertexArrayObject);

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
                 data.verteces.size()*sizeof(data.verteces[0]),
            &data.verteces.front(), GL_STATIC_DRAW);

    GLuint ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 data.indices.size()*sizeof(data.indices[0]),
            &data.indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    if(!data.vertexShaderPath.empty())
        vertexShaderSource = FileSystem::ReadFile(data.vertexShaderPath).c_str();
    else
    {
        vertexShaderSource = "#version 410\n"
                             "uniform mat4 view;\n"
                             "uniform mat4 model;\n"
                             "uniform mat4 projection;\n"
                             "in vec3 vp;\n"
                             "void main() {\n"
                             "gl_Position = projection * view * model * vec4(vp, 1.0);\n"
                             "}";
    }

    if(!data.fragmentShaderPath.empty())
        fragmentShaderSource = FileSystem::ReadFile(data.fragmentShaderPath).c_str();
    else
    {
        fragmentShaderSource = R"(
                               #version 410
                               uniform vec3 color;
                               out vec4 frag_color;
                               void main() {
                               frag_color = vec4(color, 1.0);
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
                16/9.f,
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
