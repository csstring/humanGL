#include "IK/FootIK.h"
#include "Controller.h"
#include "Character.h"
#include "Bone.h"
#include "IK/IKUtility.h"
#include "Physx.h"
#include "math/Math.h"
//발바닥 조인트 두개 다 검사
void FootIK::setCharGroundHight(float& charGroundHight)
{
    charGroundHight = _groundHight;
}

void FootIK::setTestOption(math::Vec3 position, math::Vec3 normal, math::Mat4 charLocalToWorld)
{
    _targetOn = true;
    _targetPosition = math::inverse(charLocalToWorld) * math::Vec4(position,1);
    _groundNormal = math::inverse(charLocalToWorld) * math::Vec4(normal,0);
}

void FootIK::isOffGroundCheck(
    const std::vector<math::Vec3>& inCharLocalPos, 
    Physx* physx, 
    math::Mat4 charLocalToWorld)
{
    bool curIsOffGround;
    math::Vec3 footPos = charLocalToWorld * math::Vec4(inCharLocalPos[3],1);
    math::Vec3 tibiaPos = charLocalToWorld * math::Vec4(inCharLocalPos[2],1);
    math::Vec3 femurPos = charLocalToWorld * math::Vec4(inCharLocalPos[1],1);

    math::Vec3 startPos = math::mix(footPos, tibiaPos, 0.5f);
    startPos.y +=5;
    physx::PxSweepBuffer hit;
    physx::PxVec3 sweepDirection(0,-1,0);
    physx::PxTransform initialPose(physx::PxVec3(startPos.x, startPos.y, startPos.z));
    physx::PxSphereGeometry sphere(0.1);

    bool hitFlag = physx->gScene->sweep(sphere, initialPose, sweepDirection, 10, hit);
    
    if (hitFlag == false || abs(5 - hit.block.distance) >= 0.3)
        _isOffGround = true;
    else
        _isOffGround = false;
}

bool FootIK::isStartFindTarget(const std::vector<math::Vec3>& inCharLocalPos)
{
    if (inCharLocalPos[2].y - inCharLocalPos[3].y > 0.98)
        return true;
    return false;
}


bool FootIK::findTargetObject(
    const std::vector<math::Vec3>& inCharLocalPos, 
    Physx* physx, 
    math::Mat4 charLocalToWorld,
    math::Vec3 tmpMoveDir
)
{
    math::Vec3 tibiaPos = charLocalToWorld * math::Vec4(inCharLocalPos[3],1);
    math::Vec3 targetPos;
    // if (tmpMoveDir == math::Vec3(0.0f))
    //     tibiaPos = charLocalToWorld * math::Vec4(_prevTibiaPos,1);
   
    targetPos = tibiaPos + tmpMoveDir;
    targetPos.y += 5;//fix

    physx::PxSweepBuffer hit;
    math::Vec3 sweepDirection(0,-1,0);
    float radius = 1.0f / 5.0f;
    bool hitFlag = physx->sweepTestUseSphere(20, radius, targetPos, sweepDirection, hit);

    if (hitFlag == false || abs(5 - hit.block.distance) >= 5)
    {
        // if (hitFlag == false)
        //     // std::cout << "hit fail" << std::endl;
        // else
            // std::cout << "distance fail : " << glm::abs(5-hit.block.distance) << std::endl;
        return false;
    }
    
    math::Vec3 worldTarget(hit.block.position.x, hit.block.position.y, hit.block.position.z);
    math::Vec3 worldNormal(hit.block.normal.x, hit.block.normal.y, hit.block.normal.z);
    std::vector<float> disVector;
    stairDir tmpDir;
        
    if (worldTarget.y > tibiaPos.y + 0.1)
        tmpDir = stairDir::UPSTAIR;
    else if (worldTarget.y < tibiaPos.y - 0.1)
        tmpDir = stairDir::DOWNSTAIR;
    else
        tmpDir = stairDir::NORMAL;

    //reach fail
    if (reachable(inCharLocalPos,disVector ,math::inverse(charLocalToWorld) * math::Vec4(worldTarget,1)) == false && tmpDir != stairDir::DOWNSTAIR)
        return false;

    if (tmpMoveDir != math::Vec3(0.0f))
        _stairDir = tmpDir;
            
    _targetPosition = math::inverse(charLocalToWorld) * math::Vec4(worldTarget,1);
    _groundNormal = math::inverse(charLocalToWorld) * math::Vec4(worldNormal, 0);
    _targetOn = true;
    _groundHight = hit.block.position.y;
    _curTouchBody = hit.block.actor;
    
    return true;
}

