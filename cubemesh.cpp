#include "cubemesh.h"
#include <GL/glew.h>
#include <GL/gl.h>

CubeMesh::CubeMesh(int size, glm::vec3 pos):
    pos(pos),
    size(size)
{
}

void CubeMesh::draw()
{
    glTranslatef(pos.x, pos.y, pos.y);	// Сдвинуть вглубь экрана

    //    glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
    //    glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
    //    glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z

    glBegin(GL_QUADS);					// Рисуем куб

    glColor3f(0.0f, 1.0f, 0.0f);		// Синяя сторона (Верхняя)
    glVertex3f( size, size, -size);		// Верхний правый угол квадрата
    glVertex3f(-size, size, -size);		// Верхний левый
    glVertex3f(-size, size,  size);		// Нижний левый
    glVertex3f( size, size,  size);		// Нижний правый

    glVertex3f( size, -size,  size);	// Верхний правый угол квадрата
    glVertex3f(-size, -size,  size);	// Верхний левый
    glVertex3f(-size, -size, -size);	// Нижний левый
    glVertex3f( size, -size, -size);	// Нижний правый

    glVertex3f( size,  size, size);		// Верхний правый угол квадрата
    glVertex3f(-size,  size, size);		// Верхний левый
    glVertex3f(-size, -size, size);		// Нижний левый
    glVertex3f( size, -size, size);		// Нижний правый

    glVertex3f( size, -size, -size);	// Верхний правый угол квадрата
    glVertex3f(-size, -size, -size);	// Верхний левый
    glVertex3f(-size,  size, -size);	// Нижний левый
    glVertex3f( size,  size, -size);	// Нижний правый

    glVertex3f(-size,  size,  size);	// Верхний правый угол квадрата
    glVertex3f(-size,  size, -size);	// Верхний левый
    glVertex3f(-size, -size, -size);	// Нижний левый
    glVertex3f(-size, -size,  size);	// Нижний правый

    glVertex3f( size,  size, -size);	// Верхний правый угол квадрата
    glVertex3f( size,  size,  size);	// Верхний левый
    glVertex3f( size, -size,  size);	// Нижний левый
    glVertex3f( size, -size, -size);	// Нижний правый

    glEnd();							// Закончили квадраты

}
