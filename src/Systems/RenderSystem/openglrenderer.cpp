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
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void OpenGLRenderer::SwapBuffers() const
{
    SDL_GL_SwapWindow(window);
}

void OpenGLRenderer::Draw(const ObjectDescriptor& desc) const
{
    glUseProgram(desc.shaderProgram);
    glBindVertexArray(desc.vertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, desc.vertexCount);

    glUseProgram(0);
    glBindVertexArray(0);
}

void OpenGLRenderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

ObjectDescriptor OpenGLRenderer::CreateDescriptor(MeshData& data) const
{
    unsigned shaderProgram;
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 data.verteces.size()*sizeof(data.verteces[0]),
                 &data.verteces.front(),
                 GL_STATIC_DRAW);
    GLuint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    if(!data.vertexShaderPath.empty())
        vertexShaderSource = FileSystem::readFile(data.vertexShaderPath).c_str();
    else
    {
        vertexShaderSource = "#version 410\n"
                "in vec3 vp;\n"
                "void main() {\n"
                    "gl_Position = vec4(vp, 1.0);\n"
                "}";
    }

    if(!data.fragmentShaderPath.empty())
        fragmentShaderSource = FileSystem::readFile(data.fragmentShaderPath).c_str();
    else
    {
        fragmentShaderSource = "#version 410\n"
                "out vec4 frag_colour;\n"
                "void main() {\n"
                    "frag_colour = vec4(0.5, 0.0, 0.5, 1.0);\n"
                "}";
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragmentShader);

    ObjectDescriptor desc;
    desc.vertexCount = data.verteces.size();
    desc.vertexArrayObject = vertexArrayObject;
    if(!checkShader(vertexShader) || !checkShader(fragmentShader)){
        return desc;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    desc.shaderProgram = shaderProgram;
    return desc;
}

void OpenGLRenderer::clearColorChanged()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
}


bool OpenGLRenderer::checkShader(GLint shader) const
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
