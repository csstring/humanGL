#pragma once

#include "Common.h"
#include "Skeleton.h"
#include <deque>
#include <iostream>
#include "Animation.h"
#include "Body/Cube.h"
#include "Controller.h"
#include "Body/BodyFactory.h"
#include "Body/Ground.h"

struct AnimationData;
class TimeNode;
class Character;
class Cube;
enum class KeyInput;
class Controller;

class Simulator : Noncopyable
{
    private:
        std::vector<Character*> _players;
        std::chrono::steady_clock::time_point _prevTime;
        Controller _controller;
        BodyFactory _factory;

    public:
        Simulator(){}
        ~Simulator();
        
        void initialize(void);
        void changeAnimation(KeyInput key);
        void update(void);
        void draw(void);
        void addPlayer(const std::string initAnimationName);
        void changeControllCharacter(void);
        void fileLoad(const std::string asfPath);
    public : 
        Skeleton               _skeleton;
        std::vector<Animation> _animations;
        Ground                 _ground;

};
