#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    init();
}

void Camera::init()
{
    //Camera now only holds position, forward vector and what pitch and yaw it should do
    //Then in the void Renderer::updateUniformBuffer(...) these values are used to make the viewMatrix
    //Can do the same thing with the values for the perspective matrix

    // mProjectionMatrix = glm::mat4(1.0f); //identity
    // mProjectionMatrix = glm::perspective(glm::radians(45.0f), 1100 / (float) 800, 0.1f, 10.0f); //hardcoded size to start with
    // mViewMatrix = glm::mat4(1.0f); //identity
    // mViewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::translate(float x, float y, float z)
{
    glm::vec3 translation(x, y, z);
    // mViewMatrix = glm::translate(mViewMatrix, translation);
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

    mForward = rotateX(glm::vec3{0, 0, -1}, mPitch);
    mForward = rotateY(mForward, mYaw);

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
