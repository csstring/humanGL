#include "IK/EyeIK.h"
#include "GLM/gtx/quaternion.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "EnumHeader.h"
#include "Controller.h"
#include "Character.h"
#include "Bone.h"
#include "IK/IKUtility.h"
#include "Physx.h"
#include "math/Math.h"

math::Vec3 EyeIK::moveInBoneLocalPos(const math::Vec3& start, const math::Vec3& end, const math::Quat& toTargetDir, const math::Vec3& endBoneDir, float ratio)//비율
{
    float distance = math::length(end - start);
    math::Vec3 initialPos = start + endBoneDir * distance;
    math::Vec3 targetPos = start + quatDivideRatio(toTargetDir, ratio) * endBoneDir * distance;
    
    return (targetPos - initialPos); 
}

void EyeIK::blendingRatioUpdate(const std::chrono::steady_clock::time_point& curTime)
{
    std::chrono::milliseconds  millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - _prevTime);
    if (_targetOn == false && _blendingRatio <= 0)
    {
        _prevTime = curTime;
        return;
    }
    else if (_targetOn == false && _blendingRatio > 0)
        _blendingRatio -= static_cast<float>(millisecond.count()) / OVERLAPTIME;
    else if (_targetOn == true && _blendingRatio < 1)
        _blendingRatio += static_cast<float>(millisecond.count()) / OVERLAPTIME;
    if (_blendingRatio > 1) 
        _blendingRatio = 1;
    else if (_blendingRatio < 0) 
        _blendingRatio = 0;
    
    _prevTime = curTime;
}

void EyeIK::solveIK(
    std::vector<BoneLocal>& _boneLocalVector, 
    const math::Mat4& worldRotation, 
    const math::Mat4& worldTranslate, 
    const Controller& controller,
    const std::chrono::steady_clock::time_point& curTime,
    LowerState beforeState,
    Physx* gScene
)
{
    std::vector<math::Vec3> inCharLocalPos;
    std::vector<math::Mat4> inCharLocalRot;

    for (uint32 i : _boneIndexVec)
    {
        math::Mat4 inCharTrans = controller.getMatrixInCharLocal(i, controller.getPlayer()->getCharacterSkeleton(), _boneLocalVector);
        inCharLocalPos.push_back(math::Vec3(inCharTrans * math::Vec4(0,0,0,1)));
        inCharLocalRot.push_back(math::Mat4(math::Mat3(inCharTrans)));
    }

    if (_isFirst == true)
    {
        _isFirst = false;
        _prevTime = curTime;
    }

    math::Mat4 charLocalToWorld = worldTranslate * worldRotation;
    math::Vec3 targetPosInCharLocal = math::Vec3(math::inverse(charLocalToWorld) * math::Vec4(_targetPosition, 1));
    math::Vec3 middleEye = math::mix(*(inCharLocalPos.end()-2), *(inCharLocalPos.end()-1),0.8);
    math::Vec3 targetDir = targetPosInCharLocal - middleEye;
    math::Vec3 curSee = math::Vec3(inCharLocalRot.back() * math::Vec4(math::cross(math::Vec3(1,0,0), _bonedirection.back()),1));
    math::Quat afterSee = math::rotation(math::normalize(curSee), math::normalize(targetDir));

    for (uint32 i : _boneIndexVec)
    {
        math::Quat rot;
        if (i == BONEID::LOWERNECK)
            rot = quatDivideRatio(afterSee,LOWERNECK_RATIO) * _boneLocalVector[i].rotationInBoneLocal;
        else if (i == BONEID::UPPERNECK)
            rot = quatDivideRatio(afterSee,UPPER_RATIO) * _boneLocalVector[i].rotationInBoneLocal;
        else if (i == BONEID::HEAD)
            rot = quatDivideRatio(afterSee,HEAD_RATIO) * _boneLocalVector[i].rotationInBoneLocal;
        else if (i == BONEID::THORAX)
            continue;
        if (limitAngleCheck(_boneVector[i], rot) == false)
        {
            // math::Vec3 deg = quatToEulerDivideRatio(rot, 1) * (180.0f / PI);
            // std::cout << glm::to_string(deg) << std::endl;
            _targetOn = false;
            break;
        }
        _targetOn = true;
    }

    blendingRatioUpdate(curTime);

    for (uint32 i = 0; i < _boneIndexVec.size(); ++i)
    {
        float ratio;
        if (_boneIndexVec[i] == BONEID::LOWERNECK)
            ratio = LOWERNECK_RATIO;
        else if (_boneIndexVec[i] == BONEID::UPPERNECK)
            ratio = UPPER_RATIO;
        else if (_boneIndexVec[i] == BONEID::HEAD)
            ratio = HEAD_RATIO;
        else if (_boneIndexVec[i] == BONEID::THORAX)
            continue;
        math::Quat mixRot = quatDivideRatio(afterSee,ratio) * _boneLocalVector[_boneIndexVec[i]].rotationInBoneLocal;
        math::Vec3 mixTranslate = _boneLocalVector[_boneIndexVec[i]].translationInBoneLocal + moveInBoneLocalPos(inCharLocalPos[i-1], inCharLocalPos[i], afterSee, _bonedirection[i], ratio);
        _boneLocalVector[_boneIndexVec[i]].rotationInBoneLocal = math::slerp(_boneLocalVector[_boneIndexVec[i]].rotationInBoneLocal, mixRot, _blendingRatio);
        _boneLocalVector[_boneIndexVec[i]].translationInBoneLocal = math::mix(_boneLocalVector[_boneIndexVec[i]].translationInBoneLocal, mixTranslate, _blendingRatio);
    }
}