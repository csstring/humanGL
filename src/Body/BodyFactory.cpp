#include "Body/BodyFactory.h"
#include "Character.h"
#include "Skeleton.h"
#include "Body/CollisionCylinder.h"
#include "math/Math.h"
Character* BodyFactory::makeCharacter(const Skeleton& _skeleton, const Controller& controller, CollisionCylinder* collisionMesh)
{
    Character* player = new Character(_skeleton, controller, collisionMesh);
    player->initialize();
    return player;
}

CollisionCylinder* BodyFactory::makeCollisionCylinder(
    physx::PxScene* gScene, 
    physx::PxPhysics* gPhysics, 
    float radius, float height, 
    math::Vec3 position
)
{
    math::Mat4 translate = math::translate(math::Mat4(1.0f), math::Vec3(0,position.y,0)) * math::toMat4(math::rotation(math::Vec3(0,0,1), math::Vec3(0,1,0)));
    CollisionCylinder* _collision = new CollisionCylinder(radius,height,math::Vec3(0.0f), translate);
    _collision->initialize(gPhysics, gScene);
    return _collision;
}

