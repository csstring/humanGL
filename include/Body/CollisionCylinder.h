#pragma once
#include "Cylinder.h"
#include "Common.h"

class CollisionCylinder
{
public:
    uint32 _VAO, _VBO, _VCO;
    float _radius, _height;
    Cylinder  _cylinder;
    math::Vec3 _position;
    physx::PxRigidDynamic* gCylinderActor = nullptr;
public:
    CollisionCylinder(float radius, float height, math::Vec3 position, math::Mat4 cylinderRot) : _cylinder(radius,height,12, cylinderRot)
    {
        _position = position;
        _radius = radius;
        _height = height;
    };
    ~CollisionCylinder(){};
    void UpdateCylinderPosition(const math::Vec3& position);
    void initialize(physx::PxPhysics* gPhysics, physx::PxScene* gScene);
    void update(math::Mat4 translate);
    void draw(void);
};
