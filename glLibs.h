#ifndef GLLIBS_H
#define GLLIBS_H

#include <SDL2/SDL.h>
#ifdef _WIN32
    #include <glm/glm.hpp>
    #include <glm/matrix.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <GLEW/glew.h>
    #include <GL/gl.h>
#else
    #include <include/glm/vec4.hpp>
    #include <include/glm/vec2.hpp>
    #include <include/GLEW/glew.h>
#endif

#endif // GLLIBS_H
