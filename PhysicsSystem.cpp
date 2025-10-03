#include "PhysicsSystem.h"
#include "Engine.h"
#include "Components.h"
#include <QDebug>

namespace gea
{
    PhysicsSystem::PhysicsSystem(Engine* engine) : engine(engine)
    {
        qDebug() << "Initialized PhysicsSystem.";
    }

    void PhysicsSystem::update(float deltaTime) {
        if (!engine) return;

        // Physics pipeline
        ApplyGravity(deltaTime);
        CollisionDetection();
    }
}