bool FootIK::reachable(const std::vector<math::Vec3>& inCharacterPos, std::vector<float>& distance, math::Vec3 footPosition)
{
    math::Vec3 start = inCharacterPos.front();
    math::Vec3 end = inCharacterPos.back();
    float targetDistance = math::length(footPosition - start);
    float curDistance = 0;
    for (uint32 i = 1; i < inCharacterPos.size(); ++i)
    {
        end = inCharacterPos[i];
        distance.push_back(math::length(start - end));
        start = end;
    }
    curDistance = distance[0] + distance[1];
    if (curDistance < targetDistance)
        return true;
    return true;
}

void FootIK::positionFixLimitAngleBackWard(math::Vec3& start, math::Vec3& end, math::Vec3 endBoneDir,const Bone& endBone)
{
    math::Vec3 initialDirection = math::normalize(end - start);
    math::Vec3 targetDirection = math::normalize(endBoneDir);
    math::Quat rotation = math::rotation(initialDirection, targetDirection);
    math::Vec3 eulerAngle = math::eulerAngles(rotation);

    for (auto& limit : endBone._limits)
    {
        DOF dof;
        float min, max;
        std::tie(dof, min, max) = limit;
        if (dof == DOF::RX)
            eulerAngle.x = std::clamp(eulerAngle.x, min, max);
        else if (dof == DOF::RY)
            eulerAngle.y = std::clamp(eulerAngle.y, min, max);
        else if (dof == DOF::RZ)
            eulerAngle.z = std::clamp(eulerAngle.z, min, max);
    }
    rotation = math::Quat(eulerAngle);

    math::Vec3 correctPos = math::inverse(rotation) * targetDirection * math::length(end - start);

    start = end - correctPos;

}

void FootIK::positionFixLimitAngleForWard(math::Vec3& start, math::Vec3& end, math::Vec3 startBoneDir,const Bone& endBone)
{
    math::Vec3 initialDirection = math::normalize(startBoneDir);
    math::Vec3 targetDirection = math::normalize(end - start);
    math::Quat rotation = math::rotation(initialDirection, targetDirection);
    math::Vec3 eulerAngle = math::eulerAngles(rotation);

    for (auto& limit : endBone._limits)
    {
        DOF dof;
        float min, max;
        std::tie(dof, min, max) = limit;
        if (dof == DOF::RX)
            eulerAngle.x = std::clamp(eulerAngle.x, min, max);
        else if (dof == DOF::RY)
            eulerAngle.y = std::clamp(eulerAngle.y, min, max);
        else if (dof == DOF::RZ)
            eulerAngle.z = std::clamp(eulerAngle.z, min, max);
    }
    rotation = math::Quat(eulerAngle);

    math::Vec3 correctPos = rotation * initialDirection * math::length(end - start);
    end = start + correctPos;
}

void FootIK::fixBendingAngle(math::Vec3& start, math::Vec3& mid, math::Vec3& end)
{
    math::Vec3 angle1 = math::normalize(start - mid);
    math::Vec3 angle2 = math::normalize(end - mid);
    math::Quat bendRot = math::rotation(angle1, angle2);

    if (math::axis(bendRot).x < 0)
        return;

    angle1 = math::normalize(mid - start);
    angle2 = math::normalize(end - start);
    bendRot = math::rotation(angle1, angle2);
    
    math::Vec3 dir = bendRot * angle2;
    mid = start + dir * math::length(start - mid);

    angle1 = math::normalize(start - mid);
    angle2 = math::normalize(end - mid);
    bendRot = math::rotation(angle1, angle2);

    if (math::axis(bendRot).x > 0)
    {
        // std::cout << "bend fix check" << std::endl;
        return;
    }
}

