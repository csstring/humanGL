#include "IK/IKInterface.h"
#include "Bone.h"
#include "math/Math.h"
void IKInterface::setTargetPosition(math::Vec3 targetPosition)
{
    _targetPosition = targetPosition;
}

void IKInterface::saveVelocity(math::Vec3 beforePos, math::Vec3 curPos)
{
    float moveDistance = math::length(curPos - beforePos);
    float second = getMilisecondTime(_curTime, _prevTime) / 1000.0f;
    _velocity = moveDistance / second;
}

void IKInterface::initialize(BONEID targetBone, BONEID startBone)
{
    const Bone* curBone = nullptr;
    for (const Bone& bone : _boneVector)
    {
        if (bone._boneIndex == targetBone)
        {
            curBone = &bone;
            break;
        }
    }
    while (true)
    {
        _boneIndexVec.push_back(curBone->_boneIndex);
        _bonedirection.push_back(curBone->_direction);
        curBone = &_boneVector[curBone->_parentBoneIndex];
        if (curBone->_boneIndex == startBone)
            break;
    }
    std::reverse(_boneIndexVec.begin(), _boneIndexVec.end());
}