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

    glDrawElements(GL_TRIANGLES, desc.vertexCount, GL_UNSIGNED_INT, 0);

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


    unsigned shaderProgram;

    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    if(!data.vertexShaderPath.empty())
        vertexShaderSource = FileSystem::readFile(data.vertexShaderPath).c_str();
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
        fragmentShaderSource = FileSystem::readFile(data.fragmentShaderPath).c_str();
    else
    {
        fragmentShaderSource = "#version 410\n"
                               "out vec4 frag_colour;\n"
                               "void main() {\n"
                               "frag_colour = vec4(0.8, 0.8, 0.8, 1.0);\n"
                               "}";
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragmentShader);

    ObjectDescriptor desc;
    desc.vertexCount = data.indices.size();
    desc.vertexArrayObject = vertexArrayObject;
    if(!checkShader(vertexShader) || !checkShader(fragmentShader)){
        return desc;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    desc.shaderProgram = shaderProgram;

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.5f));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 2.0),
                                 glm::vec3(0.0, 0.0, 0.0),
                                 glm::vec3(0.0, -1.0, 0.0)
                                 );
    glm::mat4 projection = glm::perspective(
                60.f,
                16/9.f,
                0.1f, 10.0f);

    const char* uniform_name;
    uniform_name = "model";
    int uniform_model = glGetUniformLocation(desc.shaderProgram, uniform_name);
    uniform_name = "view";
    int uniform_view = glGetUniformLocation(desc.shaderProgram, uniform_name);
    uniform_name = "projection";
    int uniform_proj = glGetUniformLocation(desc.shaderProgram, uniform_name);
    cout << "model " << uniform_model << endl;
    cout << "view " << uniform_view << endl;
    cout << "projection " << uniform_proj << endl;

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
    glUseProgram(0);

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
