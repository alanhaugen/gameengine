#include "Engine.h"
#include "Entity.h"
#include "Renderer.h"
#include "System.h"
#include <qdebug.h>
#include "PhysicsSystem.h"

namespace gea
{
    Engine::Engine() {}
    Engine::~Engine() {}

    void Engine::Initialize(Renderer* renderer)
    {
        mRenderer = renderer;
        InitializeSystems();
    }

    void Engine::InitializeSystems()
    {
        qDebug() << "Initializing all systems." ;
        mSystems.push_back(std::make_unique<PhysicsSystem>(this));
    }

    void Engine::Update(float deltaTime)
    {
        for (auto& system : mSystems)
        {
            system->update(deltaTime);
        }
    }

    void Engine::Quit()
    {
        mSystems.clear();
    }

    Entity* Engine::CreateEntity()
    {
        mEntities.emplace_back(this);
        return &mEntities.back();
    }

    void Engine::DestroyEntity(size_t EntityID)
    {
        //not sure how to do this
    }

    Entity* Engine::GetEntity(size_t EntityID)
    {
        for (auto& entity : mEntities)
            if (entity.mEntityID == EntityID)
            {
                return &entity;
            }
        return nullptr;
    }

}
