#ifndef MESH_H
#define MESH_H

class Mesh{
public:
    virtual ~Mesh(){};
    virtual void draw() = 0;
    virtual void update(){};
};

#endif // MESH_H
