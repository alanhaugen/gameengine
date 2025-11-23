#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "core/components/component.h"
#include "core/components/terrain.h"

class RigidBody : public Component
{
public:
    Terrain* terrain;

    glm::vec3 velocity;
    float mass;

    RigidBody(Terrain* inTerrain);
    void Update();
    void Update(VisualObject* mesh);
};

#endif // RIGIDBODY_H
