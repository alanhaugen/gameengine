#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <memory>
#include "Entity.h"
#include "Components.h"

class Renderer;

namespace gea
{
    class System;

    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Initialize(Renderer* renderer);
        void Update(float deltaTime);
        void Quit();

        Entity& CreateEntity();
        void DestroyEntity(size_t entityID);
        Entity& GetEntity(size_t entityID);

        void RegisterSystem(std::unique_ptr<System> system);

    private:
        //where we store entities
        std::vector<Entity> mEntities;
        //where we store components
        std::vector<Transform> mTransforms;
        std::vector<Mesh> mMeshes;
        std::vector<Texture> mTextures;
        std::vector<Movement> mMovements;
        std::vector<Health> mHealths;
        std::vector<Tower> mTowers;
        std::vector<Enemy> mEnemies;
        std::vector<Projectile> mProjectiles;
        std::vector<AI> mAIs;
        //systems storage
        std::vector<std::unique_ptr<System>> mSystems;
        //renderer
        Renderer* mRenderer{nullptr};
    };
}
#endif // ENGINE_H
