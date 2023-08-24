#include "math/Mat4.h"
#include "math/Mat3.h"
#include "math/Math.h"
#include "Common.h"
namespace math
{
  Vec4& Mat4::operator[](int i)
  {
    assert(i < 4);
		return this->_value[i];
  }
  
  const Vec4& Mat4::operator[](int i) const
  {
    assert(i < 4);
		return this->_value[i];
  }

  Mat4::Mat4()
    : _value{Vec4(1, 0, 0, 0), Vec4(0, 1, 0, 0), Vec4(0, 0, 1, 0), Vec4(0, 0, 0, 1)}{}

  Mat4::Mat4(const Mat4& m)
    : _value{m[0], m[1], m[2], m[3]}{}

  Mat4::Mat4(const float& x)
    : _value{Vec4(x, 0, 0, 0), Vec4(0, x, 0, 0), Vec4(0, 0, x, 0), Vec4(0, 0, 0, x)}{}
  
  Mat4::Mat4(
  const float& x0, const float& y0, const float& z0, const float& w0,
  const float& x1, const float& y1, const float& z1, const float& w1,
  const float& x2, const float& y2, const float& z2, const float& w2,
  const float& x3, const float& y3, const float& z3, const float& w3)
  : _value{
			Vec4(x0, y0, z0, w0),
			Vec4(x1, y1, z1, w1),
			Vec4(x2, y2, z2, w2),
			Vec4(x3, y3, z3, w3)}{}
      
  Mat4::Mat4( const Vec4& v0, const Vec4& v1, const Vec4& v2, const Vec4& v3)
    : _value{v0, v1, v2, v3}{}

  Mat4::Mat4(const Mat3& m)
    : _value{Vec4(m[0], 0), Vec4(m[1], 0), Vec4(m[2], 0), Vec4(0, 0, 0, 1)}{}

  Mat4& Mat4::operator=(const Mat4& m)
  {
    this->_value[0] = m[0];
		this->_value[1] = m[1];
		this->_value[2] = m[2];
		this->_value[3] = m[3];
		return *this;
  }

  Mat4& Mat4::operator+=(float s)
  {
    this->_value[0] += s;
		this->_value[1] += s;
		this->_value[2] += s;
		this->_value[3] += s;
		return *this;
  }

  Mat4& Mat4::operator+=(const Mat4& m)
  {
    this->_value[0] += m[0];
		this->_value[1] += m[1];
		this->_value[2] += m[2];
		this->_value[3] += m[3];
		return *this;
  }
  Mat4& Mat4::operator-=(float s)
  {
    this->_value[0] -= s;
		this->_value[1] -= s;
		this->_value[2] -= s;
		this->_value[3] -= s;
		return *this;
  }
  Mat4& Mat4::operator-=(const Mat4& m)
  {
    this->_value[0] -= m[0];
		this->_value[1] -= m[1];
		this->_value[2] -= m[2];
		this->_value[3] -= m[3];
		return *this;
  }
  Mat4& Mat4::operator*=(float s)
  {
    this->_value[0] *= s;
		this->_value[1] *= s;
		this->_value[2] *= s;
		this->_value[3] *= s;
		return *this;
  }
  Mat4& Mat4::operator*=(const Mat4& m)
  {
    return (*this = *this * m);
  }
  Mat4& Mat4::operator/=(float s)
  {
    this->_value[0] /= s;
		this->_value[1] /= s;
		this->_value[2] /= s;
		this->_value[3] /= s;
		return *this;
  }
  Mat4& Mat4::operator/=(const Mat4& m)
  {
    return *this *= inverse(m);
  }

  Mat4 operator+(Mat4 const& m)
  {
    return m;
  }

	Mat4 operator-(Mat4 const& m)
  {
    return Mat4(-m[0],-m[1],-m[2],-m[3]);
  }

	Mat4 operator+(Mat4 const& m, float const& s)
  {
    return Mat4(m[0] + s,m[1] + s,m[2] + s,m[3] + s);
  }

	Mat4 operator+(float const& s, Mat4 const& m)
  {
    return Mat4(m[0] + s,m[1] + s,m[2] + s,m[3] + s);
  }

	Mat4 operator+(Mat4 const& m1, Mat4 const& m2)
  {
    return Mat4(m1[0] + m2[0],m1[1] + m2[1],m1[2] + m2[2],m1[3] + m2[3]);
  }

	Mat4 operator-(Mat4 const& m, float const& s)
  {
    return Mat4(m[0] - s,m[1] - s,m[2] - s,m[3] - s);
  }

	Mat4 operator-(float const& s, Mat4 const& m)
  {
    return Mat4(s - m[0],s - m[1],s - m[2],s - m[3]);
  }

	Mat4 operator-(Mat4 const& m1,	Mat4 const& m2)
  {
    return Mat4(m1[0] - m2[0],m1[1] - m2[1],m1[2] - m2[2],m1[3] - m2[3]);
  }

	Mat4 operator*(Mat4 const& m, float const& s)
  {
    return Mat4(m[0] * s,m[1] * s,m[2] * s,m[3] * s);
  }

	Mat4 operator*(float const& s, Mat4 const& m)
  {
    return Mat4(m[0] * s,m[1] * s,m[2] * s,m[3] * s);
  }

	Vec4 operator*(Mat4 const& m, Vec4 const& v)
  {
    const Vec4 Mov0(v[0]);
		const Vec4 Mov1(v[1]);
		const Vec4 Mul0 = m[0] * Mov0;
		const Vec4 Mul1 = m[1] * Mov1;
		const Vec4 Add0 = Mul0 + Mul1;
		const Vec4 Mov2(v[2]);
		const Vec4 Mov3(v[3]);
		const Vec4 Mul2 = m[2] * Mov2;
		const Vec4 Mul3 = m[3] * Mov3;
		const Vec4 Add1 = Mul2 + Mul3;
		const Vec4 Add2 = Add0 + Add1;
		return Add2;
  }

	Vec4 operator*(Vec4 const& v, Mat4 const& m)
  {
    return Vec4(
			m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
			m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
			m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
			m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]);
  }

	Mat4 operator*(Mat4 const& m1, Mat4 const& m2)
  {
    const Vec4 SrcA0 = m1[0];
		const Vec4 SrcA1 = m1[1];
		const Vec4 SrcA2 = m1[2];
		const Vec4 SrcA3 = m1[3];

		const Vec4 SrcB0 = m2[0];
		const Vec4 SrcB1 = m2[1];
		const Vec4 SrcB2 = m2[2];
		const Vec4 SrcB3 = m2[3];

		Mat4 Result;
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
		Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
		Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
		return Result;
  }

	Mat4 operator/(Mat4 const& m, float const& s)
  {
    return Mat4(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s);
  }

	Mat4 operator/(float const& s, Mat4 const& m)
  {
    return Mat4(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]);
  }

	Vec4 operator/(Mat4 const& m, Vec4 const& v)
  {
    return inverse(m) * v;
  }

	Vec4 operator/(Vec4 const& v, Mat4 const& m)
  {
    return v * inverse(m);
  }

	Mat4 operator/(Mat4 const& m1,	Mat4 const& m2)
  {
    Mat4 m1_copy(m1);
		return m1_copy /= m2;
  }

	bool operator==(Mat4 const& m1, Mat4 const& m2)
  {
    return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
  }

	bool operator!=(Mat4 const& m1, Mat4 const& m2)
  {
    return !(m1 == m2);
  }

}