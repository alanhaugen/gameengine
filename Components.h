#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include <vector>

//Need namespace, since we start to get naming collisions with other code
namespace gea {

    //Add new component types here - Extended for tower defense (My addition: Movement, Health, Tower, Enemy, Projectile and AI)
    enum class ComponentTypes
    {
        Transform,
        Mesh,
        Texture,
        Movement,
        Health,
        Tower,
        Enemy,
        Projectile,
        AI
    };

    //Below are examples of actual components
    //Systems need each component to know what entity it belongs to

    struct Transform
    {
        glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };
        glm::vec3 mRotation{ 0.0f, 0.0f, 0.0f };
        glm::vec3 mScale{ 1.0f, 1.0f, 1.0f };
        short mEntityID{ -1 };
    };

    struct Mesh
    {
        short mMesh{-1};        //index into array of all meshes loaded
        short mEntityID{-1};
    };

    struct Texture
    {
        short mTexture{-1};        //index into array of all textures loaded
        short mEntityID{-1};
    };


    //The plan is that the systems can use these vectors containing all components of the different types
    //The components should be sorted by EntityID when added to the vectors.
    //A Render system then might need many vectors, but a Move system might only need one or two.
    //Each system just access the ones they need, and iterates through them and do their job.
    //Since the components are sorted by EntityID, the iteration should go well and we should get DOD benefits.

    // Component vectors - sorted by EntityID for DOD performance
    extern std::vector<gea::Transform> ComponentTransformVector;
    extern std::vector<gea::Mesh> ComponentMeshVector;
    extern std::vector<gea::Texture> ComponentTextureVector;
    extern std::vector<gea::Movement> ComponentMovementVector;
    extern std::vector<gea::Health> ComponentHealthVector;
    extern std::vector<gea::Tower> ComponentTowerVector;
    extern std::vector<gea::Enemy> ComponentEnemyVector;
    extern std::vector<gea::Projectile> ComponentProjectileVector;
    extern std::vector<gea::AI> ComponentAIVector;

}   //namespace gea

#endif // COMPONENTS_H
