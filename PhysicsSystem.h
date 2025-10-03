#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "System.h"
#include <glm/glm.hpp>

namespace gea
{
    class Engine;

    class PhysicsSystem : public System
    {
    public:
        PhysicsSystem(Engine* engine);

        void update(float deltaTime) override;

        void SetGravity(const glm::vec3& gravity) { mGravity = gravity; }
        glm::vec3 GetGravity() const { return mGravity; }

    private:
        Engine* engine;
        glm::vec3 mGravity {0.0f, 9.81f, 0.0f};

        void ApplyGravity(float deltaTime);
        void CollisionDetection();
    };
}
#endif // PHYSICSSYSTEM_H
