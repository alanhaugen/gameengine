#include "Camera.h"

void Camera::update()
{
    // ***** Rotation ***** :
    // no roll, since that is not needed for now

    mForward = rotateX(glm::vec3{0, 0, -1}, mPitch);
    //rotateY rotates around world up, so this does not roll the camera:
    mForward = rotateY(mForward, mYaw);


    // ***** Movement ***** :

    // move camera along the forward vector:
    mPosition += mForward * mCameraMovement.z;

    // the local right vector of the camera:
    mRight = rotateY(glm::vec3{1, 0, 0}, mYaw);
    // move camera along the right vector:
    mPosition += mRight * mCameraMovement.x;

    // move camera along worldUp vector
    mPosition += mUp * mCameraMovement.y;
}

void Camera::resetMovement()
{
    mCameraMovement = glm::vec3{0};
}
