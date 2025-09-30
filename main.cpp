#include "Engine.h"
#include "Systems.h"
#include <iostream>

int main() {
    gea::Engine engine;

    // to create an entity
    auto* entity = engine.CreateEntity();
    std::cout << "Created Entity ID: " << entity->mEntityID << std::endl;

    // to add all components
    auto* transform = engine.AddTransform(entity);
    auto* movement = engine.AddMovement(entity);
    auto* health = engine.AddHealth(entity);
    auto* tower = engine.AddTower(entity);
    auto* enemy = engine.AddEnemy(entity);
    auto* projectile = engine.AddProjectile(entity);

    // To modify component values
    movement->mDirection = glm::vec3(1.0f, 0.0f, 0.0f);
    movement->mSpeed = 2.0f;

    health->mCurrentHealth = 75.0f;
    tower->mCanFire = true;
    enemy->mReachedPlayer = false;
    projectile->mVelocity = glm::vec3(0.0f, 1.0f, 0.0f);

    // to print initial states
    std::cout << "Initial Position: " << transform->mPosition.x << ", "
        << transform->mPosition.y << ", " << transform->mPosition.z << std::endl;
    std::cout << "Health: " << health->mCurrentHealth << "/" << health->mMaxHealth << std::endl;
    std::cout << "Tower Can Fire: " << (tower->mCanFire ? "Yes" : "No") << std::endl;
    std::cout << "Enemy Reached Player: " << (enemy->mReachedPlayer ? "Yes" : "No") << std::endl;
    std::cout << "Projectile Velocity: " << projectile->mVelocity.x << ", "
        << projectile->mVelocity.y << ", " << projectile->mVelocity.z << std::endl;

    // run MovementSystem
    gea::MovementSystem movementSystem;
    float deltaTime = 1.0f;
    movementSystem.Update(deltaTime);

    // to print updated position
    std::cout << "Updated Position: " << transform->mPosition.x << ", "
        << transform->mPosition.y << ", " << transform->mPosition.z << std::endl;

    // to confirm component sorting
    std::cout << "TransformVector sorted by EntityID: ";
    for (const auto& t : gea::TransformVector) {
        std::cout << t.mEntityID << " ";
    }
    std::cout << std::endl;

    return 0;
}
