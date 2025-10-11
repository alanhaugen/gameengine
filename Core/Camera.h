#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

class Camera
{
public:
    Camera();
    ~Camera() {}

    void init();

    void translate(float x, float y, float z);
    void rotate(float t, float x, float y, float z);
    void pitch(float deg);
    void yaw(float deg);
    void moveRight(float delta);
    void moveUp(float delta);

    void setPerspective(float fovy, float screenWidth, float near, float far);
    //void setPerspective(glm::radians(float fovy), float screenWidth, float near, float far);
    void lookAt(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

    inline void setViewMatrix(const glm::mat4 &newViewMatrix) { mViewMatrix = newViewMatrix; }
    inline void setProjectionMatrix(const glm::mat4 &newProjectionMatrix) {mProjectionMatrix = newProjectionMatrix; }
    void setPosition(const glm::vec3 &newPos);
    void setSpeeds(float speed);

    void update();

    //glm::mat4 perspective = (glm::radians(45.0f),( double aspect, double near, double far));

    glm::mat4 mProjectionMatrix{};
    glm::mat4 mViewMatrix{};

    glm::vec3 mPosition = {2.0f, 2.0f, 2.0f};
    glm::vec3 mForward = {0, 0, -1.0};
    glm::vec3 mUp = {0, 0, 1};
    glm::vec3 mTarget = {0.0f, 0.0f, 0.0f};

    float mPitch = 0.f;
    float mYaw = 0.f;

    //Quick hack, since I don't have time anymore:
    float mXSpeed = 0.f;
    float mYSpeed = 0.f;
    float mZSpeed = 0.f;


    // float *ptr = &mSpeed;
};

#endif // CAMERA_H
