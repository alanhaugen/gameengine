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
        texture,
        audio,
        physics,
        collision,
        input
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
        float mVolume{100};
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

    struct Input
    {
        bool W{false};
        bool A{false};
        bool S{false};
        bool D{false};

        bool UP{false};
        bool DOWN{false};
        bool LEFT{false};
        bool RIGHT{false};

        bool Q{false};
        bool E{false};
        bool R{false};
        bool C{false};

        bool LSHIFT{false};
        bool LCTRL{false};
        bool SPACE{false};

        bool RMB{false};    //Glory Mouse
        bool MMB{false};
        bool LMB{false};
        bool MB4{false};
        bool MB5{false};


        float MWHEEL{0.f};  //MouseWheel
        int MOUSEX{0};
        int MOUSEY{0};
    };



    //Create vector of the structs so that we at a later time can implement them into different systems
    inline std::vector<bbl::transform> TransformComponent;
    inline std::vector<bbl::mesh> MeshComponent;
    inline std::vector<bbl::texture> TextureComponent;
    inline std::vector<bbl::audio> AudioComponent;
    inline std::vector<bbl::physics> PhysicsComponent;
    inline std::vector<bbl::collision> CollisionComponent;
    inline std::vector<bbl::Input> InputComponent;

    /////////////////////////////////////////////////////////////////////////



}   //namespace bbl

#endif // COMPONENT_H
