#pragma once
#include "EnumHeader.h"
#include "AnimationBlend/IBlendNode.h"

struct BoneLocal;
class Animation;
class Skeleton;

class Blender
{
    private:
        std::vector<IBlendNode*> _blendTree;
    public:
        Blender(){};
        ~Blender()
        {
            for (auto it : _blendTree)
                delete it;
            std::cerr << "blender delete call " << std::endl;
        };
        void initialize(void);
        IBlendNode* getBlendNode(BlendNode nodeNum);
        void animationUpdate(
            const std::chrono::steady_clock::time_point& curTime, 
            std::vector<BoneLocal>& boneLocalVector,
            LowerState& lowerState,
            UpperState& upperState
        );
        void eraseAnimationCall(const std::chrono::steady_clock::time_point& curTime);
};