#include "Controller.h"
#include "Skeleton.h"
#include "Character.h"
#include "EnumHeader.h"
#include "Animation.h"
#include "AnimationBlend/IBlendNode.h"
#include "math/Math.h"

void Controller::initialize(void)
{
    _targetCharterCube.initialize();
}

void Controller::draw(void)
{
    // _targetCharterCube.draw();
}

void Controller::update(void)
{
    math::Mat4 inCharLocalPosition = getMatrixInCharLocal(BONEID::HEAD, _player->getCharacterSkeleton(), _player->getCharLocalVector());
    _targetCharterCube._translate = _player->getCharacterWorldPosition() * inCharLocalPosition * math::translate(math::Mat4(1.0f), math::Vec3(0,0.7,0));
    _targetCharterCube.update();
}

void Controller::setPlayer(Character* player)
{
    if (player == nullptr)
        return;
    _player = player;
}

math::Mat4 Controller::getMatrixInCharLocal(uint32 boneindex,const Skeleton& _skeleton, const std::vector<BoneLocal>& _boneLocalVector, float scale) const
{
    const std::vector<Bone>& boneVector = _skeleton.getBoneVector();
    math::Mat4 matrix(1.0f);
    const Bone* bone = &boneVector[boneindex];
    while (true)
    {
        math::Mat4 trans = math::translate(math::Mat4(1.0f), _boneLocalVector[bone->_boneIndex].translationInBoneLocal * scale);
        math::Quat rot = _boneLocalVector[bone->_boneIndex].rotationInBoneLocal;
        matrix = trans * math::toMat4(rot) * matrix;
        if (bone->_parentBoneIndex == -1)
            break;
        bone = &boneVector[bone->_parentBoneIndex];
    }
    return matrix;
}

const Animation* Controller::findAnimation(const std::string& name, const std::vector<Animation>& _animations)
{
    for (int32 i = 0; i < _animations.size(); ++i)
    {
        if (_animations[i]._name == name)
            return &_animations[i];
    }
    return NULL;
}

void Controller::pushAnimation(const std::string& name, const std::vector<Animation>& _animations, BlendNode nodeNum)
{
    const Animation* pushAnimation = findAnimation(name, _animations);
    auto& animationDeque = _player->_blender.getBlendNode(nodeNum)->_animations;

    if (animationDeque.size() >= 3)
        animationDeque.pop_back();
    if (animationDeque.size() >= 1 &&
        animationDeque.back().second._endTime > getAfterTimePoint(OVERLAPTIME))
        animationDeque.back().second._endTime = getAfterTimePoint(OVERLAPTIME);

    TimeNode node(getCurTimePoint(), getAfterTimePoint(pushAnimation->_animationMillisecond));
    animationDeque.push_back({pushAnimation, node});

}

void Controller::controllPlayer(KeyInput key, const std::vector<Animation>& _animations)
{
    if (_player == nullptr)
        return;

    if (key == KeyInput::UP)
        this->pushAnimation("walk", _animations, BlendNode::BASE);
    else if (key == KeyInput::LOWERBACK)
        _player->rotationY(PI);
    else if (key == KeyInput::REFT)
        _player->rotationY(PI/(2*30));
    else if (key == KeyInput::RIGHT)
        _player->rotationY(-PI/(2*30));
    else if (key == KeyInput::STOP)
        this->pushAnimation("idle", _animations, BlendNode::BASE);
    else if (key == KeyInput::RUN)
    {
        if (_player->_lowerState == LowerState::WALK)
            this->pushAnimation("run", _animations, BlendNode::BASE);
        else if (_player->_lowerState == LowerState::RUN)
            this->pushAnimation("walk", _animations, BlendNode::BASE);
    }
    else if (key == KeyInput::ATTACK)
    {
        if (_player->_lowerState < LowerState::PUNCH)
            this->pushAnimation("punch", _animations, BlendNode::LOWER);
        if (_player->_upState < UpperState::PUNCH)
            this->pushAnimation("punch", _animations, BlendNode::UPPER);
    }
    else if (key == KeyInput::DRINK)
    {
        if (_player->_upState < UpperState::DRINK)
            this->pushAnimation("drink", _animations, BlendNode::LEFTARM);
    }
    else if (key == KeyInput::JUMP)
    {
        if (_player->_lowerState < LowerState::JUMP)
            this->pushAnimation("runJump2", _animations, BlendNode::LOWER);
        if (_player->_upState < UpperState::JUMP)
            this->pushAnimation("runJump2", _animations, BlendNode::UPPER);
    }
    else if (key == KeyInput::ROLL && _player->_lowerState < LowerState::ROLL)
    {
        this->pushAnimation("roll", _animations, BlendNode::LOWER);
        if (_player->_upState < UpperState::ROLL)
            this->pushAnimation("roll", _animations, BlendNode::UPPER);
    }
    else if (key == KeyInput::GOLF && _player->_upState < UpperState::GOLF)
    {
        this->pushAnimation("golf", _animations, BlendNode::UPPER);
        this->pushAnimation("golf", _animations, BlendNode::LOWER);
    }
}