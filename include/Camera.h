#pragma once
#include "Common.h"

const float cameraSpeed = 0.5f;
class Camera
{

    public:
        Camera() : _yaw(-90.0f), _pitch(0.0f), _movementSpeed(2.5f), _mouseSensitivity(0.1f), _zoom(45.0f), _isFirst(true)
        {
            _cameraPos = math::Vec3(0,3,30);
            _cameraUp = math::Vec3(0,1,0);
            _cameraFront = math::Vec3(0,0,-1);
            updateCameraVectors();
        };
        ~Camera(){};
        void update(void);
        void initialize(void);
        void ProcessMouseScroll(float yoffset);
        void updateCameraVectors(void);
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);

    private:
        float _yaw;
        float _pitch;
        float _movementSpeed;
        float _mouseSensitivity;
        math::Vec3   _cameraUp;
    
    public:
        float _zoom;
        bool _isFirst;
        float _lastX;
        float _lastY;
        math::Vec3   _cameraPos;
        math::Vec3   _cameraFront;
        math::Vec3   _cameraRight;
        math::Mat4   _view;
};  