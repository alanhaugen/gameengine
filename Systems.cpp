#include "Systems.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace gea {

glm::vec3 getPlayerPosition() {
    return glm::vec3(0.0f, 5.0f, 0.0f); // starting point for player lets supoose hilltop
}

// movement 
void MovementSystem::Update(float deltaTime) {
    for (auto& movement : mEngine->MovementVector) {
        auto transIt = std::find_if(mEngine->TransformVector.begin(), mEngine->TransformVector.end(),
            [&movement](const Transform& t){ return t.mEntityID == movement.mEntityID;});
        if (transIt != mEngine->TransformVector.end()) {
            glm::vec3 direction = getPlayerPosition() - transIt->mPosition;
            float dist = glm::length(direction);
            if (dist > 1.5f) { // Not at center yet
                movement.mDirection = glm::normalize(direction);
                transIt->mPosition += movement.mDirection * movement.mSpeed * deltaTime;
            }
        }
    }
}

// for towersystem
void TowerSystem::Update(float deltaTime) {
    for (auto& tower : mEngine->TowerVector) {
        tower.mLastFireTime += deltaTime;
        if (tower.mLastFireTime >= 1.0f / tower.mFireRate && tower.mCanFire) {
            auto towerTrans = std::find_if(mEngine->TransformVector.begin(), mEngine->TransformVector.end(),
                [&tower](const Transform& t){ return t.mEntityID == tower.mEntityID; });
            if (towerTrans == mEngine->TransformVector.end()) continue;
            glm::vec3 pos = towerTrans->mPosition;

            // search nearest enemy
            short nearestEnemyID = -1;
            float nearestDist = tower.mRange + 1.0f;
            for (const auto& enemy : mEngine->EnemyVector) {
                auto enemyTr = std::find_if(mEngine->TransformVector.begin(), mEngine->TransformVector.end(),
                    [&enemy](const Transform& t){ return t.mEntityID == enemy.mEntityID; });
                if (enemyTr == mEngine->TransformVector.end()) continue;
                float dist = glm::length(pos - enemyTr->mPosition);
                if (dist < tower.mRange && dist < nearestDist) {
                    nearestDist = dist;
                    nearestEnemyID = enemy.mEntityID;
                }
            }
            if (nearestEnemyID != -1) {
                Entity* projEntity = Engine().CreateEntity();
                auto* projTrans = Engine().AddTransform(projEntity);
                auto* projectile = Engine().AddProjectile(projEntity);
                projTrans->mPosition = pos;
                auto targetTrans = std::find_if(mEngine->TransformVector.begin(), mEngine->TransformVector.end(),
                    [nearestEnemyID](const Transform& t){ return t.mEntityID == nearestEnemyID;});
                if (targetTrans != mEngine->TransformVector.end()) {
                    projectile->mVelocity = glm::normalize(targetTrans->mPosition - pos) * 10.0f;
                }
                projectile->mEntityID = projEntity->mEntityID;
            }
            tower.mLastFireTime = 0.f;
        }
    }
}

//  checks collision and lifetime
void ProjectileSystem::Update(float deltaTime) {
    for (auto it = mEngine->ProjectileVector.begin(); it != mEngine->ProjectileVector.end();) {
        auto& projectile = *it;
        auto transIt = std::find_if(mEngine->TransformVector.begin(), mEngine->TransformVector.end(),
            [&projectile](const Transform& t){ return t.mEntityID == projectile.mEntityID;});
        if (transIt == mEngine->TransformVector.end()) { ++it; continue; }
        projectile.mLifetime -= deltaTime;
        transIt->mPosition += projectile.mVelocity * deltaTime;
        bool destroyed = false;
        // Check for hits on all enemies
        for (auto& enemy : mEngine->EnemyVector) {
            auto enemyTransIt = std::find_if(mEngine->TransformVector.begin(), mEngine->TransformVector.end(),
                [&enemy](const Transform& t){ return t.mEntityID == enemy.mEntityID; });
            if (enemyTransIt == mEngine->TransformVector.end()) continue;
            if (glm::length(enemyTransIt->mPosition - transIt->mPosition) < 1.0f) {
                auto enemyHealthIt = std::find_if(mEngine->HealthVector.begin(), mEngine->HealthVector.end(),
                    [&enemy](const Health& h){ return h.mEntityID == enemy.mEntityID; });
                if (enemyHealthIt != mEngine->HealthVector.end()) {
                    enemyHealthIt->mCurrentHealth -= projectile.mDamage;
                    std::cout << "Enemy " << enemy.mEntityID << " hit, health: " << enemyHealthIt->mCurrentHealth << "\n";
                }
                Engine().DestroyEntity(projectile.mEntityID);
                it = mEngine->ProjectileVector.erase(it);
                destroyed = true;
                break;
            }
        }
        if (destroyed) continue;
        if (projectile.mLifetime <= 0.0f) {
            Engine().DestroyEntity(projectile.mEntityID);
            it = mEngine->ProjectileVector.erase(it);
        } else {
            ++it;
        }
    }
}

void HealthSystem::Update(float /*deltaTime*/) {
    for (auto it = mEngine->HealthVector.begin(); it != mEngine->HealthVector.end();) {
        if (it->mCurrentHealth <= 0) {
            std::cout << "Entity " << it->mEntityID << " dies.\n";
            Engine().DestroyEntity(it->mEntityID);
            it = mEngine->HealthVector.erase(it);
        } else {
            ++it;
        }
    }
}

// add an "enemy" at intervals
void WaveSystem::Update(float deltaTime) {
    static float timer = 0.0f;
    timer += deltaTime;
    if (timer >= 4.0f) { // New wave every 4 seconds (for demo)
        Entity* enemy = Engine().CreateEntity();
        auto* transform = Engine().AddTransform(enemy);
        transform->mPosition = glm::vec3(10.0f - 20.0f * (rand()/(float)RAND_MAX), 0.0f, 0.0f);
        Engine().AddMovement(enemy)->mSpeed = 2.0f + rand() % 3;
        Engine().AddEnemy(enemy);
        Engine().AddHealth(enemy)->mCurrentHealth = 30.0f + rand() % 30;
        std::cout << "New enemy wave!\n";
        timer = 0.0f;
    }
}

// work in progress, not completed yet?Akash?
void AISystem::Update(float) {}

} // namespace gea
