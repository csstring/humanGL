#pragma once
#include "../Common.h"
#include "../EnumHeader.h"
class Bone;
class Controller;
class BoneLocal;
class Physx;

class IKInterface
{
    protected :
        //test fix me
        // bool                     _targetOn;
        // float                    _blendingRatio;
        bool                     _isFirst;
        math::Vec3                _targetPosition;
        std::vector<math::Vec3>   _bonedirection;
        std::vector<uint8>       _boneIndexVec;
        float                    _velocity;
        uint32                   _retargetTime;
        const std::vector<Bone>& _boneVector;//지워야 할듯?

    public:
        std::chrono::steady_clock::time_point _prevTime;
        std::chrono::steady_clock::time_point _curTime;
        //test fix me
        float                    _blendingRatio;
        bool                     _targetOn;

    public:
        explicit IKInterface(const std::vector<Bone>& boneVector) : _boneVector(boneVector)
        {
            _targetOn = false;
            _isFirst = true;
            _blendingRatio = 0;
        };
        virtual ~IKInterface(){};

        void initialize(BONEID targetBone, BONEID startBone);
        void setTargetPosition(math::Vec3 targetPosition);
        void saveVelocity(math::Vec3 beforePos, math::Vec3 curPos);
        virtual void solveIK(
            std::vector<BoneLocal>& _boneLocalVector, 
            const math::Mat4& worldRotation, 
            const math::Mat4& worldTranslate,
            const Controller& _controller,
            const std::chrono::steady_clock::time_point& curTime,
            LowerState beforeState,
            Physx* gScene
        ) = 0;
};