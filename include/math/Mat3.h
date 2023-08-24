#pragma once
#include "math/Vec3.h"
#include "Common.h"

class Mat4;
namespace math
{
  class Mat3
  {
    private:
      Vec3 _value[3];
      const uint8   _length = 3;

    public:

      Vec3& operator[](uint8 i);
      const Vec3& operator[](uint8 i) const;

      explicit Mat3();
		  explicit Mat3(const Mat3& m);
      explicit Mat3(const float& x);
		  Mat3(
			const float& x0, const float& y0, const float& z0,
			const float& x1, const float& y1, const float& z1,
			const float& x2, const float& y2, const float& z2);
		  Mat3( const Vec3& v0, const Vec3& v1, const Vec3& v2);
      Mat3(const Mat4& x);
      ~Mat3(){};

      Mat3& operator=(const Mat3& m);
      Mat3& operator+=(float s);
      Mat3& operator+=(const Mat3& m);
      Mat3& operator-=(float s);
      Mat3& operator-=(const Mat3& m);
      Mat3& operator*=(float s);
      Mat3& operator*=(const Mat3& m);
      Mat3& operator/=(float s);
      Mat3& operator/=(const Mat3& m);
  };

	Mat3 operator+(Mat3 const& m);
	Mat3 operator-(Mat3 const& m);

	// -- Binary operators --
	Mat3 operator+(Mat3 const& m, float const& s);
	Mat3 operator+(float const& s, Mat3 const& m);
	Mat3 operator+(Mat3 const& m1, Mat3 const& m2);
	Mat3 operator-(Mat3 const& m, float const& s);
	Mat3 operator-(float const& s, Mat3 const& m);
	Mat3 operator-(Mat3 const& m1,	Mat3 const& m2);
	Mat3 operator*(Mat3 const& m, float const& s);
	Mat3 operator*(float const& s, Mat3 const& m);
	Vec3 operator*(Mat3 const& m, Vec3 const& v);
	Vec3 operator*(Vec3 const& v, Mat3 const& m);
	Mat3 operator*(Mat3 const& m1, Mat3 const& m2);
	Mat3 operator/(Mat3 const& m, float const& s);
	Mat3 operator/(float const& s, Mat3 const& m);
	Vec3 operator/(Mat3 const& m, Vec3 const& v);
	Vec3 operator/(Vec3 const& v, Mat3 const& m);
	Mat3 operator/(Mat3 const& m1,	Mat3 const& m2);

	// -- Boolean operators --
	bool operator==(Mat3 const& m1, Mat3 const& m2);
	bool operator!=(Mat3 const& m1, Mat3 const& m2);
}