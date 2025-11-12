#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //for tranlate, rotate, scale

//Need namespace, since we start to get naming collisions with other code
namespace gea {

// Using a namespace to wrap the Component enum instead of using a class
// This way we can decide how big the enum will be!
namespace ComponentTypes
{

    //Add new component types here - Extended for tower defense (My addition: Movement, Health, Tower, Enemy, Projectile and AI)
    // These are now only 1 byte!
    enum Components : uint8_t
    {
        None,
        Transform,
        Model,
        Material,
        Movement,
        Health,
        Tower,
        Enemy,
        Projectile,
        Render,
        AI,
        Sound
    };
}

// ComponentBase makes it possible for the Entity to have ONE vector with all its components
struct ComponentBase
{
    short mEntityID{ -1 };
    ComponentTypes::Components mComponentType{ComponentTypes::None};
};

// MeshIndex, TextureIndex, EntityID
// This will actually result in the Renderer have to follow the meshIndex to fetch the data it needs
// So this should probably be refactored
struct RenderComponent : public ComponentBase
{
    int meshIndex{-1};
    int textureIndex{-1};
    RenderComponent(int meshIndexIn, int textureIndexIn, short id) : meshIndex{meshIndexIn}, textureIndex{textureIndexIn},
        ComponentBase{id, ComponentTypes::Render} {};
};

struct TransformComponent : public ComponentBase
{
    glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };
    glm::vec3 mRotation{ 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale{ 1.0f, 1.0f, 1.0f };

    TransformComponent(short id) : ComponentBase{id, ComponentTypes::Transform}
    { };

    glm::mat4 getModelMatrix()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, mPosition);
        model = glm::rotate(model, glm::radians(mRotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(mRotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(mRotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, mScale);
        return model;
    }
};

//Below are examples of actual components
//Systems need each component to know what entity it belongs to
struct AIComponent : public ComponentBase
{
    float mDetectionRange{ 12.0f };
    short mTargetEntityID{ -1 };  // Usually player at center
    enum AIState { IDLE, MOVING_TO_PLAYER, ATTACKING_PLAYER } mState{ MOVING_TO_PLAYER };
};

struct EnemyComponent : public ComponentBase
{
    float mDamageToPlayer{ 10.0f };
    bool mReachedPlayer{ false };
    enum SpawnDirection { NORTH, EAST, SOUTH, WEST } mSpawnSide{ NORTH };
};

struct HealthComponent : public ComponentBase
{
    float mCurrentHealth{ 100.0f };
    float mMaxHealth{ 100.0f };
    bool mIsAlive{ true };
};

struct MaterialComponent : public ComponentBase
{
    short mTexture{-1};        //index into array of all textures loaded
};

struct ModelComponent : public ComponentBase
{
    short mModel{-1};        //index into array of all meshes loaded
};

// Added more components for tower Defense specific components - from AkashECS
struct MovementComponent : public ComponentBase
{
    glm::vec3 mVelocity{ 0.0f, 0.0f, 0.0f };
    float mSpeed{ 3.0f };
    glm::vec3 mDirection{ 0.0f, 0.0f, -1.0f }; // Default toward center
    bool mIsMoving{ true };
};

struct ProjectileComponent : public ComponentBase
{
    float mDamage{ 25.0f };
    float mLifetime{ 5.0f };
    bool mIsAirborne{ true };
    glm::vec3 mGravity{ 0.0f, -9.8f, 0.0f };
    glm::vec3 mVelocity{ 0.0f, 0.0f, 0.0f }; // <-- added velocity member
    short mTargetEntityID{ -1 };
};

typedef unsigned int ALuint;    //also defined in AL/al.h but did not want to include it here
struct SoundComponent : public ComponentBase
{
    ALuint mSoundSource{0};
    ALuint mSoundBuffer{0};
};

struct TowerComponent : public ComponentBase
{
    float mRange{ 15.0f };
    float mFireRate{ 2.0f };  // shots per second
    float mLastFireTime{ 0.0f };
    bool mCanFire{ true };
    enum TowerType { PROJECTILE, BOULDER } mType{ PROJECTILE };
};


} //namespace gea

#endif // COMPONENTS_H
