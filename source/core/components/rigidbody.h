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
    void Update(float deltaTime);
    void Update(VisualObject* mesh, float deltaTime);
};

#endif // RIGIDBODY_H
