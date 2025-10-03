#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <memory>
#include "Entity.h"
#include "Components.h"

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
        std::vector<RigidBody>& GetRigidBodies() { return mRigidbodies; }
        std::vector<CollisionSphere>& GetCollisionSpheres() { return mCollisionSpheres; }
        //void RegisterSystem(std::unique_ptr<System> system);

    private:
        //where we store entities
        std::vector<Entity> mEntities;
        //.. and components
        std::vector<Transform> mTransforms;
        std::vector<Mesh> mMeshes;
        std::vector<Texture> mTextures;
        std::vector<Movement> mMovements;
        std::vector<Health> mHealths;
        std::vector<Tower> mTowers;
        std::vector<Enemy> mEnemies;
        std::vector<Projectile> mProjectiles;
        std::vector<AI> mAIs;
        std::vector<RigidBody> mRigidbodies;
        std::vector<CollisionSphere> mCollisionSpheres;
        //systems storage
        std::vector<std::unique_ptr<System>> mSystems;
        //renderer
        Renderer* mRenderer{nullptr};

        void InitializeSystems();
    };

// ============================================================================
// Template implementations - MUST be after Engine class is fully defined (Used AI for this structure)
// ============================================================================

    template<typename T>
    T* Entity::GetComponent(ComponentTypes type)
    {
        if (!mEngine) return nullptr;

        short index = GetComponentIndex(type);
        if (index == -1) return nullptr;

        if constexpr (std::is_same_v<T, Transform>) {
            return &mEngine->GetTransforms()[index];
        }
        else if constexpr (std::is_same_v<T, Mesh>) {
            return &mEngine->GetMeshes()[index];
        }
        else if constexpr (std::is_same_v<T, Texture>) {
            return &mEngine->GetTextures()[index];
        }
        else if constexpr (std::is_same_v<T, Movement>) {
            return &mEngine->GetMovements()[index];
        }
        else if constexpr (std::is_same_v<T, Health>) {
            return &mEngine->GetHealths()[index];
        }
        else if constexpr (std::is_same_v<T, Tower>) {
            return &mEngine->GetTowers()[index];
        }
        else if constexpr (std::is_same_v<T, Enemy>) {
            return &mEngine->GetEnemies()[index];
        }
        else if constexpr (std::is_same_v<T, Projectile>) {
            return &mEngine->GetProjectiles()[index];
        }
        else if constexpr (std::is_same_v<T, AI>) {
            return &mEngine->GetAIs()[index];
        }
        else if constexpr (std::is_same_v<T, RigidBody>) {
            return &mEngine->GetRigidBodies()[index];
        }
        else if constexpr (std::is_same_v<T, CollisionSphere>) {
            return &mEngine->GetCollisionSpheres()[index];
        }

        return nullptr;
    }

    template<typename T>
    void Entity::AddComponent(const T& component)
    {
        if (!mEngine) { return; }

        ComponentTypes type;

        if constexpr (std::is_same_v<T, Transform>)
        {
            type = ComponentTypes::Transform;

            if (HasComponent(type)) { return; }

            Transform newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetTransforms().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetTransforms().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, Mesh>)
        {
            type = ComponentTypes::Mesh;

            if (HasComponent(type)) { return; }

            Mesh newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetMeshes().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetMeshes().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, Texture>)
        {
            type = ComponentTypes::Texture;

            if (HasComponent(type)) { return; }

            Texture newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetTextures().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetTextures().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, Movement>)
        {
            type = ComponentTypes::Movement;

            if (HasComponent(type)) { return; }

            Movement newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetMovements().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetMovements().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, Health>)
        {
            type = ComponentTypes::Health;

            if (HasComponent(type)) { return; }

            Health newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetHealths().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetHealths().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, Tower>)
        {
            type = ComponentTypes::Tower;

            if (HasComponent(type)) { return; }

            Tower newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetTowers().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetTowers().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, Enemy>)
        {
            type = ComponentTypes::Enemy;

            if (HasComponent(type)) { return; }

            Enemy newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetEnemies().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetEnemies().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, Projectile>)
        {
            type = ComponentTypes::Projectile;

            if (HasComponent(type)) { return; }

            Projectile newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetProjectiles().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetProjectiles().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, AI>)
        {
            type = ComponentTypes::AI;

            if (HasComponent(type)) { return; }

            AI newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetAIs().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetAIs().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, RigidBody>)
        {
            type = ComponentTypes::RigidBody;

            if (HasComponent(type)) { return; }

            RigidBody newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetRigidBodies().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetRigidBodies().size() - 1;
            mComponents.push_back(ec);
        }
        else if constexpr (std::is_same_v<T, CollisionSphere>) {
            type = ComponentTypes::CollisionSphere;

            if (HasComponent(type)) { return; }

            CollisionSphere newComp = component;
            newComp.mEntityID = mEntityID;
            mEngine->GetCollisionSpheres().push_back(newComp);

            EntityComponents ec;
            ec.mComponentType = type;
            ec.mComponentIndex = mEngine->GetCollisionSpheres().size() - 1;
            mComponents.push_back(ec);
        }
    }

}

#endif // ENGINE_H
