#pragma once
#include "Common.h"
struct BoneLocal
{
    math::Quat rotationInBoneLocal = math::Quat(1.0f, math::Vec3(0.0f));
    math::Vec3 translationInBoneLocal = math::Vec3(0.0f);
    math::Vec3 scaleInBoneLocal = math::Vec3(0.0f);
};