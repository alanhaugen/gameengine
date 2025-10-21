#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

//Camera now only holds vectors and rotation values. The View and Perspective matrix are made in the Renderer
class Camera
{
public:
    Camera();
    ~Camera() {}

    void init();

    void translate(float x, float y, float z);
    void moveRight(float delta);
    void moveUp(float delta);

    void setPosition(const glm::vec3 &newPos);
    void setSpeeds(float speed);

    void update();

    glm::vec3 mPosition = {0.0f, 0.0f, 2.0f};
    glm::vec3 mForward = {0, 0, -1};
    glm::vec3 mUp = {0, 1, 0};
    glm::vec3 mTarget = {0.0f, 0.0f, 0.0f};

    float mPitch = 0.f;
    float mYaw = 0.f;

    //Quick hack, since I don't have time anymore:
    float mXSpeed = 0.f;
    float mYSpeed = 0.f;
    float mZSpeed = 0.f;


    // float *ptr = &mSpeed;

    //Utility functions - should be in some common place so we can reuse it in all of our code:

    // Rotates vector v by angleEuler degrees around the selected axis
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

    // Rotates vector v by angleEuler degrees around the selected axis
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

    // Rotates vector v by angleEuler degrees around the selected axis
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
