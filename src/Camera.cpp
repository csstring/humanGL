#include "Camera.h"
#include "GLFW/glfw3.h"
#include "math/Math.h"

void Camera::update(void)
{
    _view = math::lookAt(_cameraPos, _cameraPos+_cameraFront, _cameraUp);
}

void Camera::initialize(void)
{
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    _zoom -= (float)yoffset;
    if (_zoom < 1.0f)
        _zoom = 1.0f;
    if (_zoom > 45.0f)
        _zoom = 45.0f;
}

void Camera::updateCameraVectors()
{

    math::Vec3 front;
    front.x = cos(math::radians(_yaw)) * cos(math::radians(_pitch));
    front.y = sin(math::radians(_pitch));
    front.z = sin(math::radians(_yaw)) * cos(math::radians(_pitch));
    _cameraFront = math::normalize(front);

    _cameraRight = math::normalize(math::cross(_cameraFront, _cameraUp));  
    _cameraUp    = math::normalize(math::cross(_cameraRight, _cameraFront));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;


    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }
    updateCameraVectors();
}