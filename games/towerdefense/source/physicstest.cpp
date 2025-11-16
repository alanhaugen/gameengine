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
    first->AddComponent(new SphereCollider(first));
    first->SetPosition(glm::vec3(1, 0, -5));

    second = new GameObject("Second");
    second->AddComponent(new Sphere);
    second->AddComponent(new SphereCollider(second));
    second->SetPosition(glm::vec3(-1, 0, -5));

    renderer->SetClearColor(0, 0, 0);
}

void PhysicsTest::Update()
{
    if (input.Held(input.Key.D))
    {
        first->Translate(glm::vec3(0.01f,0,0));
    }
    if (input.Held(input.Key.A))
    {
        first->Translate(glm::vec3(-0.01f,0,0));
    }

    if (physics->isColliding(first))
    {
        first->Hide();
    }
    else
    {
        first->Show();
    }
}

void PhysicsTest::Clean()
{
}
