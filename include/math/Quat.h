#pragma once
namespace math
{
  class Mat3;
  class Mat4;
  class Vec3;
  class Vec4;
}

namespace math
{
  class Quat
  {
    
    public:
      float x, y, z, w;
    
    public:
      float& operator[](int i);
		  const float& operator[](int i) const;

		Quat();
		Quat(const Quat& q);
		Quat(float s, const Vec3& v);
		Quat(float w, float x, float y, float z);
		/// Build a Quatternion from euler angles (pitch, yaw, roll), in radians.
		Quat(const Vec3& eulerAngles);
		Quat(const Mat3& q);
		Quat(const Mat4& q);

		Quat& operator=(Quat const& q);
		Quat& operator+=(Quat const& q);
		Quat& operator-=(Quat const& q);
		Quat& operator*=(Quat const& q);
		Quat& operator*=(float s);
		Quat& operator/=(float s);

    ~Quat(){};
  };
  Quat operator+(Quat const& q);
  Quat operator-(Quat const& q);
  Quat operator+(Quat const& q, Quat const& p);
  Quat operator-(Quat const& q, Quat const& p);
  Quat operator*(Quat const& q, Quat const& p);
  Vec3 operator*(Quat const& q, Vec3 const& v);
  Vec3 operator*(Vec3 const& v, Quat const& q);
  Vec4 operator*(Quat const& q, Vec4 const& v);
  Vec4 operator*(Vec4 const& v, Quat const& q);
  Quat operator*(Quat const& q, float const& s);
  Quat operator*(float const& s, Quat const& q);
  Quat operator/(Quat const& q, float const& s);

  bool operator==(Quat const& q1, Quat const& q2);
  bool operator!=(Quat const& q1, Quat const& q2);
}