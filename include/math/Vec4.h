#pragma once

class Vec4
{
	public:
		union { float x, r, s; };
		union { float y, g, t; };
		union { float z, b, p; };
		union { float w, a, q; };
  public:
    explicit Vec4(float x, float y, float z, float w);
    explicit Vec4(float scalar);
    Vec4(const Vec4& v);
    ~Vec4(){};

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
Vec4 operator-(Vec4 const& v, float scalar);
Vec4 operator-(float scalar, Vec4 const& v);
Vec4 operator*(Vec4 const& v, float scalar);
Vec4 operator*(float scalar, Vec4 const& v);
Vec4 operator/(Vec4 const& v, float scalar);
Vec4 operator/(float scalar, Vec4 const& v);
bool operator==(Vec4 const& v1, Vec4 const& v2);
bool operator!=(Vec4 const& v1, Vec4 const& v2);
