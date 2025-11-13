#ifndef AAPHYSICS_H
#define AAPHYSICS_H

#include <glm/glm.hpp>
#include "../physics.h"
#include "vector"

class AAPhysics : public Physics
{
public:
    AAPhysics();

    bool Init() override;
    void Update() override;

    Collider* CreateCollider(int response) override;

    std::vector<Collider*> sceneColliders;

private:
    void SetGravity(const glm::vec3& gravity) { mGravity = gravity; }
    glm::vec3 GetGravity() const { return mGravity; }

    glm::vec3 mGravity {0.0f, 9.81f, 0.0f};

    void ApplyGravity(float deltaTime = 1.0f);
    void CollisionDetection();
    void CollisionResponse(Collider* colliderA, Collider* colliderB);
    void CalculateImpulses(float massA, float massB, float speedA, float speedB);
};

#endif // AAPHYSICS_H
