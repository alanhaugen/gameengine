#include "Systems.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace gea {

glm::vec3 getPlayerPosition()
{
    return glm::vec3(0.0f, 5.0f, 0.0f); // starting point for player lets supoose hilltop
}

// movement
void MovementSystem::update(float deltaTime)
{
    for (auto& movement : mEngine->mMovementComponents) {
        auto transIt = std::find_if(mEngine->mTransformComponents.begin(), mEngine->mTransformComponents.end(),
            [&movement](const TransformComponent& t){ return t.mEntityID == movement.mEntityID;});
        if (transIt != mEngine->mTransformComponents.end()) {
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
void TowerSystem::update(float deltaTime)
{
    for (auto& tower : mEngine->mTowerComponents) {
        tower.mLastFireTime += deltaTime;
        if (tower.mLastFireTime >= 1.0f / tower.mFireRate && tower.mCanFire) {
            auto towerTrans = std::find_if(mEngine->mTransformComponents.begin(), mEngine->mTransformComponents.end(),
                [&tower](const TransformComponent& t){ return t.mEntityID == tower.mEntityID; });
            if (towerTrans == mEngine->mTransformComponents.end()) continue;
            glm::vec3 pos = towerTrans->mPosition;

            // search nearest enemy
            short nearestEnemyID = -1;
            float nearestDist = tower.mRange + 1.0f;
            for (const auto& enemy : mEngine->mEnemyComponents) {
                auto enemyTr = std::find_if(mEngine->mTransformComponents.begin(), mEngine->mTransformComponents.end(),
                    [&enemy](const TransformComponent& t){ return t.mEntityID == enemy.mEntityID; });
                if (enemyTr == mEngine->mTransformComponents.end()) continue;
                float dist = glm::length(pos - enemyTr->mPosition);
                if (dist < tower.mRange && dist < nearestDist) {
                    nearestDist = dist;
                    nearestEnemyID = enemy.mEntityID;
                }
            }
            if (nearestEnemyID != -1) {
                Entity* projEntity = mEngine->createEntity();
                auto* projTrans = mEngine->addTransform(projEntity);
                auto* projectile = mEngine->addProjectile(projEntity);
                projTrans->mPosition = pos;
                auto targetTrans = std::find_if(mEngine->mTransformComponents.begin(), mEngine->mTransformComponents.end(),
                    [nearestEnemyID](const TransformComponent& t){ return t.mEntityID == nearestEnemyID;});
                if (targetTrans != mEngine->mTransformComponents.end()) {
                    projectile->mVelocity = glm::normalize(targetTrans->mPosition - pos) * 10.0f;
                }
                projectile->mEntityID = projEntity->mEntityID;
            }
            tower.mLastFireTime = 0.f;
        }
    }
}

//  checks collision and lifetime
void ProjectileSystem::update(float deltaTime)
{
    for (auto it = mEngine->mProjectileComponents.begin(); it != mEngine->mProjectileComponents.end();) {
        auto& projectile = *it;
        auto transIt = std::find_if(mEngine->mTransformComponents.begin(), mEngine->mTransformComponents.end(),
            [&projectile](const TransformComponent& t){ return t.mEntityID == projectile.mEntityID;});
        if (transIt == mEngine->mTransformComponents.end()) { ++it; continue; }
        projectile.mLifetime -= deltaTime;
        transIt->mPosition += projectile.mVelocity * deltaTime;
        bool destroyed = false;
        // Check for hits on all enemies
        for (auto& enemy : mEngine->mEnemyComponents) {
            auto enemyTransIt = std::find_if(mEngine->mTransformComponents.begin(), mEngine->mTransformComponents.end(),
                [&enemy](const TransformComponent& t){ return t.mEntityID == enemy.mEntityID; });
            if (enemyTransIt == mEngine->mTransformComponents.end()) continue;
            if (glm::length(enemyTransIt->mPosition - transIt->mPosition) < 1.0f) {
                auto enemyHealthIt = std::find_if(mEngine->mHealthComponents.begin(), mEngine->mHealthComponents.end(),
                    [&enemy](const HealthComponent& h){ return h.mEntityID == enemy.mEntityID; });
                if (enemyHealthIt != mEngine->mHealthComponents.end()) {
                    enemyHealthIt->mCurrentHealth -= projectile.mDamage;
                    std::cout << "Enemy " << enemy.mEntityID << " hit, health: " << enemyHealthIt->mCurrentHealth << "\n";
                }
                mEngine->destroyEntity(projectile.mEntityID);
                it = mEngine->mProjectileComponents.erase(it);
                destroyed = true;
                break;
            }
        }
        if (destroyed) continue;
        if (projectile.mLifetime <= 0.0f) {
            mEngine->destroyEntity(projectile.mEntityID);
            it = mEngine->mProjectileComponents.erase(it);
        } else {
            ++it;
        }
    }
}

void HealthSystem::update(float /*deltaTime*/) {
    for (auto it = mEngine->mHealthComponents.begin(); it != mEngine->mHealthComponents.end();) {
        if (it->mCurrentHealth <= 0) {
            std::cout << "Entity " << it->mEntityID << " dies.\n";
            mEngine->destroyEntity(it->mEntityID);
            it = mEngine->mHealthComponents.erase(it);
        } else {
            ++it;
        }
    }
}

// add an "enemy" at intervals
void WaveSystem::update(float deltaTime)
{
    static float timer = 0.0f;
    timer += deltaTime;
    if (timer >= 4.0f) { // New wave every 4 seconds (for demo)
        Entity* enemy = mEngine->createEntity();
        auto* transform = mEngine->addTransform(enemy);
        transform->mPosition = glm::vec3(10.0f - 20.0f * (rand()/(float)RAND_MAX), 0.0f, 0.0f);
        mEngine->addMovement(enemy)->mSpeed = 2.0f + rand() % 3;
        mEngine->addEnemy(enemy);
        mEngine->addHealth(enemy)->mCurrentHealth = 30.0f + rand() % 30;
        std::cout << "New enemy wave!\n";
        timer = 0.0f;
    }
}

// work in progress, not completed yet?Akash?
void AISystem::update(float) {}

} // namespace gea
