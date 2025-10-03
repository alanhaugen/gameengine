#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <memory>
#include "Entity.h"
#include "Components.h"
#include "System.h"

//fd
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

        Entity* CreateEntity();
        void DestroyEntity(size_t entityID);
        Entity* GetEntity(size_t entityID);

        std::vector<Transform>& GetTransforms() { return mTransforms; }
        std::vector<Mesh>& GetMeshes() { return mMeshes; }
        std::vector<Texture>& GetTextures() { return mTextures; }
        std::vector<Movement>& GetMovements() { return mMovements; }
        std::vector<Health>& GetHealths() { return mHealths; }
        std::vector<Tower>& GetTowers() { return mTowers; }
        std::vector<Enemy>& GetEnemies() { return mEnemies; }
        std::vector<Projectile>& GetProjectiles() { return mProjectiles; }
        std::vector<AI>& GetAIs() { return mAIs; }

        void InitializeSystems();
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
