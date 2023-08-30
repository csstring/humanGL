#include "Common.h"
#include <sstream>
#include "math/Math.h"

void ft_assert(const std::string& exec)
{
    std::cout << exec << std::endl;
    assert(false);
}

std::vector<std::string> ft_split(const std::string& str)
{
    std::stringstream ss(str);
    std::vector<std::string> v;
    std::string buffer;

    while (ss >> buffer)
        v.push_back(buffer);
    v.shrink_to_fit();
    return v;
}

math::Mat4 ft_rotate(math::Vec3 start, math::Vec3 end)
{ 
    start = math::normalize(start);
    end = math::normalize(end);
    math::Vec3 axis = math::cross(start, end);
    math::Vec3 axisNormal = math::normalize(axis);
    float angle = acos(math::dot(start, end));
    return math::rotate(angle, axisNormal);
}

math::Vec3 quatToEulerDivideRatio(const math::Quat& quat, float ratio)
{
    math::Vec3 axis = math::axis(quat);
    float angle = math::angle(quat);
    angle *= ratio;
    math::Quat newQuat = math::angleAxis(angle, axis);

    return math::eulerAngles(newQuat);
}

math::Quat quatDivideRatio(const math::Quat& quat, float ratio)
{
    math::Vec3 axis = math::axis(quat);
    float angle = math::angle(quat);
    angle *= ratio;
    return math::angleAxis(angle, axis);
}

void ft_exit(const std::string message)
{
    std::cerr << message << std::endl;
    exit(1);
}