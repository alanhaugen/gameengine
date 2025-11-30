#include "rigidbody.h"
#include "core/components/gameobject.h"

RigidBody::RigidBody(Terrain *inTerrain)
{
    name = "Rigid Body";

    terrain = inTerrain;
}

void RigidBody::Update(float deltaTime)
{
    Update(nullptr, deltaTime);
}

void RigidBody::Update(VisualObject *mesh, float deltaTime)
{
    glm::vec3 pos;

    if (mesh == nullptr)
    {
        pos = gameObject->GetPosition();
    }
    else
    {
        pos = mesh->GetPosition();
    }

    velocity += (terrain->GetNormal(pos) / 500.0f) * deltaTime;
    velocity -= velocity * terrain->GetFriction(pos) * deltaTime;
    velocity.y = 0.0f;

    pos += velocity;
    pos.y = terrain->GetHeightAt(pos) + 1.0f;

    if (glm::length(velocity) > 0.0001f)
    {
        glm::vec3 rollVector = glm::normalize(glm::cross(glm::normalize(velocity), terrain->GetNormal(pos)));

        if (glm::length(rollVector) > 0.0001f)
        {
            if (gameObject)
            {
                gameObject->Rotate((glm::length(velocity)), rollVector);
            }
        }
    }

    if (mesh == nullptr)
    {
        gameObject->SetPosition(pos);
    }
    else
    {
        mesh->SetPosition(pos);
    }
}
