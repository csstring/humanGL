#include "Character.h"
#include "Skeleton.h"
#include "TimeNode.h"
#include "Animation.h"
#include "Body/Cylinder.h"
#include "Controller.h"
#include <queue>
#include "AnimationBlend/Blender.h"
#include "AnimationBlend/IBlendNode.h"
#include "Body/Ground.h"
#include "math/Math.h"
#include "Body/Cube.h"

void Character::rotationY(float radian)
{
    _worldRotation = math::rotate(_worldRotation, radian, math::Vec3(0,1,0));
}

math::Mat4 Character::getCharacterWorldPosition(void) const
{
    return _worldTrans * _worldRotation;
}

void Character::initialize(void)
{
    int64 size = _skeleton.getBoneVector().size();


    _boneLocalVector.resize(size);
    _worldTrans = math::Mat4(1.0f);
    _worldRotation = math::Mat4(1.0f);


    _blender.initialize();
}

void Character::worldPositionUpdate(float deltaTime)
{
    math::Vec3 t = math::Vec3(_worldTrans * _worldRotation * _controller.getMatrixInCharLocal(BONEID::RFOOT, _skeleton, _boneLocalVector) * math::Vec4(0,0,0,1));
    math::Vec3 root = math::Vec3(_worldTrans * _worldRotation * _controller.getMatrixInCharLocal(BONEID::ROOT, _skeleton, _boneLocalVector) * math::Vec4(0,0,0,1));

    if (t.y > _groundHight)
        root.y -= _yError * deltaTime;
    else if (t.y < _groundHight)
        root.y += _yError * deltaTime;
    _worldTrans = math::translate(math::Mat4(1.0f), root);
}

void Character::update(const std::chrono::steady_clock::time_point& curTime)
{
    std::chrono::milliseconds delta;
    static int i = 0;
    if (_isFirst == true)
    {
        _isFirst = false;
        _lastCallTime = curTime;
    }
    if (_yError != 0)
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - _lastCallTime);
    else 
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - curTime);

    _blender.eraseAnimationCall(curTime);
    worldPositionUpdate(delta.count());
    _blender.animationUpdate(curTime, _boneLocalVector, _lowerState, _upState);

    _lastCallTime = curTime;
}

//up -> draw
void Character::draw(void)
{
    const std::vector<Bone>& boneVector = _skeleton.getBoneVector();

    ImGui::ColorEdit3("clear color", &_skinColor.x);
    ImGui::SliderFloat("float", &scaleUpVal, 0.2f, 3.0f);

    for(const Bone& bone : boneVector)
    {
        if (bone._parentBoneIndex == -1)
            continue;
        math::Mat4 parentTransForm;
        math::Vec3 parentBoneDir = boneVector[bone._parentBoneIndex]._direction;
        if (bone._parentBoneIndex != 0)    
            parentTransForm = _worldTrans * _worldRotation * _controller.getMatrixInCharLocal(bone._parentBoneIndex, _skeleton, _boneLocalVector,scaleUpVal) * ft_rotate(math::Vec3(0.0,0.0,1.0), -parentBoneDir);
        else
            parentTransForm = _worldTrans * _worldRotation * _controller.getMatrixInCharLocal(bone._parentBoneIndex, _skeleton, _boneLocalVector, scaleUpVal);
        math::Vec3 parentPos = math::Vec3(parentTransForm * math::Vec4(0,0,0,1));
        
        math::Mat4 toParentDir = _worldTrans * _worldRotation * _controller.getMatrixInCharLocal(bone._boneIndex, _skeleton, _boneLocalVector,scaleUpVal) * ft_rotate(math::Vec3(0.0,0.0,1.0), -bone._direction);// * glm::inverse(test3);
        math::Quat WorldRot = math::quatCast(toParentDir);
        math::Vec3 worldPos = math::Vec3(toParentDir * math::Vec4(0,0,0,1));
        float length = 1.0f * _skeleton.getGBL() * bone._length * scaleUpVal;

        Cube box(math::Vec3(0.5,0.5,length), math::Vec3(0.0f), _skinColor);
        // Cube box(math::Vec3(length), math::Vec3(0.0f), color);
        box._translate = math::translate(math::Mat4(1.0f), math::mix(worldPos, parentPos, 0.5));
        box._rot = WorldRot; 
        box.initialize();
        box.update();
        box.draw();
    }
}


