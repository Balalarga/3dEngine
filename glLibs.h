#ifndef GLLIBS_H
#define GLLIBS_H

#include <SDL2/SDL.h>
#ifdef _WIN32
    #include <glm/vec4.hpp>
    #include <glm/vec2.hpp>
    #include <GLEW/glew.h>r
#else
    #include <include/glm/vec4.hpp>
    #include <include/glm/vec2.hpp>
    #include <include/GLEW/glew.h>
#endif

#endif // GLLIBS_H
