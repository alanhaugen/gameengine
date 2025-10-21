#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

//Camera now only holds vectors and rotation values. The View and Perspective(Projection) matrix are made in the Renderer
class Camera
{
public:
    Camera() {}
    ~Camera() {}

    // Reset movement from last frame
    void resetMovement();

    // Update position, forward and right vector based on input
    void update();


    glm::vec3 mPosition {0.0f, 0.0f, 2.0f};
    glm::vec3 mForward {0, 0, -1};  // Forward vector local to the camera
    glm::vec3 mRight {1, 0, 0};     // Right vector local to the camera
    glm::vec3 mUp {0, 1, 0};        // Using world up

    float mPitch {0.f};     // The pitch of the camera - in Euler angle
    float mYaw {0.f};       // The yaw of the camera - in Euler angle

    // How much should the camera move next frame in cameraForward coordinates
    glm::vec3 mCameraMovement{0, 0, 0};


    // ******* Utility functions - should be in some common place so we can reuse it in all of our code:

    // Rotates vector v by angleEuler degrees around the selected world axis
    glm::vec3 rotateX(const glm::vec3& v, float angleEuler)
    {
        float angleRad = glm::radians(angleEuler);
        float c = cos(angleRad);
        float s = sin(angleRad);
        return glm::vec3
            (
            v.x,
            c * v.y - s * v.z,
            s * v.y + c * v.z
            );
    }

    // Rotates vector v by angleEuler degrees around the selected world axis
    glm::vec3 rotateY(const glm::vec3& v, float angleEuler)
    {
        float angleRad = glm::radians(angleEuler);
        float c = cos(angleRad);
        float s = sin(angleRad);
        return glm::vec3
            (
            c * v.x + s * v.z,
            v.y,
            -s * v.x + c * v.z
            );
    }

    // Rotates vector v by angleEuler degrees around the selected world axis
    glm::vec3 rotateZ(const glm::vec3& v, float angleEuler)
    {
        float angleRad = glm::radians(angleEuler);
        float c = cos(angleRad);
        float s = sin(angleRad);
        return glm::vec3
            (
            c * v.x - s * v.y,
            s * v.x + c * v.y,
            v.z
            );
    }
};

#endif // CAMERA_H
