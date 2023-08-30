#include "Simulator.h"
#include "Animation.h"
#include "TimeNode.h"
#include "Character.h"
#include "Body/Cube.h"
#include "EnumHeader.h"
#include "math/Math.h"
#include "CmuFileParser.h"
#include "AMCFileParser.h"
void Simulator::addPlayer(const std::string initAnimationName)
{
    float radius = _skeleton.getSkeletonWidth();
    float height = _skeleton.getSkeletonHeight();
    math::Vec3 rFoot = _skeleton.getCharLocalPosition(BONEID::RFOOT) - _skeleton.getCharLocalPosition(BONEID::ROOT);

    Character* newPlayer = _factory.makeCharacter(_skeleton, _controller);
    Character* oldPlayer = _controller.getPlayer();
    
    _players.push_back(newPlayer);
    _controller.setPlayer(newPlayer);
    _controller.pushAnimation(initAnimationName, _animations, BlendNode::BASE);
    _controller.setPlayer(oldPlayer);
}

void Simulator::initialize(void)
{
    addPlayer("idle");
    _controller.initialize();

    math::Quat rot = math::angleAxis(math::radians(10.0f), math::Vec3(0.0f, 0.0f, 1.0f));

    _ground.initialize();
    _controller.setPlayer(_players.front());
    _prevTime = getCurTimePoint();
}

void Simulator::draw(void)
{
    for (Character* player : _players)
        player->draw();
    _controller.draw();
    // _ground.draw();
}

void Simulator::update(void)
{
    std::chrono::steady_clock::time_point curTime = getCurTimePoint();
    std::chrono::milliseconds  millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - _prevTime);
    float delta = static_cast<float>(millisecond.count()) / 1000.0f;
    if (delta == 0)
    {
        std::cout << "delta check\n";
        delta = 1.0f/60.0f;
    }
    float radian = PI * delta * 0.25f;
    math::Quat groundCubeRot = math::angleAxis(radian, math::Vec3(0,1,0));
    _controller.update();
    // _ground.update();
    for (Character* player : _players)
    {
        player->update(curTime);
    }

    _prevTime = curTime;
}

void Simulator::changeControllCharacter(void)
{
    const Character* curPlayer = _controller.getPlayer();
    float minRad = 5; 
    math::Mat4 inCharLocalPosition = _controller.getMatrixInCharLocal(BONEID::THORAX, curPlayer->getCharacterSkeleton(), curPlayer->getCharLocalVector());
    math::Mat3 tmpRot = math::Mat3(inCharLocalPosition);
    math::Mat3 worRot = math::Mat3(curPlayer->getCharacterWorldPosition());
    
    math::Vec3 curSee,curPos;
    curPos = curPlayer->getCharacterWorldPosition() * inCharLocalPosition * math::Vec4(0,0,0,1);
    curSee = worRot * tmpRot * math::cross(math::Vec3(1,0,0), curPlayer->getCharacterSkeleton().getBoneVector()[BONEID::THORAX]._direction);
    for (Character* player : _players)
    {
        if (player == curPlayer)
            continue;
        inCharLocalPosition = _controller.getMatrixInCharLocal(BONEID::THORAX, player->getCharacterSkeleton(), player->getCharLocalVector());
        math::Vec3 nextPos = math::Vec3(player->getCharacterWorldPosition() * inCharLocalPosition * math::Vec4(0,0,0,1));
        math::Vec3 nextEeler = math::normalize(nextPos - curPos);
        math::Quat quat = math::rotation(curSee, nextEeler);
        float rad = abs(math::angle(quat));

        if (rad < minRad)
        {
            _controller.setPlayer(player);
            minRad = rad;
        }
    }
}

void Simulator::changeAnimation(KeyInput key)
{
    // if (key == KeyInput::CUBEBACK)
    //     _cube._pos = glm::translate(_cube._pos, math::Vec3(0,0,0.1));
    // else if (key == KeyInput::CUBEFRONT)
    //     _cube._pos = glm::translate(_cube._pos, math::Vec3(0,0,-0.1));
    // else if (key == KeyInput::CUBERIGHT)
    //     _cube._pos = glm::translate(_cube._pos, math::Vec3(0.1,0,0));
    // else if (key == KeyInput::CUBELEFT)
    //     _cube._pos = glm::translate(_cube._pos, math::Vec3(-0.1,0,0));
    if (key == KeyInput::CUBEUP)
        _ground._rot = math::translate(_ground._rot, math::Vec3(0,0.1,0));
    else if (key == KeyInput::CUBEDOWN)
        _ground._rot = math::translate(_ground._rot, math::Vec3(0,-0.1,0));
    else if (key == KeyInput::CUBEBACK)//j
        _ground._rot = _ground._rot * math::rotate(math::radians(1.0f), math::Vec3(-1,0,0));
    else if (key == KeyInput::CUBEFRONT)//u
        _ground._rot = _ground._rot * math::rotate(math::radians(1.0f), math::Vec3(1,0,0));
    else if (key == KeyInput::CUBERIGHT)//k
        _ground._rot = _ground._rot * math::rotate(math::radians(1.0f), math::Vec3(0,0,1));
    else if (key == KeyInput::CUBELEFT)//h
        _ground._rot = _ground._rot * math::rotate(math::radians(1.0f), math::Vec3(0,0,-1));
    else
        _controller.controllPlayer(key, _animations);
}

void Simulator::fileLoad(const std::string asfPath)
{
    std::vector<const char*> amcPathList = {"./amc/walk1.amc", 
    "./amc/run.amc","./amc/runJump2.amc","./amc/punch.amc",
    "./amc/idle.amc", "./amc/dance.amc", "./amc/drink.amc", 
    "./amc/roll.amc", "./amc/golf.amc"};
    _animations.push_back(Animation("walk", 1));
    _animations.push_back(Animation("run", 1));
    _animations.push_back(Animation("runJump2", 1));
    _animations.push_back(Animation("punch", 1));
    _animations.push_back(Animation("idle", 1));
    _animations.push_back(Animation("dance", 1));
    _animations.push_back(Animation("drink", 1));
    _animations.push_back(Animation("roll", 1));
    _animations.push_back(Animation("golf", 1));

    std::filesystem::path asf(asfPath);
    if (std::filesystem::exists(asf) == false)
        ft_exit("asf file path fail");
    
    CmuFileParser parser(std::filesystem::canonical(asf),&_skeleton, &_animations[0]);
    parser.loadCmuFile();

    AnimationData root = _animations[0]._rootNode;
    for (int i = 0; i < _animations.size(); ++i)
    {
        _animations[i]._rootNode = root;
        AMCFileParser amcParser(amcPathList[i], &_skeleton, &_animations[i]);
        amcParser.loadAMCFile();
    }
}

Simulator::~Simulator()
{
    for (auto it : _players)
        delete it;
}