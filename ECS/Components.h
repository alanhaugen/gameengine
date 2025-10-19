#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> //for tranlate, rotate, scale

//Need namespace, since we start to get naming collisions with other code
namespace gea {

//Add new component types here - Extended for tower defense (My addition: Movement, Health, Tower, Enemy, Projectile and AI)
enum class ComponentTypes
{
    Transform,
    Model,
    Material,
    Movement,
    Health,
    Tower,
    Enemy,
    Projectile,
    RenderComponent,
    AI,
    Sound
};

//Below are examples of actual components
//Systems need each component to know what entity it belongs to
struct AIComponent
{
    float mDetectionRange{ 12.0f };
    short mTargetEntityID{ -1 };  // Usually player at center
    enum AIState { IDLE, MOVING_TO_PLAYER, ATTACKING_PLAYER } mState{ MOVING_TO_PLAYER };
    short mEntityID{ -1 };
};

struct EnemyComponent
{
    float mDamageToPlayer{ 10.0f };
    bool mReachedPlayer{ false };
    enum SpawnDirection { NORTH, EAST, SOUTH, WEST } mSpawnSide{ NORTH };
    short mEntityID{ -1 };
};

struct HealthComponent
{
    float mCurrentHealth{ 100.0f };
    float mMaxHealth{ 100.0f };
    bool mIsAlive{ true };
    short mEntityID{ -1 };
};

struct MaterialComponent
{
    short mTexture{-1};        //index into array of all textures loaded
    short mEntityID{-1};
};

struct ModelComponent
{
    short mModel{-1};        //index into array of all meshes loaded
    short mEntityID{-1};
};

// Added more components for tower Defense specific components - from AkashECS
struct MovementComponent
{
    glm::vec3 mVelocity{ 0.0f, 0.0f, 0.0f };
    float mSpeed{ 3.0f };
    glm::vec3 mDirection{ 0.0f, 0.0f, -1.0f }; // Default toward center
    bool mIsMoving{ true };
    short mEntityID{ -1 };
};

struct ProjectileComponent
{
    float mDamage{ 25.0f };
    float mLifetime{ 5.0f };
    bool mIsAirborne{ true };
    glm::vec3 mGravity{ 0.0f, -9.8f, 0.0f };
    glm::vec3 mVelocity{ 0.0f, 0.0f, 0.0f }; // <-- added velocity member
    short mTargetEntityID{ -1 };
    short mEntityID{ -1 };
};

//MeshIndex, TextureIndex, EntityID
struct RenderComponent
{
    int meshIndex{-1};
    int textureIndex{-1};
    int mEntityID{-1};
};

typedef unsigned int ALuint;    //also defined in AL/al.h but did not want to include it here
struct SoundComponent
{
    ALuint mSoundSource{0};
    ALuint mSoundBuffer{0};
    short mEntityID{-1};
};

struct TowerComponent
{
    float mRange{ 15.0f };
    float mFireRate{ 2.0f };  // shots per second
    float mLastFireTime{ 0.0f };
    bool mCanFire{ true };
    enum TowerType { PROJECTILE, BOULDER } mType{ PROJECTILE };
    short mEntityID{ -1 };
};

struct TransformComponent
{
    glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };
    glm::vec3 mRotation{ 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale{ 1.0f, 1.0f, 1.0f };
    short mEntityID{ -1 };

    TransformComponent(short id) : mEntityID{id}{};
    glm::mat4 GetModelMatrix()
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

} //namespace gea

#endif // COMPONENTS_H
