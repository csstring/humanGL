#include "Skeleton.h"
#include "math/Math.h"

int32 Skeleton::findBoneIndex(const std::string& name) const
{
    for (int i =0; i < _boneVector.size(); ++i)
    {
        if (_boneVector[i]._boneName == name)
            return i;
    }
    return -1;
}

math::Vec3 Skeleton::getCharLocalPosition(BONEID boneID)
{
    math::Mat4 matrix(1.0f);
    const Bone* bone = &_boneVector[boneID];
    while (true)
    {   
        math::Quat localRot = bone->_c * math::quatCast(matrix) * bone->_invC;
        math::Vec3 transV = math::toMat3(localRot) * bone->_b;
        math::Mat4 trans = math::translate(math::Mat4(1.0f), transV);

        matrix = trans * math::toMat4(localRot) * matrix;
        if (bone->_parentBoneIndex == -1)
            break;
        bone = &_boneVector[bone->_parentBoneIndex];
    }
    return math::Vec3(matrix * math::Vec4(0,0,0,1));
}

float Skeleton::getSkeletonHeight(void)
{
    math::Vec3 headPos = getCharLocalPosition(BONEID::HEAD);
    math::Vec3 rfootPos = getCharLocalPosition(BONEID::RFOOT);

    return (headPos.y - rfootPos.y);
}

float Skeleton::getSkeletonWidth(void)
{
    math::Vec3 rightHandPos = getCharLocalPosition(BONEID::RCLAVICLE);
    math::Vec3 leftHandPos = getCharLocalPosition(BONEID::LCLAVICLE);

    return math::length(rightHandPos - leftHandPos);
}