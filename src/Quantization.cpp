#include "Quantization.h"
#include <cmath>

int16 toShort(float val)
{   
    int16 returnVal = static_cast<int16>(std::roundf(val * (1 << 14)));
    returnVal = returnVal >> 1;
    return returnVal;
}

float toFloat(int16 val)
{
    val = val << 1;
    float returnVal = static_cast<float>(val);
    return returnVal / (1 << 14);
}

quatPressData packQuaternionData(math::Quat quat)
{
    quatPressData pressData;
    uint32 find = 0;
    float max = 0;

    for (uint32 i =0; i <4; ++i)
    {
        float cur = quat[i] * quat[i];
        if (cur > max)
        {
            max = cur;
            find = i;
        }
    }

    pressData.other = find;
    uint32 count = 0;
    for (uint32 i = 0; i < 4; ++i)
    {
        if (i == find)
            continue;
        switch (count++)
        {
        case 0:
            pressData.x = toShort(quat[i]);
            break;
        case 1:
            pressData.y = toShort(quat[i]);
            break;
        case 2:
            pressData.z = toShort(quat[i]);
            break;
        }
    }
    return pressData;
}

math::Quat unpackQuaternionData(quatPressData packData)
{
    math::Quat quat;
    uint32 find = packData.other;

    uint32 count = 0;
    float val = 0;
    for (uint32 i = 0; i < 4; ++i)
    {
        if (i == find)
            continue;
        switch (count++)
        {
        case 0:
            quat[i] = toFloat(packData.x);
            break;
        case 1:
            quat[i] = toFloat(packData.y);
            break;
        case 2:
            quat[i] = toFloat(packData.z);
            break;
        }
        val += quat[i] * quat[i];
    }
    quat[find] = sqrt(1 - val);
    return quat;
}
