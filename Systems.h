#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "Engine.h"
#include <iostream>

namespace gea {

class SystemBase {
public:
    virtual ~SystemBase() = default;
    virtual void Update(float deltaTime) = 0;
};

// enemy movement up the hill, towards the player
class MovementSystem : public SystemBase {
public:
    void Update(float deltaTime) override;
};

// tower shooting projectiles or rolling boulders
class TowerSystem : public SystemBase {
public:
    void Update(float deltaTime) override;
};

// projectile movement and collision with enemies
class ProjectileSystem : public SystemBase {
public:
    void Update(float deltaTime) override;
};

//  enemies damage player, entity death
class HealthSystem : public SystemBase {
public:
    void Update(float deltaTime) override;
};

// spawns waves of enemies from all directions
class WaveSystem : public SystemBase {
public:
    void Update(float deltaTime) override;
};

// Basic AI 
class AISystem : public SystemBase {
public:
    void Update(float deltaTime) override;
};

// Rendering system for Qt/Vulkan
class RenderSystem : public SystemBase {
public:
    void Update(float deltaTime) override;
};

}

#endif // SYSTEMS_H
