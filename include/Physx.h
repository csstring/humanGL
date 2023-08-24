#pragma once
#include "Common.h"

class Physx : Noncopyable
{
    public:
        physx::PxDefaultAllocator gAllocator;
        physx::PxDefaultErrorCallback gErrorCallback;
        physx::PxFoundation* gFoundation = nullptr;
        physx::PxPhysics* gPhysics = nullptr;
        physx::PxScene* gScene = nullptr;
        physx::PxSimulationEventCallback* _contactCallback = nullptr;

    public:
        Physx(){};
        ~Physx()
        {
            gScene->release();
            gPhysics->release();
            gFoundation->release();
        };
        void Initialize(void);
        bool sweepTestUseSphere(float maxDistance,float radius, math::Vec3 initPose, math::Vec3 direction, physx::PxSweepBuffer &hit);
};