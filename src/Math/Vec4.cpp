#include "math/Vec4.h"
#include "math/Vec3.h"
#include "Common.h"
namespace math
{
Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{}
Vec4::Vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar)
{}
Vec4::Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w)
{}
Vec4::Vec4(const Vec3& v) : x(v.x), y(v.y), z(v.z), w(0)
{}

Vec4::Vec4():x(0), y(0), z(0), w(0)
{}
Vec4::Vec4(float x, const Vec3& v) : x(x), y(v.x), z(v.y), w(v.z)
{}
Vec4::Vec4(const Vec3& v, float w) : x(v.x), y(v.y), z(v.z), w(w)
{}
float& Vec4::operator[](int i)
{
	assert(i >= 0 && i < 4);
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
}
const float& Vec4::operator[](int i) const
{
	assert(i >= 0 && i < 4);
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
}
Vec4& Vec4::operator=(Vec4 const& v)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	this->z = static_cast<float>(v.z);
	this->w = static_cast<float>(v.w);
	return *this;
}

Vec4& Vec4::operator+=(float scalar)
{
	this->x += static_cast<float>(scalar);
	this->y += static_cast<float>(scalar);
	this->z += static_cast<float>(scalar);
	this->w += static_cast<float>(scalar);
	return *this;
}

Vec4& Vec4::operator+=(Vec4 const& v)
{
	this->x += static_cast<float>(v.x);
	this->y += static_cast<float>(v.y);
	this->z += static_cast<float>(v.z);
	this->w += static_cast<float>(v.w);
	return *this;
}

Vec4& Vec4::operator-=(float scalar)
{
	this->x -= static_cast<float>(scalar);
	this->y -= static_cast<float>(scalar);
	this->z -= static_cast<float>(scalar);
	this->w -= static_cast<float>(scalar);
	return *this;
}

Vec4& Vec4::operator-=(Vec4 const& v)
{
	this->x -= static_cast<float>(v.x);
	this->y -= static_cast<float>(v.y);
	this->z -= static_cast<float>(v.z);
	this->w -= static_cast<float>(v.w);
	return *this;
}

Vec4& Vec4::operator*=(float scalar)
{
	this->x *= static_cast<float>(scalar);
	this->y *= static_cast<float>(scalar);
	this->z *= static_cast<float>(scalar);
	this->w *= static_cast<float>(scalar);
	return *this;
}

Vec4& Vec4::operator*=(Vec4 const& v)
{
	this->x *= static_cast<float>(v.x);
	this->y *= static_cast<float>(v.y);
	this->z *= static_cast<float>(v.z);
	this->w *= static_cast<float>(v.w);
	return *this;
}

Vec4& Vec4::operator/=(float scalar)
{
	this->x /= static_cast<float>(scalar);
	this->y /= static_cast<float>(scalar);
	this->z /= static_cast<float>(scalar);
	this->w /= static_cast<float>(scalar);
	return *this;
}

Vec4& Vec4::operator/=(Vec4 const& v)
{
	this->x /= static_cast<float>(v.x);
	this->y /= static_cast<float>(v.y);
	this->z /= static_cast<float>(v.z);
	this->w /= static_cast<float>(v.w);
	return *this;
}


Vec4 operator+(Vec4 const& v)
{
	return v;
}

Vec4 operator-(Vec4 const& v)
{
	return Vec4( -v.x, -v.y, -v.z, -v.w);
}

Vec4 operator+(Vec4 const& v, float scalar)
{
	return Vec4(v.x + scalar,v.y + scalar,v.z + scalar, v.w +scalar);
}

Vec4 operator+(float scalar, Vec4 const& v)
{
		return Vec4(scalar + v.x,scalar + v.y,scalar + v.z, scalar + v.w);
}

Vec4 operator+(Vec4 const& v1, Vec4 const& v2)
{
		return Vec4(v1) += v2;
}

Vec4 operator-(Vec4 const& v, float scalar)
{
		return Vec4(v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar);
}

Vec4 operator-(float scalar, Vec4 const& v)
{
		return Vec4( scalar - v.x, scalar - v.y, scalar - v.z, scalar - v.w);
}

Vec4 operator-(Vec4 const& v1, Vec4 const& v2)
{
		return Vec4(v1) -= v2;
}

Vec4 operator*(Vec4 const& v, float scalar)
{
		return Vec4( v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

Vec4 operator*(float scalar, Vec4 const& v)
{
		return Vec4( scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}

Vec4 operator*(Vec4 const& v1, Vec4 const& v2)
{
	return Vec4(v1) *= v2;
}

Vec4 operator/(Vec4 const& v, float scalar)
{
		return Vec4( v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

Vec4 operator/(float scalar, Vec4 const& v)
{
		return Vec4( scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
}

Vec4 operator/(Vec4 const& v1, Vec4 const& v2)
{
	return Vec4(v1) /= v2;
}

bool operator==(Vec4 const& v1, Vec4 const& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
}

bool operator!=(Vec4 const& v1, Vec4 const& v2)
{
	return !(v1 == v2);
}
}