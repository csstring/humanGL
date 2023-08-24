#pragma once
#include <cmath>

const float PI = 3.141592;
namespace math
{
  class Mat3;
  class Mat4;
  class Vec3;
  class Vec4;
  class Quat;
}
namespace math
{
  float radians(float degrees);

  float     dot(const Vec3& x, const Vec3& y);
	float     dot(const Quat& a, const Quat& b);
	Quat conjugate(const Quat& q);
  Vec3 cross(const Vec3& x, const Vec3& y);

  Mat4 translate(const Mat4& m, const Vec3& v);
	
  Mat4 inverse(const Mat4& m);
  Mat3 inverse(const Mat3& m);
	Quat inverse(const Quat& q);

  Vec3 normalize(const Vec3& v);
  Mat4 rotate(const Mat4& m, float radians, const Vec3& v);
  Mat4 rotate(float radians, const Vec3& v);

  Quat quatCast(const Mat4& m4);
  Quat quatCast(const Mat3& m3);
  Mat3 toMat3(const Quat& q);
  Mat4 toMat4(const Quat& q);

  Quat catmullRom(const Quat& v1, const Quat& v2, const Quat& v3, const Quat& v4, const float& s);
  Vec3 catmullRom(const Vec3& v1, const Vec3& v2, const Vec3& v3, const Vec3& v4, const float& s);

  float angle(const Quat& x);
	Vec3 axis(const Quat& x);
	Quat angleAxis(const float& angle, const Vec3& v);
	
	Vec3 eulerAngles(const Quat& x);
	float roll(const Quat& q);
	float pitch(const Quat& q);
	float yaw(const Quat& q);

	float length2(const Quat& q);
	float length(const Vec3& v);
	Quat rotation(const Vec3& orig,const Vec3& dest);

	Vec3 mix(const Vec3& x, const Vec3& y, const float& a);
	float mix(const float& x, const float& y, const float& a);
	Quat slerp(const Quat& x, const Quat& y, const float& a);

  Mat4 perspective(float fovy, float aspect, float zNear, float zFar);
  Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
}
