#pragma once
#include "Common.h"
#include "BoneLocal.h"
#include "IKInterface.h"

const float LOWERNECK_RATIO = 0.2;
const float UPPER_RATIO = 0.35;
const float HEAD_RATIO = 1 - LOWERNECK_RATIO - UPPER_RATIO;
class EyeIK : public IKInterface
{
    private:
        math::Vec3 moveInBoneLocalPos(const math::Vec3& start, const math::Vec3& end, const math::Quat& toTargetDir, const math::Vec3& endBoneDir, float ratio);
        void blendingRatioUpdate(const std::chrono::steady_clock::time_point& curTime);
    
    public:
        explicit EyeIK(const std::vector<Bone>& boneVector) : IKInterface(boneVector){};
        ~EyeIK(){};

        virtual void solveIK(
            std::vector<BoneLocal>& _boneLocalVector, 
            const math::Mat4& worldRotation, 
            const math::Mat4& worldTranslate,
            const Controller& _controller,
            const std::chrono::steady_clock::time_point& curTime,
            LowerState beforeState = LowerState::IDLE,
            Physx* physx = nullptr
        ) override final;
};
