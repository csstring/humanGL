#include "math/Mat4.h"
#include "math/Mat3.h"
#include "math/Math.h"
#include "Common.h"
namespace math
{
  Vec3& Mat3::operator[](int i)
  {
    assert(i < 3);
		return this->_value[i];
  }
  
  const Vec3& Mat3::operator[](int i) const
  {
    assert(i < 3);
		return this->_value[i];
  }

  Mat3::Mat3()
    : _value{Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1)}{}

  Mat3::Mat3(const Mat3& m)
    : _value{m[0], m[1], m[2]}{}

  Mat3::Mat3(const float& x)
    : _value{Vec3(x, 0, 0), Vec3(0, x, 0), Vec3(0, 0, x)}{}
  
  Mat3::Mat3(
  const float& x0, const float& y0, const float& z0,
  const float& x1, const float& y1, const float& z1,
  const float& x2, const float& y2, const float& z2)
  : _value{
			Vec3(x0, y0, z0),
			Vec3(x1, y1, z1),
			Vec3(x2, y2, z2)
    }{}
      
  Mat3::Mat3( const Vec3& v0, const Vec3& v1, const Vec3& v2)
    : _value{v0, v1, v2}{}

  Mat3::Mat3(const Mat4& m)
    : _value{Vec3(m[0]), Vec3(m[1]), Vec3(m[2])}{}

  Mat3& Mat3::operator=(const Mat3& m)
  {
    this->_value[0] = m[0];
		this->_value[1] = m[1];
		this->_value[2] = m[2];
		return *this;
  }

  Mat3& Mat3::operator+=(float s)
  {
    this->_value[0] += s;
		this->_value[1] += s;
		this->_value[2] += s;
		return *this;
  }

  Mat3& Mat3::operator+=(const Mat3& m)
  {
    this->_value[0] += m[0];
		this->_value[1] += m[1];
		this->_value[2] += m[2];
		return *this;
  }
  Mat3& Mat3::operator-=(float s)
  {
    this->_value[0] -= s;
		this->_value[1] -= s;
		this->_value[2] -= s;
		return *this;
  }
  Mat3& Mat3::operator-=(const Mat3& m)
  {
    this->_value[0] -= m[0];
		this->_value[1] -= m[1];
		this->_value[2] -= m[2];
		return *this;
  }
  Mat3& Mat3::operator*=(float s)
  {
    this->_value[0] *= s;
		this->_value[1] *= s;
		this->_value[2] *= s;
		return *this;
  }
  Mat3& Mat3::operator*=(const Mat3& m)
  {
    return (*this = *this * m);
  }
  Mat3& Mat3::operator/=(float s)
  {
    this->_value[0] /= s;
		this->_value[1] /= s;
		this->_value[2] /= s;
		return *this;
  }

  Mat3& Mat3::operator/=(const Mat3& m)
  {
    return *this *= inverse(m);
  }

  Mat3 operator+(Mat3 const& m)
  {
    return m;
  }

	Mat3 operator-(Mat3 const& m)
  {
    return Mat3(
			-m[0],
			-m[1],
			-m[2]);
  }


  Mat3 operator+(Mat3 const& m, float const& s)
  {
    return Mat3(
			m[0] + s,
			m[1] + s,
			m[2] + s);
  }

	Mat3 operator+(float const& s, Mat3 const& m)
  {
    return Mat3(
			m[0] + s,
			m[1] + s,
			m[2] + s);
  }

	Mat3 operator+(Mat3 const& m1, Mat3 const& m2)
  {
    return Mat3(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2]);
  }

	Mat3 operator-(Mat3 const& m, float const& s)
  {
    return Mat3(
			m[0] - s,
			m[1] - s,
			m[2] - s);
  } 

	Mat3 operator-(float const& s, Mat3 const& m)
  {
    return Mat3(
			s - m[0],
			s - m[1],
			s - m[2]);
  }

	Mat3 operator-(Mat3 const& m1,	Mat3 const& m2)
  {
    return Mat3(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2]);
  }

	Mat3 operator*(Mat3 const& m, float const& s)
  {
    return Mat3(
			m[0] * s,
			m[1] * s,
			m[2] * s);
  }

	Mat3 operator*(float const& s, Mat3 const& m)
  {
    return Mat3(
			m[0] * s,
			m[1] * s,
			m[2] * s);
  }

	Vec3 operator*(Mat3 const& m, Vec3 const& v)
  {
    return Vec3(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
  }

	Vec3 operator*(Vec3 const& v, Mat3 const& m)
  {
    return Vec3(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
  }

	Mat3 operator*(Mat3 const& m1, Mat3 const& m2)
  {
    const float SrcA00 = m1[0][0];
		const float SrcA01 = m1[0][1];
		const float SrcA02 = m1[0][2];
		const float SrcA10 = m1[1][0];
		const float SrcA11 = m1[1][1];
		const float SrcA12 = m1[1][2];
		const float SrcA20 = m1[2][0];
		const float SrcA21 = m1[2][1];
		const float SrcA22 = m1[2][2];

		const float SrcB00 = m2[0][0];
		const float SrcB01 = m2[0][1];
		const float SrcB02 = m2[0][2];
		const float SrcB10 = m2[1][0];
		const float SrcB11 = m2[1][1];
		const float SrcB12 = m2[1][2];
		const float SrcB20 = m2[2][0];
		const float SrcB21 = m2[2][1];
		const float SrcB22 = m2[2][2];

		Mat3 Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
		return Result;
  }

	Mat3 operator/(Mat3 const& m, float const& s)
  {
    return Mat3(
			m[0] / s,
			m[1] / s,
			m[2] / s);
  }

	Mat3 operator/(float const& s, Mat3 const& m)
  {
    return Mat3(
			s / m[0],
			s / m[1],
			s / m[2]);
  }

	Vec3 operator/(Mat3 const& m, Vec3 const& v)
  {
    return inverse(m) * v;
  }

	Vec3 operator/(Vec3 const& v, Mat3 const& m)
  {
    return v * inverse(m);
  }

	Mat3 operator/(Mat3 const& m1,	Mat3 const& m2)
  {
    Mat3 m1_copy(m1);
		return m1_copy /= m2;
  }


	// -- Boolean operators --
	bool operator==(Mat3 const& m1, Mat3 const& m2)
  {
    return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
  }

	bool operator!=(Mat3 const& m1, Mat3 const& m2)
  {
    return !(m1 == m2);
  }

}