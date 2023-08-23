#include "Common.h"
#include "GLM/gtx/transform.hpp"
#include <sstream>

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

glm::mat4 ft_rotate(glm::vec3 start, glm::vec3 end)
{ 
    start = math::normalize(start);
    end = math::normalize(end);
    glm::vec3 axis = math::cross(start, end);
    glm::vec3 axisNormal = math::normalize(axis);
    float angle = acos(math::dot(start, end));
    return math::rotate(angle, axisNormal);
}

glm::vec3 quatToEulerDivideRatio(const glm::quat& quat, float ratio)
{
    glm::vec3 axis = math::axis(quat);
    float angle = math::angle(quat);
    angle *= ratio;
    glm::quat newQuat = math::angleAxis(angle, axis);

    return math::eulerAngles(newQuat);
}

glm::quat quatDivideRatio(const glm::quat& quat, float ratio)
{
    glm::vec3 axis = math::axis(quat);
    float angle = math::angle(quat);
    angle *= ratio;
    return math::angleAxis(angle, axis);
}

std::string ft_to_string(const physx::PxVec3& vec)
{
    std::string oss;
    oss = "PxVec3(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " +std::to_string(vec.z) + ")";
    return oss;
}

