#ifndef ENGINE_H
#define ENGINE_H

#include "Entity.h"
#include "Components.h"
#include "Mesh.h"
#include "RenderSystem.h"
#include "Texture.h"

namespace gea
{

class Engine
{
public:
    Engine(Renderer* renderer);

    //Variables for the game loop - not used and not working yet
    bool mIsRunning{false};
    const long long mUpdateInterval = 10000000; // 10ms in nanoseconds (10^7)
    void gameLoop();

    void updateRenderSystem();
    void setupRenderSystem();

    gea::RenderSystem* mRenderSystem{nullptr};
    Renderer* mVulkanRenderer{nullptr};

    // to Add/Remove entity
    Entity* createEntity();
    void destroyEntity(std::size_t entityID);

    // to add component
    TransformComponent* addTransform(Entity* entity);
    MovementComponent* addMovement(Entity* entity);
    HealthComponent* addHealth(Entity* entity);
    TowerComponent* addTower(Entity* entity);
    EnemyComponent* addEnemy(Entity* entity);
    ProjectileComponent* addProjectile(Entity* entity);

    // It sort all component vectors by EntityID
    void sortComponents();

    // It is the game loop
    void update(float deltaTime); // Calls all system update functions

    //Vector that holds all the Entities in our game:
    std::vector<Entity> mEntityVector;

    //Vectors that holds all the Components
    //should sorted by EntityID for DOD performance
    std::vector<TransformComponent> mTransformComponents;
    std::vector<MovementComponent> mMovementComponents;
    std::vector<HealthComponent> mHealthComponents;
    std::vector<TowerComponent> mTowerComponents;
    std::vector<EnemyComponent> mEnemyComponents;
    std::vector<ProjectileComponent> mProjectileComponents;
    std::vector<AIComponent> mAIComponents;
    std::vector<MaterialComponent> mMaterialComponents;
    std::vector<ModelComponent> mModelComponents;
    std::vector<SoundComponent> mSoundComponents;

    //RenderTesting
    std::vector<gea::RenderComponent> mRenderComponents;
    std::vector<gea::RenderComponent> mStaticRenderComponents;
    //this is done for testing sake. in the real ecs there would only be one vector of transform components
    std::vector<gea::TransformComponent> mStaticTransformComponents;

    //These are the ACTUAL meshes and Textures, and is used by Entities from a
    //RenderComponent
    std::vector<Mesh> mMeshs;
    std::vector<Texture> mTextures;

    //The plan is that the systems can use these vectors containing all components of the different types
    //The components should be sorted by EntityID when added to the vectors.
    //A Render system then might need many vectors, but a Move system might only need one or two.
    //Each system just access the ones they need, and iterates through them and do their job.
    //Since the components are sorted by EntityID, the iteration should go well and we should get DOD benefits.
};

} //namespace gea

#endif