bool FootIK::saveBlendingAnimation(std::vector<math::Vec3>& inCharLocalPos, std::vector<math::Mat4>& inCharLocalRot, math::Vec3 curFootPos)
{
    std::vector<float> distance;
    math::Vec3 parentDir = math::normalize(inCharLocalPos[2] - inCharLocalPos[3]);
    math::Quat rot = math::rotation(_groundNormal, parentDir);
    math::Vec3 axis = math::axis(rot);
    float radians = math::radians(90.0f) - math::angle(rot);
    math::Vec3 groundDir = math::angleAxis(radians, axis) * parentDir;
    groundDir = math::mix(parentDir, groundDir, _blendingRatio);

    math::Vec3 tmpTarget = curFootPos;
    if (_targetPosition.y > _firstHitHight)
        tmpTarget.y = math::mix(tmpTarget.y, _targetPosition.y, _blendingRatio);
    else
        tmpTarget.y = math::mix(tmpTarget.y, _firstHitHight, _blendingRatio);

    if (_bonePos[0].y == 0)
        _bonePos[0].y = _targetPosition.y - inCharLocalPos[3].y;
    math::Vec3 footPosInChar = tmpTarget + groundDir * math::length(inCharLocalPos[2] - inCharLocalPos[3]);
    
    if (reachable(inCharLocalPos, distance, footPosInChar) == false)//fix me 
    {}
    
    math::Vec3 start = inCharLocalPos.front();
    uint32 iterCount = 0;
    while (math::length(footPosInChar - inCharLocalPos[2]) > 0.1)
    {
        iterCount++;
        if (iterCount >= 30)
        {
            // std::cout << "Fook ik length val : " << glm::length(footPosInChar - inCharLocalPos[2]) << std::endl;
            return false;
        }
            
        inCharLocalPos[2] = footPosInChar;
        math::Vec3 BoneDir;
        for(uint16 i = _boneIndexVec.size()-2; i >=1; --i)
        {
            float r = math::length(inCharLocalPos[i] - inCharLocalPos[i-1]);
            float k = distance[i-1] / r;
            inCharLocalPos[i-1] = math::mix(inCharLocalPos[i], inCharLocalPos[i-1], k);
            if (i-1 == 1)
                fixBendingAngle(start, inCharLocalPos[1], footPosInChar);
            BoneDir = inCharLocalPos[i+1] - inCharLocalPos[i];
            // positionFixLimitAngleBackWard(inCharLocalPos[i-1], inCharLocalPos[i], BoneDir ,_boneVector[_boneIndexVec[i+1]]);
        }

        inCharLocalPos.front() = start;
        for(uint16 i = 0; i < _boneIndexVec.size()-2; ++i)//1 2 
        {
            float r = math::length(inCharLocalPos[i] - inCharLocalPos[i+1]);
            float k = distance[i] / r;
            inCharLocalPos[i+1] = math::mix(inCharLocalPos[i], inCharLocalPos[i+1], k);
            if (i+1 == 1)
                fixBendingAngle(start, inCharLocalPos[1], footPosInChar);
            if (i == 0)
                BoneDir = inCharLocalRot[i] * math::Vec4(_boneVector[_boneIndexVec[0]]._direction,0);
            else
                BoneDir = inCharLocalPos[i] - inCharLocalPos[i-1];
            positionFixLimitAngleForWard(inCharLocalPos[i], inCharLocalPos[i+1], BoneDir, _boneVector[_boneIndexVec[i+1]]);
        }
    }

    inCharLocalPos[3] = tmpTarget;
    for (int i = 3; i >= 1; --i)
    {
        math::Vec3 inCharDir = math::normalize(inCharLocalPos[i] - inCharLocalPos[i-1]);
        inCharLocalRot[i] = math::toMat4(math::rotation(_boneVector[_boneIndexVec[i]]._direction ,inCharDir));
  
        math::Mat4 trans = math::translate(math::Mat4(1.0f), inCharLocalPos[i-1]) * inCharLocalRot[i-1];
        _bonePos[i] = math::inverse(trans) * math::Vec4(inCharLocalPos[i], 1);
        _boneRot[i] = math::Quat(math::inverse(trans) * inCharLocalRot[i]);
    }

    return true;
}

