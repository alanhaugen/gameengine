#ifndef COMPONENTS_H
#define COMPONENTS_H

//Sound
#ifdef _WIN32
#include <AL/al.h>
#include <AL/alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
//

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> //for tranlate, rotate, scale
#include <vector>


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

    struct AI
    {
        float mDetectionRange{ 12.0f };
        short mTargetEntityID{ -1 };  // Usually player at center
        enum AIState { IDLE, MOVING_TO_PLAYER, ATTACKING_PLAYER } mState{ MOVING_TO_PLAYER };
        short mEntityID{ -1 };
    };

    struct Enemy
    {
        float mDamageToPlayer{ 10.0f };
        bool mReachedPlayer{ false };
        enum SpawnDirection { NORTH, EAST, SOUTH, WEST } mSpawnSide{ NORTH };
        short mEntityID{ -1 };
    };

    struct Health
    {
        float mCurrentHealth{ 100.0f };
        float mMaxHealth{ 100.0f };
        bool mIsAlive{ true };
        short mEntityID{ -1 };
    };

    struct Material
    {
        short mTexture{-1};        //index into array of all textures loaded
        short mEntityID{-1};
    };

    struct Model
    {
        short mModel{-1};        //index into array of all meshes loaded
        short mEntityID{-1};
    };

    // Added more components for tower Defense specific components - from AkashECS
    struct Movement
    {
        glm::vec3 mVelocity{ 0.0f, 0.0f, 0.0f };
        float mSpeed{ 3.0f };
        glm::vec3 mDirection{ 0.0f, 0.0f, -1.0f }; // Default toward center
        bool mIsMoving{ true };
        short mEntityID{ -1 };
    };

    struct Projectile
    {
        float mDamage{ 25.0f };
        float mLifetime{ 5.0f };
        bool mIsAirborne{ true };
        glm::vec3 mGravity{ 0.0f, -9.8f, 0.0f };
        glm::vec3 mVelocity{ 0.0f, 0.0f, 0.0f }; // <-- added velocity member
        short mTargetEntityID{ -1 };
        short mEntityID{ -1 };
    };

    struct RenderComponent
    {
        RenderComponent(short m, short t, short id) : meshIndex(m), textureIndex(t), entityID(id){};
        short meshIndex;
        short textureIndex;
        short entityID;
    };

    struct Sound
    {
        ALuint mSoundSource{0};
        ALuint mSoundBuffer{0};
        short mEntityID{-1};

    };

    struct Tower
    {
        float mRange{ 15.0f };
        float mFireRate{ 2.0f };  // shots per second
        float mLastFireTime{ 0.0f };
        bool mCanFire{ true };
        enum TowerType { PROJECTILE, BOULDER } mType{ PROJECTILE };
        short mEntityID{ -1 };
    };

    struct Transform
    {
        glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };
        glm::vec3 mRotation{ 0.0f, 0.0f, 0.0f };
        glm::vec3 mScale{ 1.0f, 1.0f, 1.0f };
        short mEntityID{ -1 };

        Transform(short id) : mEntityID(id){};

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


    //The plan is that the systems can use these vectors containing all components of the different types
    //The components should be sorted by EntityID when added to the vectors.
    //A Render system then might need many vectors, but a Move system might only need one or two.
    //Each system just access the ones they need, and iterates through them and do their job.
    //Since the components are sorted by EntityID, the iteration should go well and we should get DOD benefits.

    // Component vectors - sorted by EntityID for DOD performance
    extern std::vector<gea::AI> ComponentAIVector;
    extern std::vector<gea::Enemy> ComponentEnemyVector;
    extern std::vector<gea::Health> ComponentHealthVector;
    extern std::vector<gea::Material> ComponentMaterialVector;
    extern std::vector<gea::Model> ComponentModelVector;
    extern std::vector<gea::Movement> ComponentMovementVector;
    extern std::vector<gea::Projectile> ComponentProjectileVector;
    extern std::vector<gea::Sound> ComponentSoundVector;
    extern std::vector<gea::Tower> ComponentTowerVector;
    extern std::vector<gea::Transform> ComponentTransformVector;

}   //namespace gea

#endif // COMPONENTS_H
