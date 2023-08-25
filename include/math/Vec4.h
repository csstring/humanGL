#pragma once
namespace math
{
	class Vec3;
}
namespace math
{
class Vec4
{
	public:
		float x;
		float y;
		float z;
		float w;
		
  public:
    explicit Vec4(float x, float y, float z, float w);
    explicit Vec4(float scalar);
		Vec4();
    Vec4(const Vec4& v);
		explicit Vec4(const Vec3& v);
		Vec4(float x, const Vec3& v);
		Vec4(const Vec3& v, float w);
    ~Vec4(){};
		float& operator[](int i);
		const float& operator[](int i) const;
		Vec4& operator=(Vec4 const& v);
		Vec4& operator+=(float scalar);
		Vec4& operator+=(Vec4 const& v);
		Vec4& operator-=(float scalar);
		Vec4& operator-=(Vec4 const& v);
		Vec4& operator*=(float scalar);
		Vec4& operator*=(Vec4 const& v);
		Vec4& operator/=(float scalar);
		Vec4& operator/=(Vec4 const& v);

};

Vec4 operator+(Vec4 const& v);
Vec4 operator-(Vec4 const& v);
Vec4 operator+(Vec4 const& v, float scalar);
Vec4 operator+(float scalar, Vec4 const& v);
Vec4 operator+(Vec4 const& v1, Vec4 const& v2);
Vec4 operator-(Vec4 const& v, float scalar);
Vec4 operator-(float scalar, Vec4 const& v);
Vec4 operator-(Vec4 const& v1, Vec4 const& v2);
Vec4 operator*(Vec4 const& v, float scalar);
Vec4 operator*(float scalar, Vec4 const& v);
Vec4 operator*(Vec4 const& v1, Vec4 const& v2);
Vec4 operator/(Vec4 const& v, float scalar);
Vec4 operator/(float scalar, Vec4 const& v);
Vec4 operator/(Vec4 const& v1, Vec4 const& v2);
bool operator==(Vec4 const& v1, Vec4 const& v2);
bool operator!=(Vec4 const& v1, Vec4 const& v2);
}