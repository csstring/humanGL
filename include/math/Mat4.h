#pragma once
#include "math/Vec4.h"
namespace math
{
	class Mat3;
}

namespace math
{
  class Mat4
  {
    public:
      Vec4 _value[4];

    public:

      Vec4& operator[](int i);
      const Vec4& operator[](int i) const;

      explicit Mat4();
		  Mat4(const Mat4& m);
      explicit Mat4(const Mat3& x);
      explicit Mat4(const float& x);
		  explicit Mat4(
			const float& x0, const float& y0, const float& z0, const float& w0,
			const float& x1, const float& y1, const float& z1, const float& w1,
			const float& x2, const float& y2, const float& z2, const float& w2,
			const float& x3, const float& y3, const float& z3, const float& w3);
		  explicit Mat4( const Vec4& v0, const Vec4& v1, const Vec4& v2, const Vec4& v3);
      ~Mat4(){};

      Mat4& operator=(const Mat4& m);
      Mat4& operator+=(float s);
      Mat4& operator+=(const Mat4& m);
      Mat4& operator-=(float s);
      Mat4& operator-=(const Mat4& m);
      Mat4& operator*=(float s);
      Mat4& operator*=(const Mat4& m);
      Mat4& operator/=(float s);
      Mat4& operator/=(const Mat4& m);
  };

	Mat4 operator+(Mat4 const& m);
	Mat4 operator-(Mat4 const& m);

	// -- Binary operators --
	Mat4 operator+(Mat4 const& m, float const& s);
	Mat4 operator+(float const& s, Mat4 const& m);
	Mat4 operator+(Mat4 const& m1, Mat4 const& m2);
	Mat4 operator-(Mat4 const& m, float const& s);
	Mat4 operator-(float const& s, Mat4 const& m);
	Mat4 operator-(Mat4 const& m1,	Mat4 const& m2);
	Mat4 operator*(Mat4 const& m, float const& s);
	Mat4 operator*(float const& s, Mat4 const& m);
	Vec4 operator*(Mat4 const& m, Vec4 const& v);
	Vec4 operator*(Vec4 const& v, Mat4 const& m);
	Mat4 operator*(Mat4 const& m1, Mat4 const& m2);
	Mat4 operator/(Mat4 const& m, float const& s);
	Mat4 operator/(float const& s, Mat4 const& m);
	Vec4 operator/(Mat4 const& m, Vec4 const& v);
	Vec4 operator/(Vec4 const& v, Mat4 const& m);
	Mat4 operator/(Mat4 const& m1,	Mat4 const& m2);

	// -- Boolean operators --
	bool operator==(Mat4 const& m1, Mat4 const& m2);
	bool operator!=(Mat4 const& m1, Mat4 const& m2);
}