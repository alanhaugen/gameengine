#include "Engine.h"
#include "Core/Renderer.h"
#include "ECS/ScriptingSystem.h"
#include <algorithm>
#include <chrono>
#include <qlogging.h>

namespace gea
{

Engine::Engine(Renderer* renderer, MainWindow *mainWindow) : mVulkanRenderer{renderer}, mMainWindow{mainWindow}
{
    // Set up Asset Managers for different assets:
    mMeshManager = new AssetManager<gea::Mesh>();
    mMeshManager->importObjects();

    mTextureManager = new AssetManager<gea::Texture>();
    mTextureManager->importObjects();

    // and something like this for sound files:
    //mSoundFileManager=new AssetManager<gea::Sound>();
    //mSoundFileManager->importObjects();


    // Set up different systems:
    setupRenderSystem();
    mScriptSystem = new ScriptingSystem(mainWindow, this);

    // Set up the scene to be rendered:
    sceneSetup();
}

void Engine::setupRenderSystem()
{
    mVulkanRenderer->mEngine = this; // must be done before the renderSystem is setup
    mRenderSystem = new gea::RenderSystem(this, mVulkanRenderer);
    mRenderSystem->initialize(mStaticRenderComponents, mStaticTransformComponents, mMeshManager->mAssets, mTextureManager->mAssets);
}

void Engine::sceneSetup()
{
    //Make entities with at least MeshComponent and TransformComponent
    Entity tempEntity;
    RenderComponent tempRenderComp(3, 0, tempEntity.mEntityID);
    TransformComponent tempTransformComp(tempEntity.mEntityID);

    // Push components to vectors:
    mDynamicRenderComponents.push_back(tempRenderComp);
    mTransformComponents.push_back(tempTransformComp);

    // Update Entity:
    tempEntity.mComponents.push_back(&mDynamicRenderComponents.back());
    tempEntity.mComponents.push_back(&mTransformComponents.back());

    // Push Entity
    mEntities.push_back(tempEntity);
}

void Engine::updateRenderSystem()
{
    mRenderSystem->update(mTransformComponents);
}

Entity* Engine::createEntity()
{
    mEntities.emplace_back();
    emit itemAppended(mEntities.size() - 1);
    return &mEntities.back();
}

void Engine::sortComponents()
{
    std::sort(mTransformComponents.begin(), mTransformComponents.end(),
              [](const TransformComponent& a, const TransformComponent& b){ return a.mEntityID < b.mEntityID; });
    std::sort(mMovementComponents.begin(), mMovementComponents.end(),
              [](const MovementComponent& a, const MovementComponent& b){ return a.mEntityID < b.mEntityID; });
}

void Engine::update()
{
    // ***** Calculate deltaTime
    auto clockNow = std::chrono::high_resolution_clock::now();
    auto timeSinceLastFrame = clockNow - mClockLastFrame;
    float deltaTimeSeconds = std::chrono::duration_cast<std::chrono::duration<float>>(timeSinceLastFrame).count();
    mClockLastFrame = clockNow;
    //qDebug("DeltaTime %.6f", deltaTimeSeconds);    //prints float with 6 decimal places


    // ***** Update systems and other stuff each frame
    mMainWindow->handleInput();         //maybe put into its own class or system?
    mVulkanRenderer->mCamera.update();  //needs some propper cleanup


    updateRenderSystem();   //calls drawFrame()


    // to call all systems
    // i am listing Example:
    //   MovementSystem::Update()
    //   TowerSystem::Update()
    //   ProjectileSystem::Update()
    //   HealthSystem::Update()
}

void Engine::destroyEntity(std::size_t entityID)
{
    mEntities.erase(std::remove_if(mEntities.begin(), mEntities.end(),
                                       [entityID](const Entity& e){ return e.mEntityID == entityID; }), mEntities.end());
    mTransformComponents.erase(std::remove_if(mTransformComponents.begin(), mTransformComponents.end(),
                                              [entityID](const TransformComponent& c){ return c.mEntityID == entityID; }), mTransformComponents.end());
    mMovementComponents.erase(std::remove_if(mMovementComponents.begin(), mMovementComponents.end(),
                                             [entityID](const MovementComponent& c){ return c.mEntityID == entityID; }), mMovementComponents.end());
    mHealthComponents.erase(std::remove_if(mHealthComponents.begin(), mHealthComponents.end(),
                                           [entityID](const HealthComponent& c){ return c.mEntityID == entityID; }), mHealthComponents.end());
    mTowerComponents.erase(std::remove_if(mTowerComponents.begin(), mTowerComponents.end(),
                                          [entityID](const TowerComponent& c){ return c.mEntityID == entityID; }), mTowerComponents.end());
    mEnemyComponents.erase(std::remove_if(mEnemyComponents.begin(), mEnemyComponents.end(),
                                          [entityID](const EnemyComponent& c){ return c.mEntityID == entityID; }), mEnemyComponents.end());
    mProjectileComponents.erase(std::remove_if(mProjectileComponents.begin(), mProjectileComponents.end(),
                                               [entityID](const ProjectileComponent& c){ return c.mEntityID == entityID; }), mProjectileComponents.end());
}

RenderComponent* Engine::createRenderComponent(std::string, std::string, int)
{
    RenderComponent tempComponent(1, 1, 1); // = gea::RenderComponent{static_cast<int>(mMeshes.size()-1), static_cast<int>(mTextures.size()-1), ID};
    mDynamicRenderComponents.push_back(tempComponent);
    return &mDynamicRenderComponents.back();
}

TransformComponent* Engine::addTransform(Entity* entity)
{
    TransformComponent tempTransform(entity->mEntityID);
    mTransformComponents.push_back(tempTransform);
    entity->mComponents.push_back(&tempTransform);  // entity only has pointers to its components

    // sortComponents();    //commented out. Then the return statement will be valid. Sorting components at the end of all additions.

    return &mTransformComponents.back();
}

// MovementComponent* Engine::addMovement(Entity* entity)
// {
//     MovementComponent tempMovement;
//     tempMovement.mEntityID = entity->mEntityID;
//     mMovementComponents.push_back(tempMovement);
//     entity->mComponents.push_back({ComponentTypes::Movement, (short)(mMovementComponents.size()-1)});
//     sortComponents();
//     return &mMovementComponents.back();
// }

// HealthComponent* Engine::addHealth(Entity* entity)
// {
//     HealthComponent h;
//     h.mEntityID = entity->mEntityID;
//     mHealthComponents.push_back(h);
//     entity->mComponents.push_back({ComponentTypes::Health, (short)(mHealthComponents.size()-1)});
//     sortComponents();
//     return &mHealthComponents.back();
// }

// TowerComponent* Engine::addTower(Entity* entity)
// {
//     TowerComponent t;
//     t.mEntityID = entity->mEntityID;
//     mTowerComponents.push_back(t);
//     entity->mComponents.push_back({ComponentTypes::Tower, (short)(mTowerComponents.size()-1)});
//     sortComponents();
//     return &mTowerComponents.back();
// }

// EnemyComponent* Engine::addEnemy(Entity* entity)
// {
//     EnemyComponent e;
//     e.mEntityID = entity->mEntityID;
//     mEnemyComponents.push_back(e);
//     entity->mComponents.push_back({ComponentTypes::Enemy, (short)(mEnemyComponents.size()-1)});
//     sortComponents();
//     return &mEnemyComponents.back();
// }

// ProjectileComponent* Engine::addProjectile(Entity* entity)
// {
//     ProjectileComponent p;
//     p.mEntityID = entity->mEntityID;
//     mProjectileComponents.push_back(p);
//     entity->mComponents.push_back({ComponentTypes::Projectile, (short)(mProjectileComponents.size()-1)});
//     sortComponents();
//     return &mProjectileComponents.back();
// }


} //gea namespace
