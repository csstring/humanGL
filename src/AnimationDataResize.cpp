#include "AnimationDataResize.h"
#include "Animation.h"

void AnimationDataResize::processNode(AnimationData& data)
{
    data._localRotation.reserve(_size);
    data._localTrans.reserve(_size);
}