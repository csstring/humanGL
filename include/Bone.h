#pragma once
#include "Common.h"
#include <string>
#include <vector>
#include "GLM/ext.hpp"
#include <tuple>

enum class DOF;

struct Bone
{
    uint32           _boneIndex;
    int32            _parentBoneIndex;
    std::string      _boneName;
    float            _length;
    math::Vec3        _direction;
    std::vector<std::tuple<DOF, float,float>> _limits;
    //fixme : 아래쪽 데이터 필요없어서 정리 해야함
    math::Vec3        _postion;
    math::Vec3        _axis;
    std::vector<DOF> _dof;
    math::Quat        _c;
    math::Quat        _invC;
    math::Vec3        _b;
};