void FootIK::solveIK(
    std::vector<BoneLocal>& _boneLocalVector, 
    const math::Mat4& worldRotation, 
    const math::Mat4& worldTranslate, 
    const Controller& controller,
    const std::chrono::steady_clock::time_point& curTime,
    LowerState curState,
    Physx* physx
)
{
    _curTime = curTime;
    std::vector<math::Vec3> inCharLocalPos;
    std::vector<math::Mat4> inCharLocalRot;
    std::vector<math::Mat4> inCharTrans;
    std::vector<float> distance;

    for (uint32 i : _boneIndexVec)
    {
        inCharTrans.push_back(controller.getMatrixInCharLocal(i, controller.getPlayer()->getCharacterSkeleton(), _boneLocalVector));
        inCharLocalPos.push_back(inCharTrans.back() * math::Vec4(0,0,0,1));
        inCharLocalRot.push_back(math::Mat3(inCharTrans.back()));
    }
    math::Mat4 charLocalToWorld = worldTranslate * worldRotation;

    if (_isFirst == true)
    {
        _isFirst = false;
        _prevTime = _curTime;
    }
    //save velocity
    {
        math::Vec3 beforePos = charLocalToWorld * math::Vec4(0,0,0,1);
        math::Mat4 curRootTrans = controller.getMatrixInCharLocal(BONEID::ROOT, controller.getPlayer()->getCharacterSkeleton(), _boneLocalVector);
        math::Vec3 curPos = charLocalToWorld * curRootTrans * math::Vec4(0,0,0,1);
        saveVelocity(beforePos, curPos);
    }

    //get delta time, prevTime update
    {
        _deltaMilisecond = getMilisecondTime(_curTime ,_prevTime);
        _prevTime = _curTime;
    }

    if (isStartFindTarget(inCharLocalPos) && _isRootAnimationOn == false && _rootRatio <= 0)// || _retargetTime >= 1000)
    {   
        math::Mat4 rootTrans = charLocalToWorld * controller.getMatrixInCharLocal(BONEID::ROOT, controller.getPlayer()->getCharacterSkeleton(), _boneLocalVector);
        math::Vec3 foot1Pos = controller.getMatrixInCharLocal(BONEID::RFOOT, controller.getPlayer()->getCharacterSkeleton(), _boneLocalVector) * math::Vec4(0,0,0,1);
        math::Vec3 foot2Pos = controller.getMatrixInCharLocal(BONEID::LFOOT, controller.getPlayer()->getCharacterSkeleton(), _boneLocalVector) * math::Vec4(0,0,0,1);
        foot1Pos.y = 0;
        foot2Pos.y = 0;
        math::Vec3 moveDir = math::length(foot1Pos - foot2Pos) * 1.6f *  math::normalize(rootTrans * math::Vec4(0,0,1,0));

        if (findTargetObject(inCharLocalPos, physx, charLocalToWorld, moveDir) == true)
        {
            _isMoveAnimation = true;
            _bonePos[0].y = 0;
            _rootRatio = 1;
            _blendingRatio = 0;
            _isRootAnimationOn = false;
        }
    }
    else if (_isMoveAnimation == false)
    {
        if (findTargetObject(inCharLocalPos, physx, charLocalToWorld, math::Vec3(0.0f)) == true)
        {
            _bonePos[0].y = 0;
            _rootRatio = 0;
            _isRootAnimationOn = false;
        }
    }

    if (_retargetTime >= 1000)
        _retargetTime = 0;
    _retargetTime += _deltaMilisecond;

    if (_blendingRatio <= 0.0f && _targetOn == false && _isRootAnimationOn == false && _rootRatio <= 0)
        return ;

    blendingRatioUpdate();

    _firstHitHight = getFirstHitHight(charLocalToWorld, inCharLocalPos[3], physx);
    bool saveAnimation = saveBlendingAnimation(inCharLocalPos, inCharLocalRot, inCharLocalPos[3]);

    //debug
    if (saveAnimation == false)
    {
        // std::cout <<"save fail" << std::endl;
        // std::cout << _bonePos[0].y << std::endl;
        // std::cout << "_stairDir " << (uint32)_stairDir << std::endl;
        // std::cout << "target pos" << glm::to_string(_targetPosition) << std::endl;
        // std::cout <<"is root animation " << _isRootAnimationOn << std::endl;
        // std::cout <<"rootRatio " << _rootRatio << std::endl;
        // std::cout <<"_blendingRatio" << _blendingRatio << std::endl;
        // std::cout <<"_isMoveAnimation" << _isMoveAnimation << std::endl;
        // std::cout <<"_targetOn " << _targetOn << std::endl;
    } else {
        // std::cout << "foot pos" << glm::to_string(charLocalToWorld * math::Vec4(inCharLocalPos[2],1)) << std::endl;
        // std::cout << "tibia pos" << glm::to_string(charLocalToWorld * math::Vec4(inCharLocalPos[3],1)) << std::endl;
        // std::cout << "target pos" << glm::to_string(charLocalToWorld * math::Vec4(_targetPosition,1)) << std::endl;
        // std::cout <<"_targetOn " << _targetOn << std::endl;
        // std::cout <<"_blendingRatio" << _blendingRatio << std::endl;
    }

    _prevTibiaPos = inCharLocalPos[3];
    if (_isRootAnimationOn == true || (_stairDir == stairDir::DOWNSTAIR && _rootRatio > 0))
    {
        float rootRatioDelta = _deltaMilisecond / 200.0f;
        if (rootRatioDelta > _rootRatio)
            rootRatioDelta = _rootRatio;
        _boneLocalVector[BONEID::ROOT].translationInBoneLocal = math::mix(_boneLocalVector[BONEID::ROOT].translationInBoneLocal,_bonePos[0], rootRatioDelta);
        _rootRatio -= rootRatioDelta;
    }

    if (saveAnimation == true)
    {
        for (int i=3; i >=1; --i)
        {
            // std::cout << std::to_string(_boneIndexVec[i]) << " : " << glm::to_string(_bonePos[i]) << std::endl;
            // std::cout <<std::to_string(_boneIndexVec[i]) << " : " << glm::to_string(_boneLocalVector[_boneIndexVec[i]].translationInBoneLocal) << std::endl;
            _boneLocalVector[_boneIndexVec[i]].translationInBoneLocal = _bonePos[i];
            _boneLocalVector[_boneIndexVec[i]].rotationInBoneLocal = _boneRot[i];
        }
    }

    //move change
    if (_isMoveAnimation == true && _blendingRatio == 0 && _rootRatio == 0 && _targetOn == false && _isRootAnimationOn == false)
        _isMoveAnimation = false;
}

