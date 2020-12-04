#include "gameobject.h"
#include "Components/component.h"

GameObject::~GameObject(){
    for(auto& pair: components){
        delete pair.second;
    }
};

void GameObject::Update(float dt){
    for(auto& pair: components){
        pair.second->Update(dt);
    }
};

void GameObject::Draw(){
    glPushMatrix();

    glTranslatef(transform.position.x,
                 transform.position.y,
                 transform.position.z);
    glRotatef(transform.rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(transform.rotation.z, 0.0f, 0.0f, 1.0f);

    glColor3f(color.r,
              color.g,
              color.b);

    for(auto& pair: components)
        pair.second->Draw();

    glPopMatrix();
};

void GameObject::Move(glm::vec3 dPosition){
    transform.position += dPosition;
}

void GameObject::Rotate(glm::vec3 dAngle){
    transform.rotation += dAngle;
}

void GameObject::Scale(glm::vec3 dScale){
    transform.scale += dScale;
}
