#ifndef ENGINE_H
#define ENGINE_H

#include "Entity.h"
#include "Components.h"

namespace gea {

    class Engine {
    public:
        // to Add/Remove entity
        Entity* CreateEntity();
        void DestroyEntity(std::size_t entityID);

        // to add component 
        Transform* AddTransform(Entity* entity);
        Movement* AddMovement(Entity* entity);
        Health* AddHealth(Entity* entity);
        Tower* AddTower(Entity* entity);
        Enemy* AddEnemy(Entity* entity);
        Projectile* AddProjectile(Entity* entity);

        // It sort all component vectors by EntityID
        void SortComponents();

        // It is game loop
        void Update(float deltaTime); // Calls all system update functions
    };
}

#endif
