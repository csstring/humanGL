#pragma once
namespace math
{
	class Vec4;
}
namespace math
{
class Vec3
{
	public:
		union { float x, r, s; };
		union { float y, g, t; };
		union { float z, b, p; };

  public:
    explicit Vec3(float x, float y, float z);
    explicit Vec3(float scalar);
    Vec3(const Vec3& v);
		Vec3(const Vec4& v);
		Vec3();
    ~Vec3(){};
		float& operator[](int i);
		const float& operator[](int i) const;
		Vec3& operator=(Vec3 const& v);
		Vec3& operator+=(float scalar);
		Vec3& operator+=(Vec3 const& v);
		Vec3& operator-=(float scalar);
		Vec3& operator-=(Vec3 const& v);
		Vec3& operator*=(float scalar);
		Vec3& operator*=(Vec3 const& v);
		Vec3& operator/=(float scalar);
		Vec3& operator/=(Vec3 const& v);

};

Vec3 operator+(Vec3 const& v);
Vec3 operator-(Vec3 const& v);
Vec3 operator+(Vec3 const& v, float scalar);
Vec3 operator+(float scalar, Vec3 const& v);
Vec3 operator+(Vec3 const& v1, Vec3 const& v2);
Vec3 operator-(Vec3 const& v, float scalar);
Vec3 operator-(float scalar, Vec3 const& v);
Vec3 operator-(Vec3 const& v1, Vec3 const& v2);
Vec3 operator*(Vec3 const& v, float scalar);
Vec3 operator*(float scalar, Vec3 const& v);
Vec3 operator*(Vec3 const& v1, Vec3 const& v2);
Vec3 operator/(Vec3 const& v, float scalar);
Vec3 operator/(float scalar, Vec3 const& v);
Vec3 operator/(Vec3 const& v1, Vec3 const& v2);
bool operator==(Vec3 const& v1, Vec3 const& v2);
bool operator!=(Vec3 const& v1, Vec3 const& v2);
}