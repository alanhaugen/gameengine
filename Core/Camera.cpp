#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    init();
}

void Camera::init()
{
    mProjectionMatrix = glm::mat4(1.0f); //identity
    mProjectionMatrix = glm::perspective(glm::radians(45.0f), 1100 / (float) 800, 0.1f, 10.0f); //hardcoded size to start with
    mViewMatrix = glm::mat4(1.0f); //identity
    mViewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::translate(float x, float y, float z)
{
    glm::vec3 translation(x, y, z);
    mViewMatrix = glm::translate(mViewMatrix, translation);
}

void Camera::rotate(float t, float x, float y, float z)
{
    mViewMatrix = glm::rotate(mViewMatrix, glm::radians(t), glm::vec3(x, y, z));
}

void Camera::pitch(float deg)
{
    mPitch += deg;
}

void Camera::yaw(float deg)
{
    mYaw += deg;
}

void Camera::moveRight(float delta)
{
    mPosition.x = ( mPosition.x + delta);
}

void Camera::moveUp(float delta)
{
    mPosition.y = (mPosition.y + delta);
}

void Camera::update()
{
    mPosition.x += mXSpeed;
    mPosition.y += mYSpeed;
    mPosition.z += mZSpeed;

    // mViewMatrix = glm::mat4(1.0f); //identity
    // mPosition.z = (mPosition.z + mSpeed);

    // mViewMatrix = glm::rotate(mViewMatrix, glm::radians(mPitch), glm::vec3(1.0, 0.0, 0.0));
    // mViewMatrix = glm::rotate(mViewMatrix, glm::radians(mYaw), glm::vec3(0.0, 1.0, 0.0));

    // mViewMatrix = glm::translate(mViewMatrix, mPosition);
}

void Camera::setSpeeds(float speed)
{
    mXSpeed = speed;
    mYSpeed = speed;
    mZSpeed = speed;
}

void Camera::setPosition(const glm::vec3 &newPos)
{
    mPosition = newPos;
    update();
}

void Camera::setPerspective(float fovy, float screenWidth, float near, float far)
{
    mProjectionMatrix = glm::mat4(1.0f); //identity
    mProjectionMatrix = glm::perspective(fovy, screenWidth, near, far);
}

void Camera::lookAt(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
{
    mPosition = position;
    mForward = forward;
    mUp = up;
    mViewMatrix = glm::mat4(1.0f); //identity
    mViewMatrix = glm::lookAt(mPosition, mForward, mUp);
}
