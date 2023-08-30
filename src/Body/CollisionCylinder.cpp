#include "Body/CollisionCylinder.h"
#include "physx/PxPhysicsAPI.h"
#include "GL/glew.h"
#include "EnumHeader.h"
void CollisionCylinder::initialize(physx::PxPhysics* gPhysics, physx::PxScene* gScene)
{
    ///실린더 init으로 빼야 할 부분
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_VCO);
    glBindBuffer(GL_ARRAY_BUFFER, _VCO);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    _cylinder.initialize(math::Vec3(0,1,0), _VCO, BONEID::THORAX);

    physx::PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    physx::PxCapsuleGeometry capsule(_radius, _height/2);
    physx::PxShape* shape = gPhysics->createShape(capsule, *material);
    physx::PxFilterData filterData;
    filterData.word0 = 1; 
    shape->setSimulationFilterData(filterData);

    gCylinderActor = gPhysics->createRigidDynamic(physx::PxTransform(_position.x, _position.y, _position.z));
    gCylinderActor->attachShape(*shape);
    gScene->addActor(*gCylinderActor);
}
//collision update fix me
// void Physx::UpdateCylinderPosition(const math::Vec3& position) 
// {
//     gCylinderActor->setGlobalPose(PxTransform(position.x, position.y, position.z));
// }
void CollisionCylinder::update(math::Mat4 translate)
{
    math::Vec3 pos = math::Vec3(translate * math::Vec4(0,0,0,1));
    gCylinderActor->setGlobalPose(physx::PxTransform(pos.x, pos.y, pos.z));
    auto copy = gCylinderActor->getGlobalPose().p;
    math::Vec3 copy1 = math::Vec3(copy.x, copy.y, copy.z);
    for (uint32 i = 0; i < _cylinder._buffer.size(); ++i)
    {
        _cylinder._buffer[i] = translate * _cylinder._vertices[i];
    }
}

void CollisionCylinder::draw(void)
{
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * _cylinder._buffer.size(), _cylinder._buffer.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_LINES, 0, _cylinder._numVerticesSide);
    glDrawArrays(GL_LINE_LOOP, _cylinder._numVerticesSide+1, _cylinder._numVerticesTopBottom-1);
    glDrawArrays(GL_LINE_LOOP, _cylinder._numVerticesSide + _cylinder._numVerticesTopBottom+1, _cylinder._numVerticesTopBottom-1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}