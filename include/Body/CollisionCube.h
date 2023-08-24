#pragma once
#include "Cube.h"
#include "Common.h"


class CollisionCube
{
    public:
        Cube  _cube;
        math::Vec3 _position;
        math::Vec3 _dimensions;
        math::Quat _rot;
        physx::PxRigidStatic* gCubeActor = nullptr;
        
    public:
        CollisionCube(math::Vec3 dimensions, math::Vec3 position, math::Quat rot = math::Quat(1.0f, math::Vec3(0.0f)), math::Vec3 color = math::Vec3(0,1,0)) : _cube(dimensions,position, color)
        {
            _position = position;
            _dimensions = dimensions;
            _rot = rot;
        };
        ~CollisionCube(){};
        void initialize(physx::PxPhysics* gPhysics, physx::PxScene* gScene);
        void update(math::Quat quat = math::Quat(1.0f, math::Vec3(0.0f)));
        void draw(void);
};
