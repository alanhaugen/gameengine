#ifndef ENGINE_H
#define ENGINE_H

#include "Entity.h"
#include "Components.h"
#include "Mesh.h"
#include "RenderSystem.h"
#include "Texture.h"

namespace gea {

    class Engine
    {
    public:

        Engine(Renderer* renderer);

        bool mIsRunning{false};
        const long long mUpdateInterval = 10000000; // 10ms in nanoseconds (10^7)
        void GameLoop();

        void UpdateRenderSystem();
        void SetupRenderSystem();

        gea::RenderSystem* mRenderSystem{nullptr};
        Renderer* mVulkanRenderer{nullptr};

        // to Add/Remove entity
        Entity* CreateEntity();
        void DestroyEntity(std::size_t entityID);

        // to add component
        Transform *AddTransform(Entity* entity);
        Movement* AddMovement(Entity* entity);
        Health* AddHealth(Entity* entity);
        Tower* AddTower(Entity* entity);
        Enemy* AddEnemy(Entity* entity);
        Projectile* AddProjectile(Entity* entity);

        // It sort all component vectors by EntityID
        void SortComponents();

        // It is game loop
        void Update(float deltaTime); // Calls all system update functions

        //Vector that holds all the Entities in our game:
        std::vector<Entity> mEntityVector;

        //Vectors that holds all the Components
        //should sorted by EntityID for DOD performance
        std::vector<Transform> mTransformComponents;
        std::vector<Mesh> mMeshComponents;
        std::vector<Texture> mTextureComponents;
        std::vector<Movement> mMovementComponents;
        std::vector<Health> mHealthComponents;
        std::vector<Tower> mTowerComponents;
        std::vector<Enemy> mEnemyComponents;
        std::vector<Projectile> mProjectileComponents;
        std::vector<AI> mAIComponents;
        std::vector<Material> mMaterialComponents;
        std::vector<Model> mModelComponents;
        std::vector<Sound> mSoundComponents;

        //RenderTesting
        std::vector<gea::RenderComponent> mRenderComponents;
        std::vector<gea::RenderComponent> mStaticRenderComponents;
        //this is done for testing sake. in the real ecs there would only be one vector of transform components
        std::vector<gea::Transform> mStaticTransformComponents;

        //The plan is that the systems can use these vectors containing all components of the different types
        //The components should be sorted by EntityID when added to the vectors.
        //A Render system then might need many vectors, but a Move system might only need one or two.
        //Each system just access the ones they need, and iterates through them and do their job.
        //Since the components are sorted by EntityID, the iteration should go well and we should get DOD benefits.
    };
}

#endif
