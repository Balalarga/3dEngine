#include "mesh.h"

Mesh::Mesh()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);


    glBindVertexArray(0);
}
