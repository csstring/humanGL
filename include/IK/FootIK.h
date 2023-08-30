#pragma once
#include "Common.h"
#include "BoneLocal.h"
#include "IKInterface.h"
#include "EnumHeader.h"

class Physx;
enum class stairDir
{
    UPSTAIR, DOWNSTAIR, NORMAL
};
class FootIK : public IKInterface
{
    private:
        void positionFixLimitAngleForWard(math::Vec3& start, math::Vec3& end, math::Vec3 startBoneDir,const Bone& endBone);
        void positionFixLimitAngleBackWard(math::Vec3& start, math::Vec3& end, math::Vec3 endBoneDir,const Bone& endBone);
        void isOffGroundCheck(const std::vector<math::Vec3>& inCharLocalPos, Physx* gScene, math::Mat4 charLocalToWorld);
        bool findTargetObject(
            const std::vector<math::Vec3>& inCharLocalPos, 
            Physx* gScene, 
            math::Mat4 charLocalToWorld,
            math::Vec3 tmpMoveDir
        );
        void blendingRatioUpdate(void);
        void fixBendingAngle(math::Vec3& start, math::Vec3& mid, math::Vec3& end);
        bool saveBlendingAnimation(std::vector<math::Vec3>& inCharLocalPos, std::vector<math::Mat4>& inCharLocalRot, math::Vec3 curFootPos);
        bool isStartFindTarget(const std::vector<math::Vec3>& inCharLocalPos);
        float getFirstHitHight(const math::Mat4& charLocalToWorld, const math::Vec3& inCharPos, Physx* physx);
        
    private:
        bool      _isMoveAnimation = false;
        float     _rootRatio = 0;
        bool      _isRootAnimationOn = false;
        math::Vec3 _groundNormal;
        float     _groundHight = -10;
        float     _firstHitHight;
        float     _deltaMilisecond;
        stairDir  _stairDir = stairDir::NORMAL;
        math::Vec3 _prevTibiaPos;
        std::vector<math::Vec3> _bonePos;
        std::vector<math::Quat> _boneRot;
        physx::PxRigidActor* _curTouchBody = nullptr;

    public:
        explicit FootIK(const std::vector<Bone>& boneVector) : IKInterface(boneVector)
        {
            _isOffGround = false;
            _bonePos.resize(4);
            _boneRot.resize(4);
        };
        ~FootIK(){};
        bool reachable(const std::vector<math::Vec3>& inCharacterPos, std::vector<float>& distance, math::Vec3 footPosition);
        virtual void solveIK(
            std::vector<BoneLocal>& _boneLocalVector, 
            const math::Mat4& worldRotation, 
            const math::Mat4& worldTranslate,
            const Controller& _controller,
            const std::chrono::steady_clock::time_point& curTime,
            LowerState beforeState,
            Physx* gScene
        ) override final;
        void setCharGroundHight(float& charGroundHight);
        void setTestOption(math::Vec3 position, math::Vec3 normal, math::Mat4 charLocalToWorld);

    public :
        bool      _isOffGround;
};
