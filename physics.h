#ifndef PHYSICS_H
#define PHYSICS_H


class Physics{
public:
    float velocity{1.f};
    float acceleration{0.f};
    void Accelerate(float dAccelerate){
        acceleration+=dAccelerate;
    }
};

#endif // PHYSICS_H
