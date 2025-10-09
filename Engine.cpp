#include "Engine.h"
#include <algorithm>
#include <chrono>
#include <qlogging.h>
#include <thread>

namespace gea {

Engine::Engine(Renderer* renderer) : mVulkanRenderer{renderer}
{
    mMeshComponents.push_back(gea::Mesh());
    mTextureComponents.push_back(gea::Texture());

    mRenderComponents.push_back(gea::RenderComponent{0, 0, 0});
    gea::Transform t1 = gea::Transform(0);
    t1.mPosition = glm::vec3(1.0f, 0.0f, 0.0f);
    mTransformComponents.push_back(t1);

    mStaticRenderComponents.push_back(gea::RenderComponent{0, 0, 1});
    gea::Transform t2 = gea::Transform(1);
    t2.mPosition = glm::vec3(-1.0f, 0.0f, 0.0f);
    mStaticTransformComponents.push_back(t2);

    SetupRenderSystem();
    //mVulkanWindow->initVulkan();
    UpdateRenderSystem();
}

void Engine::SetupRenderSystem()
{
    mRenderSystem = new gea::RenderSystem(this, mVulkanRenderer);
    mRenderSystem->Initialize(mStaticRenderComponents, mStaticTransformComponents, mMeshComponents, mTextureComponents);
}

void Engine::UpdateRenderSystem()
{
    mRenderSystem->Update(mRenderComponents, mTransformComponents);
}

Entity* Engine::CreateEntity()
    {
        mEntityVector.emplace_back();
        return &mEntityVector.back();
    }

    void Engine::DestroyEntity(std::size_t entityID)
    {
 
        mEntityVector.erase(std::remove_if(mEntityVector.begin(), mEntityVector.end(),
                          [entityID](const Entity& e){ return e.mEntityID == entityID; }), mEntityVector.end());
       
        mTransformComponents.erase(std::remove_if(mTransformComponents.begin(), mTransformComponents.end(),
                          [entityID](const Transform& c){ return c.mEntityID == entityID; }), mTransformComponents.end());
        mMovementComponents.erase(std::remove_if(mMovementComponents.begin(), mMovementComponents.end(),
                          [entityID](const Movement& c){ return c.mEntityID == entityID; }), mMovementComponents.end());
        mHealthComponents.erase(std::remove_if(mHealthComponents.begin(), mHealthComponents.end(),
                          [entityID](const Health& c){ return c.mEntityID == entityID; }), mHealthComponents.end());
        mTowerComponents.erase(std::remove_if(mTowerComponents.begin(), mTowerComponents.end(),
                          [entityID](const Tower& c){ return c.mEntityID == entityID; }), mTowerComponents.end());
        mEnemyComponents.erase(std::remove_if(mEnemyComponents.begin(), mEnemyComponents.end(),
                          [entityID](const Enemy& c){ return c.mEntityID == entityID; }), mEnemyComponents.end());
        mProjectileComponents.erase(std::remove_if(mProjectileComponents.begin(), mProjectileComponents.end(),
                          [entityID](const Projectile& c){ return c.mEntityID == entityID; }), mProjectileComponents.end());
        
    }

    Transform* Engine::AddTransform(Entity* entity)
    {
        Transform t(entity->mEntityID);
        mTransformComponents.push_back(t);
        entity->mComponents.push_back({ComponentTypes::Transform, (short)(mTransformComponents.size()-1)});
        SortComponents();
        return &mTransformComponents.back();
    }
   
    Movement* Engine::AddMovement(Entity* entity)
    {
        Movement m;
        m.mEntityID = entity->mEntityID;
        mMovementComponents.push_back(m);
        entity->mComponents.push_back({ComponentTypes::Movement, (short)(mMovementComponents.size()-1)});
        SortComponents();
        return &mMovementComponents.back();
    }

    Health* Engine::AddHealth(Entity* entity)
    {
        Health h;
        h.mEntityID = entity->mEntityID;
        mHealthComponents.push_back(h);
        entity->mComponents.push_back({ComponentTypes::Health, (short)(mHealthComponents.size()-1)});
        SortComponents();
        return &mHealthComponents.back();
    }

    Tower* Engine::AddTower(Entity* entity)
    {
        Tower t;
        t.mEntityID = entity->mEntityID;
        mTowerComponents.push_back(t);
        entity->mComponents.push_back({ComponentTypes::Tower, (short)(mTowerComponents.size()-1)});
        SortComponents();
        return &mTowerComponents.back();
    }

    Enemy* Engine::AddEnemy(Entity* entity)
    {
        Enemy e;
        e.mEntityID = entity->mEntityID;
        mEnemyComponents.push_back(e);
        entity->mComponents.push_back({ComponentTypes::Enemy, (short)(mEnemyComponents.size()-1)});
        SortComponents();
        return &mEnemyComponents.back();
    }

    Projectile* Engine::AddProjectile(Entity* entity)
    {
        Projectile p;
        p.mEntityID = entity->mEntityID;
        mProjectileComponents.push_back(p);
        entity->mComponents.push_back({ComponentTypes::Projectile, (short)(mProjectileComponents.size()-1)});
        SortComponents();
        return &mProjectileComponents.back();
    }

    void Engine::SortComponents()
    {
        std::sort(mTransformComponents.begin(), mTransformComponents.end(),
                  [](const Transform& a, const Transform& b){ return a.mEntityID < b.mEntityID; });
        std::sort(mMovementComponents.begin(), mMovementComponents.end(),
                  [](const Movement& a, const Movement& b){ return a.mEntityID < b.mEntityID; });
   
    }

    void Engine::Update(float deltaTime)
    {
        //qDebug("Update called %.6f", deltaTime);
        UpdateRenderSystem();
        // to call all systems 
        // i am listing Example:
        //   MovementSystem::Update()
        //   TowerSystem::Update()
        //   ProjectileSystem::Update()
        //   HealthSystem::Update()
    }

    //Simple loop that should call Update 100Hz
    void Engine::GameLoop()
    {
        qDebug("GameLoop started");
        auto lastUpdateTime = std::chrono::high_resolution_clock::now();
        long long accumulatedTime = 0;

        while (mIsRunning)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastUpdateTime).count();
            lastUpdateTime = currentTime;
            accumulatedTime += frameTime;

            // Convert to seconds for physics calculations

            // Update at fixed intervals (100Hz)
            while (accumulatedTime >= mUpdateInterval)
            {
                // Convert to seconds for physics calculations
                double deltaTimeSeconds = mUpdateInterval / 1000000000.0;
                Update(deltaTimeSeconds);  // Your 100Hz logic here
                accumulatedTime -= mUpdateInterval;
            }

            // Small sleep to prevent 100% CPU usage
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
