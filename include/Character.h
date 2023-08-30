#include "TimeNode.h"
#include <deque>
#include "BoneLocal.h"
#include "AnimationBlend/Blender.h"
#include "EnumHeader.h"
struct AnimationData;
class Animation;
class Skeleton;
class Controller;
class EyeIK;
class FootIK;
class Ground;
class CollisionCylinder;
class Physx;
class Character
{   
    private:
        std::vector<uint32>    VAO, VBO, VBC;
        std::vector<BoneLocal> _boneLocalVector;
        math::Mat4              _worldTrans;
        math::Mat4              _worldRotation;
        const Skeleton&        _skeleton;
        const Controller&      _controller;
        bool                   _isFirst;
        std::chrono::steady_clock::time_point _lastCallTime;

    public:
        CollisionCylinder* _collisionMesh;
        Blender _blender;
        EyeIK* _eyeIK = nullptr;
        FootIK* _RfootIK = nullptr;
        FootIK* _LfootIK = nullptr; 
        UpperState _upState;
        LowerState _lowerState;
        float      _yError = 0.001;
        float      _groundHight = -10;

    private :
        void boneBufferMaping(void);  
        void worldPositionUpdate(float deltaTime);

    public:
        Character(
            const Skeleton& skeleton, const Controller& controller, CollisionCylinder* collisionMesh
        ) : _skeleton(skeleton), _controller(controller), _isFirst(true), _collisionMesh(collisionMesh){};
        ~Character();
        void initialize(void);
        const Skeleton& getCharacterSkeleton(void) const {return _skeleton;};
        void update(const std::chrono::steady_clock::time_point& curTime, math::Vec3 eyeTarget, Physx* physx);
        void draw(void);
        void rotationY(float radian);
        math::Mat4 getCharacterWorldPosition(void) const;
        const std::vector<BoneLocal>& getCharLocalVector(void) const {return _boneLocalVector;};

};
