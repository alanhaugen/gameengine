#include "Engine.h"
#include "Core/Renderer.h"
#include <algorithm>
#include <chrono>
#include <qlogging.h>

namespace gea
{

Engine::Engine(Renderer* renderer, MainWindow *mainWindow) : mVulkanRenderer{renderer}, mMainWindow{mainWindow}
{
    mMeshs.push_back(gea::Mesh());
    mTextures.push_back(gea::Texture());

    mRenderComponents.push_back(gea::RenderComponent{0, 0, 0});
    gea::TransformComponent t1 = gea::TransformComponent(0);
    t1.mPosition = glm::vec3(1.0f, 0.0f, 0.0f);
    mTransformComponents.push_back(t1);

    mStaticRenderComponents.push_back(gea::RenderComponent{0, 0, 1});
    gea::TransformComponent t2 = gea::TransformComponent(1);
    t2.mPosition = glm::vec3(-1.0f, 0.0f, 0.0f);
    mStaticTransformComponents.push_back(t2);

    setupRenderSystem();
    //mVulkanWindow->initVulkan();
    //updateRenderSystem();
}

void Engine::setupRenderSystem()
{
    mRenderSystem = new gea::RenderSystem(this, mVulkanRenderer);
    mRenderSystem->initialize(mStaticRenderComponents, mStaticTransformComponents, mMeshs, mTextures);
}

void Engine::updateRenderSystem()
{
    mRenderSystem->update(mRenderComponents, mTransformComponents);
}

Entity* Engine::createEntity()
{
    mEntityVector.emplace_back();
    return &mEntityVector.back();
}

void Engine::destroyEntity(std::size_t entityID)
{

    mEntityVector.erase(std::remove_if(mEntityVector.begin(), mEntityVector.end(),
                          [entityID](const Entity& e){ return e.mEntityID == entityID; }), mEntityVector.end());
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

TransformComponent* Engine::addTransform(Entity* entity)
{
    TransformComponent t(entity->mEntityID);
    mTransformComponents.push_back(t);
    entity->mComponents.push_back({ComponentTypes::Transform, (short)(mTransformComponents.size()-1)});
    sortComponents();
    return &mTransformComponents.back();
}

MovementComponent* Engine::addMovement(Entity* entity)
{
    MovementComponent m;
    m.mEntityID = entity->mEntityID;
    mMovementComponents.push_back(m);
    entity->mComponents.push_back({ComponentTypes::Movement, (short)(mMovementComponents.size()-1)});
    sortComponents();
    return &mMovementComponents.back();
}

HealthComponent* Engine::addHealth(Entity* entity)
{
    HealthComponent h;
    h.mEntityID = entity->mEntityID;
    mHealthComponents.push_back(h);
    entity->mComponents.push_back({ComponentTypes::Health, (short)(mHealthComponents.size()-1)});
    sortComponents();
    return &mHealthComponents.back();
}

TowerComponent* Engine::addTower(Entity* entity)
{
    TowerComponent t;
    t.mEntityID = entity->mEntityID;
    mTowerComponents.push_back(t);
    entity->mComponents.push_back({ComponentTypes::Tower, (short)(mTowerComponents.size()-1)});
    sortComponents();
    return &mTowerComponents.back();
}

EnemyComponent* Engine::addEnemy(Entity* entity)
{
    EnemyComponent e;
    e.mEntityID = entity->mEntityID;
    mEnemyComponents.push_back(e);
    entity->mComponents.push_back({ComponentTypes::Enemy, (short)(mEnemyComponents.size()-1)});
    sortComponents();
    return &mEnemyComponents.back();
}

ProjectileComponent* Engine::addProjectile(Entity* entity)
{
    ProjectileComponent p;
    p.mEntityID = entity->mEntityID;
    mProjectileComponents.push_back(p);
    entity->mComponents.push_back({ComponentTypes::Projectile, (short)(mProjectileComponents.size()-1)});
    sortComponents();
    return &mProjectileComponents.back();
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
    qDebug("DeltaTime %.6f", deltaTimeSeconds);    //prints float with 6 decimal places


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

} //gea namespace
