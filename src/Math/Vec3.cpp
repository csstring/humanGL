#include "math/Vec3.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)
{}
Vec3::Vec3(float scalar) : x(scalar), y(scalar), z(scalar)
{}
Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z)
{}

Vec3& Vec3::operator=(Vec3 const& v)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	this->z = static_cast<float>(v.z);
	return *this;
}

Vec3& Vec3::operator+=(float scalar)
{
	this->x += static_cast<float>(scalar);
	this->y += static_cast<float>(scalar);
	this->z += static_cast<float>(scalar);
	return *this;
}

Vec3& Vec3::operator+=(Vec3 const& v)
{
	this->x += static_cast<float>(v.x);
	this->y += static_cast<float>(v.y);
	this->z += static_cast<float>(v.z);
	return *this;
}

Vec3& Vec3::operator-=(float scalar)
{
	this->x -= static_cast<float>(scalar);
	this->y -= static_cast<float>(scalar);
	this->z -= static_cast<float>(scalar);
	return *this;
}

Vec3& Vec3::operator-=(Vec3 const& v)
{
	this->x -= static_cast<float>(v.x);
	this->y -= static_cast<float>(v.y);
	this->z -= static_cast<float>(v.z);
	return *this;
}

Vec3& Vec3::operator*=(float scalar)
{
	this->x *= static_cast<float>(scalar);
	this->y *= static_cast<float>(scalar);
	this->z *= static_cast<float>(scalar);
	return *this;
}

Vec3& Vec3::operator*=(Vec3 const& v)
{
	this->x *= static_cast<float>(v.x);
	this->y *= static_cast<float>(v.y);
	this->z *= static_cast<float>(v.z);
	return *this;
}

Vec3& Vec3::operator/=(float v)
{
	this->x /= static_cast<float>(v);
	this->y /= static_cast<float>(v);
	this->z /= static_cast<float>(v);
	return *this;
}

Vec3& Vec3::operator/=(Vec3 const& v)
{
	this->x /= static_cast<float>(v.x);
	this->y /= static_cast<float>(v.y);
	this->z /= static_cast<float>(v.z);
	return *this;
}


Vec3 operator+(Vec3 const& v)
{
	return v;
}

Vec3 operator-(Vec3 const& v)
{
	return Vec3( -v.x, -v.y, -v.z);
}

Vec3 operator+(Vec3 const& v, float scalar)
{
	return Vec3(v.x + scalar,v.y + scalar,v.z + scalar);
}

Vec3 operator+(float scalar, Vec3 const& v)
{
		return Vec3(scalar + v.x,scalar + v.y,scalar + v.z);
}

Vec3 operator-(Vec3 const& v, float scalar)
{
		return Vec3(v.x - scalar, v.y - scalar, v.z - scalar);
}

Vec3 operator-(float scalar, Vec3 const& v)
{
		return Vec3( scalar - v.x, scalar - v.y, scalar - v.z);
}

Vec3 operator*(Vec3 const& v, float scalar)
{
		return Vec3( v.x * scalar, v.y * scalar, v.z * scalar);
}

Vec3 operator*(float scalar, Vec3 const& v)
{
		return Vec3( scalar * v.x, scalar * v.y, scalar * v.z);
}

Vec3 operator/(Vec3 const& v, float scalar)
{
		return Vec3( v.x / scalar, v.y / scalar, v.z / scalar);
}

Vec3 operator/(float scalar, Vec3 const& v)
{
		return Vec3( scalar / v.x, scalar / v.y, scalar / v.z);
}

bool operator==(Vec3 const& v1, Vec3 const& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

bool operator!=(Vec3 const& v1, Vec3 const& v2)
{
	return !(v1 == v2);
}