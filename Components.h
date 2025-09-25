#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>
#include <vector>


//to avoid naming collisions, we will use namespace bbl - Boba Blast Labs
namespace bbl
{

    enum class ComponentTypes
    {
        transform,
        mesh,
        texture
    };

    struct transform
    {
        glm::vec3 mPosition;
        glm::vec3 mRotation;
        glm::vec3 mScale;
        short mEntityId{-1}; //since it is a signed short int, it can hold -32,768 to 32,767 Integers
    };

    struct mesh
    {
        short mMesh{-1};
        short mEntityId{-1};
    };

    struct texture
    {
        short mTexture{-1};
        short mEntityId{-1};

    };


    //Create vector of the structs so that we at a later time can implement them into different systems
    std::vector<bbl::transform> ComponentTransformVector;
    std::vector<bbl::mesh> ComponentMeshVector;
    std::vector<bbl::texture> ComponentTextureVector;



}   //namespace bbl

#endif // COMPONENT_H
