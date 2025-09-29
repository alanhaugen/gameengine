#include "camera.h"

camera::camera()
{
    init();
}

void camera::init()
{
    mProjectionMatrix.setToIdentity();
    mViewMatrix.setToIdentity();
}

void camera::translate(float x, float y, float z)
{
    mViewMatrix.translate(x, y, z);
}

void camera::rotate(float t, float x, float y, float z)
{
    mViewMatrix.rotate(t, x, y, z);
}

void camera::pitch(float deg)
{
    mPitch += deg;
}

void camera::yaw(float deg)
{
    mYaw += deg;
}

void camera::update()
{
    mViewMatrix.setToIdentity();
    mPosition.setZ(mPosition.z() + mSpeed);
    mViewMatrix.rotate(mPitch, 1.0, 0.0, 0.0);
    mViewMatrix.rotate(mYaw, 0.0, 1.0, 0.0);
    mViewMatrix.translate(mPosition);
}

void camera::setPosition(const QVector3D &newPos)
{
    mPosition = newPos;
    update();
}

void camera::setPerspective(float fovy, float screenWidth, float near, float far)
{
    mProjectionMatrix.setToIdentity();
    mProjectionMatrix.perspective(fovy, screenWidth, near, far);
}

void camera::lookAt(QVector3D position, QVector3D forward, QVector3D up)
{
    mPosition = position;
    mForward = forward;
    mUp = up;
    mViewMatrix.setToIdentity();
    mViewMatrix.lookAt(mPosition, mForward, mUp);
}
