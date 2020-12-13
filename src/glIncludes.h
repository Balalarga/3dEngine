#ifndef GLINCLUDES_H
#define GLINCLUDES_H

#ifdef WIN32
    #include <GLEW/glew.h>
#else
    #include <GL/glew.h>
#endif

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif // GLINCLUDES_H
