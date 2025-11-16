#include "physicstest.h"
#include "core/components/sphere.h"
#include "core/components/spherecollider.h"

PhysicsTest::PhysicsTest()
{
}

void PhysicsTest::Init()
{
    first = new GameObject("First");
    first->AddComponent(new Sphere);
    first->AddComponent(new SphereCollider);
    first->SetPosition(glm::vec3(1, 0, -5));

    second = new GameObject("Second");
    second->AddComponent(new Sphere);
    second->AddComponent(new SphereCollider);
    second->SetPosition(glm::vec3(-1, 0, -5));

    renderer->SetClearColor(0, 0, 0);
}

void PhysicsTest::Update()
{
}

void PhysicsTest::Clean()
{
}
