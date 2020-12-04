#include "meshcomponent.h"
#include "Objects/gameobject.h"

MeshComponent::MeshComponent(vector<glm::vec3> vertecies):
    vertecies(vertecies)
{
}

void MeshComponent::Draw()
{
    assert(vertecies.size()%3 == 0);
    glBegin(GL_TRIANGLES);
    for(auto i: vertecies){
        glVertex3f(i.x, i.y, i.z);
    }

    glEnd();
}
