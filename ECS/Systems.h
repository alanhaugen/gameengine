#ifndef SYSTEMS_H
#define SYSTEMS_H

namespace gea
{

class SystemBase
{
public:
    SystemBase(class Engine* engineInstance) : mEngine{engineInstance} {};
    virtual ~SystemBase() = default;
    virtual void update(float deltaTime) = 0;

    class Engine* mEngine{nullptr};
};

// enemy movement up the hill, towards the player
class MovementSystem : public SystemBase
{
public:
    void update(float deltaTime) override;
};

// // tower shooting projectiles or rolling boulders
// class TowerSystem : public SystemBase
// {
// public:
//     void update(float deltaTime) override;
// };

// // projectile movement and collision with enemies
// class ProjectileSystem : public SystemBase
// {
// public:
//     void update(float deltaTime) override;
// };

// //  enemies damage player, entity death
// class HealthSystem : public SystemBase
// {
// public:
//     void update(float deltaTime) override;
// };

// // spawns waves of enemies from all directions
// class WaveSystem : public SystemBase
// {
// public:
//     void update(float deltaTime) override;
// };

// // Basic AI
// class AISystem : public SystemBase
// {
// public:
//     void update(float deltaTime) override;
// };

} //namespace gea

#endif // SYSTEMS_H
