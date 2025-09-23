#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include <vector>

//Need namespace, since we start to get naming collisions with other code
namespace gea{

    //Add new component types here
    enum class ComponentTypes
    {
        Transform,
        Mesh,
        Texture
    };


    //Below are examples of actual components
    //Systems need each component to know what entity it belongs to

    struct Transform
    {
        glm::vec3 mPosition;
        glm::vec3 mRotation;
        glm::vec3 mScale;
        short mEntityID{-1};
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

    std::vector<gea::Transform> ComponentTransformVector;
    std::vector<gea::Mesh> ComponentMeshVector;
    std::vector<gea::Texture> ComponentTextureVector;

}   //namespace gea

#endif // COMPONENTS_H
