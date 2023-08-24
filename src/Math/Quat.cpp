#include "math/Quat.h"
#include "math/Vec4.h"
#include "math/Vec3.h"
#include "math/Mat4.h"
#include "math/Mat4.h"
#include "math/Math.h"
#include "Common.h"
namespace math
{
float& Quat::operator[](int i)
{
  assert(i >= 0 && i < 4);
	return (&x)[i];
}
const float& Quat::operator[](int i) const
{
  assert(i >= 0 && i < 4);
	return (&x)[i];
}

Quat::Quat() : x(0), y(0), z(0), w(1)
{}
Quat::Quat(const Quat& q) : x(q.x), y(q.y), z(q.z), w(q.w)
{}
Quat::Quat(float s, const Vec3& v) : x(v.x), y(v.y), z(v.z), w(s)
{}
Quat::Quat(float w, float x, float y, float z) : x(x), y(y), z(z), w(w)
{}

/// Build a Quatternion from euler angles (pitch, yaw, roll), in radians.
Quat::Quat(const Vec3& eulerAngle)
{
		Vec3 c = Vec3(cos(eulerAngle.x * float(0.5)), cos(eulerAngle.y * float(0.5)),cos(eulerAngle.z * float(0.5)));
		Vec3 s = Vec3(sin(eulerAngle.x * float(0.5)), sin(eulerAngle.y * float(0.5)),sin(eulerAngle.z * float(0.5)));
		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
}

Quat::Quat(const Mat3& m)
{
  *this = quatCast(m);
}
Quat::Quat(const Mat4& m)
{
  *this = quatCast(m);
}

Quat& Quat::operator=(Quat const& q)
{
	this->w = static_cast<float>(q.w);
	this->x = static_cast<float>(q.x);
	this->y = static_cast<float>(q.y);
	this->z = static_cast<float>(q.z);
	return *this;
}

Quat& Quat::operator+=(Quat const& q)
{
  this->w += static_cast<float>(q.w);
	this->x += static_cast<float>(q.x);
	this->y += static_cast<float>(q.y);
	this->z += static_cast<float>(q.z);
	return *this;
}
Quat& Quat::operator-=(Quat const& q)
{
  this->w -= static_cast<float>(q.w);
	this->x -= static_cast<float>(q.x);
	this->y -= static_cast<float>(q.y);
	this->z -= static_cast<float>(q.z);
	return *this;
}
Quat& Quat::operator*=(Quat const& r)
{
  const Quat p(*this);
	const Quat q(r);

	this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
	this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
	this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
	this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
	return *this;
}

Quat& Quat::operator*=(float s)
{
  this->w *= s;
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}
Quat& Quat::operator/=(float s)
{
  this->w /= s;
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

Quat operator+(Quat const& q)
{
  return q;
}
Quat operator-(Quat const& q)
{
  return Quat(-q.w, -q.x, -q.y, -q.z);
}
Quat operator+(Quat const& q, Quat const& p)
{
  return Quat(q) += p;
}
Quat operator-(Quat const& q, Quat const& p)
{
  return Quat(q) -= p;
}
Quat operator*(Quat const& q, Quat const& p)
{
  return Quat(q) *= p;
}
Vec3 operator*(Quat const& q, Vec3 const& v)
{
  const Vec3 QuatVector(q.x, q.y, q.z);
	const Vec3 uv(cross(QuatVector, v));
	const Vec3 uuv(cross(QuatVector, uv));

	return v + ((uv * q.w) + uuv) * static_cast<float>(2);
}
Vec3 operator*(Vec3 const& v, Quat const& q)
{
  return inverse(q) * v;
}
Vec4 operator*(Quat const& q, Vec4 const& v)
{
  return Vec4(q * Vec3(v), v.w);
}
Vec4 operator*(Vec4 const& v, Quat const& q)
{
  return inverse(q) * v;
}
Quat operator*(Quat const& q, float const& s)
{
  return Quat(q.w * s, q.x * s, q.y * s, q.z * s);
}
Quat operator*(float const& s, Quat const& q)
{
  return q * s;
}
Quat operator/(Quat const& q, float const& s)
{
  return Quat(q.w / s, q.x / s, q.y / s, q.z / s);
}

bool operator==(Quat const& q1, Quat const& q2)
{
  return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
}
bool operator!=(Quat const& q1, Quat const& q2)
{
  return !(q1 == q2);
}

}