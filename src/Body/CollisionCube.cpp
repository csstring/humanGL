#include "Body/CollisionCube.h"
#include "physx/PxPhysicsAPI.h"
#include "GL/glew.h"
#include "EnumHeader.h"
#include "Body/Cube.h"
#include "math/Math.h"
void CollisionCube::initialize(physx::PxPhysics* gPhysics, physx::PxScene* gScene)
{

    _cube.initialize();
    _cube._rot = _rot;

    physx::PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    physx::PxBoxGeometry box(_dimensions.x / 2, _dimensions.y / 2, _dimensions.z / 2);
    physx::PxShape* shape = gPhysics->createShape(box, *material);
    
    physx::PxQuat rotation(_rot.x, _rot.y, _rot.z, _rot.w);
    gCubeActor = gPhysics->createRigidStatic(physx::PxTransform(_position.x, _position.y, _position.z, rotation));
    gCubeActor->attachShape(*shape);
    gScene->addActor(*gCubeActor);
}

void CollisionCube::update(math::Quat quat)
{
    _cube._rot = quat * _cube._rot;
    _cube._translate = math::translate(math::Mat4(1.0f), _position);
    _cube.update();
}

void CollisionCube::draw(void)
{
    _cube.draw();
}