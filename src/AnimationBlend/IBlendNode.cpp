#include "AnimationBlend/IBlendNode.h"
#include "BoneLocal.h"
#include "math/Math.h"
#include <queue>

inline bool pairCompare(const std::pair<uint32, math::Quat>& a, const uint32& val)
{
    return a.first < val;
}

void IBlendNode::getTransFormByKeyFrame(math::Quat& interpolR, math::Vec3& interpolT, const AnimationData* node, uint32 keyFrame)
{
    auto itR = std::lower_bound(node->_localRotation.begin(), node->_localRotation.end(), keyFrame, pairCompare);
    if (itR == node->_localRotation.end()) 
        itR--;
    if (itR + 1 != node->_localRotation.end())
        itR++;
    uint32 frontDistance = std::distance(node->_localRotation.begin(), itR);
    if (frontDistance < 3) itR = node->_localRotation.begin() + 3;
    if (keyFrame <= (itR -2)->first) keyFrame = (itR -2)->first + 1;
    else if (keyFrame > (itR - 1)->first) keyFrame = (itR - 1)->first;
    const math::Quat& t0 = (itR - 3)->second;
    const math::Quat& t1 = (itR - 2)->second;
    const math::Quat& t2 = (itR - 1)->second;
    const math::Quat& t3 = (itR - 0)->second;
    interpolR = math::catmullRom(t0,t1,t2,t3, (keyFrame - (itR -2)->first)/((itR-1)->first - (itR -2)->first));

    auto itT = std::lower_bound(node->_localTrans.begin(), node->_localTrans.end(), keyFrame, pairCompare);
    itT++;
    const math::Vec3& v0 = (itT - 3)->second;
    const math::Vec3& v1 = (itT - 2)->second;
    const math::Vec3& v2 = (itT - 1)->second;
    const math::Vec3& v3 = (itT - 0)->second;
    interpolT = math::catmullRom(v0,v1,v2,v3,(keyFrame - (itT -2)->first)/((itT-1)->first - (itT -2)->first));
}

void IBlendNode::updateTransForm(
    const AnimationData& node, uint32 keyFrame, float interpolVal, 
    std::vector<BoneLocal>& _boneLocalVector,
    std::vector<BONEID> boneIds,
    BlendNode nodeNum 
)
{
    std::queue<const AnimationData*> animationQ;
    
    if (interpolVal > 1)
        interpolVal = 1;

    animationQ.push(&node);
    while (animationQ.empty() == false)
    {
        const AnimationData* curData = animationQ.front();
        animationQ.pop();
        for (const AnimationData& animation : curData->_childrens)
        {
            auto it = std::find(boneIds.begin(), boneIds.end(), animation._boneIndex);
            if (it != boneIds.end())
            {
                boneIds.erase(it);
                continue;
            }
            animationQ.push(&animation);
        }
        math::Quat mixR;
        math::Vec3 mixT;
        getTransFormByKeyFrame(mixR, mixT, curData, keyFrame);
        
        _boneLocalVector[curData->_boneIndex].translationInBoneLocal = math::mix(_boneLocalVector[curData->_boneIndex].translationInBoneLocal, mixT, interpolVal);
        _boneLocalVector[curData->_boneIndex].rotationInBoneLocal = math::slerp(_boneLocalVector[curData->_boneIndex].rotationInBoneLocal, mixR, interpolVal);
    }
}

void IBlendNode::changeUpperState(UpperState& upperState, const std::string& name)
{
    if (name == "idle")
        upperState = UpperState::IDLE;
    if (name == "run")
        upperState = UpperState::RUN;
    if (name == "walk")
        upperState = UpperState::WALK;
    if (name == "runJump2")
        upperState = UpperState::JUMP;
    if (name == "punch")
        upperState = UpperState::PUNCH;
    if (name == "drink")
        upperState = UpperState::DRINK;
    if (name == "roll")
        upperState = UpperState::ROLL;
    if (name == "golf")
        upperState = UpperState::GOLF;
    _state = static_cast<int32>(upperState);
}

void IBlendNode::changeLowerState(LowerState& loswerState, const std::string& name)
{
    if (name == "idle")
        loswerState = LowerState::IDLE;
    if (name == "run")
        loswerState = LowerState::RUN;
    if (name == "walk")
        loswerState = LowerState::WALK;
    if (name == "runJump2")
        loswerState = LowerState::JUMP;
    if (name == "punch")
        loswerState = LowerState::PUNCH;
    if (name == "drink")
        loswerState = LowerState::DRINK;
    if (name == "roll")
        loswerState = LowerState::ROLL;
    if (name == "golf")
        loswerState = LowerState::GOLF;
    _state = static_cast<int32>(loswerState);
}