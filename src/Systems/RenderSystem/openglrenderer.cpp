#include "openglrenderer.h"
#include "Systems/FileSystem/filesystem.h"
#include "Utils/utils.h"

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
}

OpenGLRenderer::~OpenGLRenderer()
{
    for(auto i: descriptors){
        glDeleteProgram(i.shaderProgram);
        glDeleteVertexArrays(1, &i.vertexArrayObject);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void OpenGLRenderer::SwapBuffers() const
{
    SDL_GL_SwapWindow(window);
}

void OpenGLRenderer::Draw(const ObjectDescriptor& desc, const glm::mat4& modelMatrix) const
{
    glUseProgram(desc.shaderProgram);
    int uniform_model = glGetUniformLocation(desc.shaderProgram, "model");
    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glBindVertexArray(desc.vertexArrayObject);

    GLenum mode = desc.drawType == DrawType::TRIANGLES ? GL_TRIANGLES : GL_QUADS;

    glDrawElements(mode, desc.vertexCount, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
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

    const char* vertexShaderSource;
    const char* fragmentShaderSource;
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
        fragmentShaderSource = "#version 410\n"
                               "out vec4 frag_colour;\n"
                               "void main() {\n"
                               "frag_colour = vec4(0.8, 0.8, 0.8, 1.0);\n"
                               "}";
    }

    unsigned shaderProgram = glCreateProgram();
    bool ok = AddShader(shaderProgram, GL_VERTEX_SHADER, vertexShaderSource);
    ok &= AddShader(shaderProgram, GL_FRAGMENT_SHADER, fragmentShaderSource);
    if(!ok){
        cout<<"Couldn't create shaders\n";
        glDeleteProgram(shaderProgram);
        return ObjectDescriptor();
    }else
        glLinkProgram(shaderProgram);

    ObjectDescriptor desc;
    desc.vertexCount = data.indices.size();
    desc.vertexArrayObject = vertexArrayObject;
    desc.drawType = data.drawType;
    desc.shaderProgram = shaderProgram;

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.5f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, -1.0f, 0.0f)
                                 );
    glm::mat4 projection = glm::perspective(
                60.f,
                16/9.f,
                0.1f, 100.0f);

    const char* uniform_name;
    uniform_name = "view";
    int uniform_view = glGetUniformLocation(desc.shaderProgram, uniform_name);
    uniform_name = "projection";
    int uniform_proj = glGetUniformLocation(desc.shaderProgram, uniform_name);

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
    glUseProgram(0);

    return desc;
}

void OpenGLRenderer::ClearColorChanged()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
}


bool OpenGLRenderer::CheckShader(GLint shader) const
{
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
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

bool OpenGLRenderer::AddShader(GLuint program, GLenum type, const char *source) const
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    if(!CheckShader(shader)){
        glDeleteShader(shader);
        return false;
    }
    glAttachShader(program, shader);
    return true;
}
