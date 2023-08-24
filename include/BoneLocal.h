#pragma once
#include "Common.h"
struct BoneLocal
{
    math::Quat rotationInBoneLocal;
    math::Vec3 translationInBoneLocal;
    math::Vec3 scaleInBoneLocal;
};