float FootIK::getFirstHitHight(const math::Mat4& charLocalToWorld, const math::Vec3& inCharPos, Physx* physx)
{
    physx::PxSweepBuffer hit;
    math::Vec3 sweepDirection(0,-1,0);
    math::Vec4 inWorldPos = charLocalToWorld * math::Vec4(inCharPos, 1);
    inWorldPos.y += 5;
    bool hitFlag = physx->sweepTestUseSphere(100, 0.3, inWorldPos, sweepDirection, hit);
    inWorldPos = math::Vec4(hit.block.position.x, hit.block.position.y, hit.block.position.z,1);

    math::Vec3 inCharHitPos = math::inverse(charLocalToWorld) * inWorldPos;
    if (hitFlag == false)
        return -100000;
    else
        return inCharHitPos.y;
}

void FootIK::blendingRatioUpdate(void)
{
    if (_targetOn == false && _blendingRatio > 0)
        _blendingRatio -= _deltaMilisecond / 125.0f;
    else if (_targetOn == true && _blendingRatio < 1.0f)
        _blendingRatio += _deltaMilisecond / 250.0f;
    if (_blendingRatio >= 1.0f)
    {
        _blendingRatio = 1;
        _targetOn = false;
        _isRootAnimationOn = true;
    } 
    else if (_blendingRatio < 0)
    {
        _blendingRatio = 0;
    }
    if (_rootRatio <= 0)
       _isRootAnimationOn = false;
}