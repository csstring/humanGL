#include "Camera.h"
#include "GLFW/glfw3.h"
#include "math/Math.h"
#include "GLM/ext.hpp"
#include "GLM/glm.hpp"

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
    // calculate the new Front vector
    math::Vec3 front;
    front.x = cos(math::radians(_yaw)) * cos(math::radians(_pitch));
    front.y = sin(math::radians(_pitch));
    front.z = sin(math::radians(_yaw)) * cos(math::radians(_pitch));
    _cameraFront = math::normalize(front);
    // also re-calculate the Right and Up vector
    _cameraRight = math::normalize(math::cross(_cameraFront, _cameraUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _cameraUp    = math::normalize(math::cross(_cameraRight, _cameraFront));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }
    updateCameraVectors();
}