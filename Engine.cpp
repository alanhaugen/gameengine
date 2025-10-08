#include "Engine.h"
#include <algorithm>

namespace gea {

    Entity* Engine::CreateEntity()
    {
        EntityVector.emplace_back();
        return &EntityVector.back();
    }

    void Engine::DestroyEntity(std::size_t entityID)
    {
 
        EntityVector.erase(std::remove_if(EntityVector.begin(), EntityVector.end(),
                          [entityID](const Entity& e){ return e.mEntityID == entityID; }), EntityVector.end());
       
        TransformVector.erase(std::remove_if(TransformVector.begin(), TransformVector.end(),
                          [entityID](const Transform& c){ return c.mEntityID == entityID; }), TransformVector.end());
        MovementVector.erase(std::remove_if(MovementVector.begin(), MovementVector.end(),
                          [entityID](const Movement& c){ return c.mEntityID == entityID; }), MovementVector.end());
        HealthVector.erase(std::remove_if(HealthVector.begin(), HealthVector.end(),
                          [entityID](const Health& c){ return c.mEntityID == entityID; }), HealthVector.end());
        TowerVector.erase(std::remove_if(TowerVector.begin(), TowerVector.end(),
                          [entityID](const Tower& c){ return c.mEntityID == entityID; }), TowerVector.end());
        EnemyVector.erase(std::remove_if(EnemyVector.begin(), EnemyVector.end(),
                          [entityID](const Enemy& c){ return c.mEntityID == entityID; }), EnemyVector.end());
        ProjectileVector.erase(std::remove_if(ProjectileVector.begin(), ProjectileVector.end(),
                          [entityID](const Projectile& c){ return c.mEntityID == entityID; }), ProjectileVector.end());
        
    }

    Transform* Engine::AddTransform(Entity* entity)
    {
        Transform t(entity->mEntityID);
        TransformVector.push_back(t);
        entity->mComponents.push_back({ComponentTypes::Transform, (short)(TransformVector.size()-1)});
        SortComponents();
        return &TransformVector.back();
    }
   
    Movement* Engine::AddMovement(Entity* entity)
    {
        Movement m;
        m.mEntityID = entity->mEntityID;
        MovementVector.push_back(m);
        entity->mComponents.push_back({ComponentTypes::Movement, (short)(MovementVector.size()-1)});
        SortComponents();
        return &MovementVector.back();
    }

    Health* Engine::AddHealth(Entity* entity)
    {
        Health h;
        h.mEntityID = entity->mEntityID;
        HealthVector.push_back(h);
        entity->mComponents.push_back({ComponentTypes::Health, (short)(HealthVector.size()-1)});
        SortComponents();
        return &HealthVector.back();
    }

    Tower* Engine::AddTower(Entity* entity)
    {
        Tower t;
        t.mEntityID = entity->mEntityID;
        TowerVector.push_back(t);
        entity->mComponents.push_back({ComponentTypes::Tower, (short)(TowerVector.size()-1)});
        SortComponents();
        return &TowerVector.back();
    }

    Enemy* Engine::AddEnemy(Entity* entity)
    {
        Enemy e;
        e.mEntityID = entity->mEntityID;
        EnemyVector.push_back(e);
        entity->mComponents.push_back({ComponentTypes::Enemy, (short)(EnemyVector.size()-1)});
        SortComponents();
        return &EnemyVector.back();
    }

    Projectile* Engine::AddProjectile(Entity* entity)
    {
        Projectile p;
        p.mEntityID = entity->mEntityID;
        ProjectileVector.push_back(p);
        entity->mComponents.push_back({ComponentTypes::Projectile, (short)(ProjectileVector.size()-1)});
        SortComponents();
        return &ProjectileVector.back();
    }

    void Engine::SortComponents()
    {
        std::sort(TransformVector.begin(), TransformVector.end(),
                  [](const Transform& a, const Transform& b){ return a.mEntityID < b.mEntityID; });
        std::sort(MovementVector.begin(), MovementVector.end(),
                  [](const Movement& a, const Movement& b){ return a.mEntityID < b.mEntityID; });
   
    }

    void Engine::Update(float deltaTime)
    {
        // to call all systems 
        // i am listing Example:
        //   MovementSystem::Update()
        //   TowerSystem::Update()
        //   ProjectileSystem::Update()
        //   HealthSystem::Update()
    }
}
