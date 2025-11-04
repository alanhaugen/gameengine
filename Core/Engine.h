#ifndef ENGINE_H
#define ENGINE_H

#include "ECS/Entity.h"
#include "ECS/Components.h"
#include "ECS/RenderSystem.h"
#include "AssetManager/Mesh.h"
#include "AssetManager/Texture.h"
#include "Editor/MainWindow.h"
#include <chrono>

namespace gea
{

class Engine
{
public:
    Engine(Renderer* renderer, MainWindow* mainWindow);

    //Variables for the game loop
    bool mIsRunning{false};
    std::chrono::time_point<std::chrono::high_resolution_clock> mClockLastFrame{};

    //This is the core game loop!
    void update();

    void updateRenderSystem();
    void setupRenderSystem();

    gea::RenderSystem* mRenderSystem{nullptr};
    Renderer* mVulkanRenderer{nullptr};

    MainWindow* mMainWindow{nullptr};

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
