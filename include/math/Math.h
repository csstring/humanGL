#pragma once
#include <cmath>
#include "GLM/glm.hpp"
#include "GLM/gtx/string_cast.hpp"
const float PI = 3.141592;
namespace math
{
  float radians(float degrees);

  float     dot(const glm::vec3& x, const glm::vec3& y);
	float     dot(const glm::quat& a, const glm::quat& b);
	glm::quat conjugate(const glm::quat& q);
  glm::vec3 cross(const glm::vec3& x, const glm::vec3& y);

  glm::mat4 translate(const glm::mat4& m, const glm::vec3& v);
	
  glm::mat4 inverse(const glm::mat4& m);
  glm::mat3 inverse(const glm::mat3& m);
	glm::quat inverse(const glm::quat& q);

  glm::vec3 normalize(const glm::vec3& v);
  glm::mat4 rotate(const glm::mat4& m, float radians, const glm::vec3& v);
  glm::mat4 rotate(float radians, const glm::vec3& v);

  glm::quat quatCast(const glm::mat4& m4);
  glm::quat quatCast(const glm::mat3& m3);
  glm::mat3 toMat3(const glm::quat& q);
  glm::mat4 toMat4(const glm::quat& q);

  glm::quat catmullRom(const glm::quat& v1, const glm::quat& v2, const glm::quat& v3, const glm::quat& v4, const float& s);
  glm::vec3 catmullRom(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const float& s);

  float angle(const glm::quat& x);
	glm::vec3 axis(const glm::quat& x);
	glm::quat angleAxis(const float& angle, const glm::vec3& v);
	
	glm::vec3 eulerAngles(const glm::quat& x);
	float roll(const glm::quat& q);
	float pitch(const glm::quat& q);
	float yaw(const glm::quat& q);

	float length2(const glm::quat& q);
	float length(const glm::vec3& v);
	glm::quat rotation(const glm::vec3& orig,const glm::vec3& dest);

	glm::vec3 mix(const glm::vec3& x, const glm::vec3& y, const float& a);
	float mix(const float& x, const float& y, const float& a);
	glm::quat slerp(const glm::quat& x, const glm::quat& y, const float& a);
}
