#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>
#include <string>
#include <vector>


//to avoid naming collisions, we will use namespace bbl - Boba Blast Labs
namespace bbl
{

    enum class ComponentTypes
    {
        transform,
        mesh,
        texture,
        audio,
        physics,
        collision
    };

    struct transform
    {
        glm::vec3 mPosition{};
        glm::vec3 mRotation{};
        glm::vec3 mScale{1, 1, 1};
        short mEntityId{-1};
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

    struct audio
    {
        std::string mAUDIO_FILE{};
        short mEntityId{-1};
    };

    struct physics
    {
        float mDeltaTime{0.016f};
        float mGravity{9.81f};
        short mEntityId{-1};
    };

    struct collision
    {
        bool isColliding{};
        short mEntityId{-1};
    };


    //Create vector of the structs so that we at a later time can implement them into different systems
    std::vector<bbl::transform> ComponentTransformVector;
    std::vector<bbl::mesh> ComponentMeshVector;
    std::vector<bbl::texture> ComponentTextureVector;
    std::vector<bbl::audio> ComponentAudioVector;
    std::vector<bbl::physics> ComponentPhysicsVector;
    std::vector<bbl::collision> ComponentCollisionVector;



    /////////////////////////////////////////////////////////////////////////



}   //namespace bbl

#endif // COMPONENT_H
