#include "math/Math.h"
#include "math/Quat.h"
#include "math/Vec4.h"
#include "math/Vec3.h"
#include "math/Mat4.h"
#include "math/Mat4.h"

namespace math
{
  float radians(float degrees)
  {
    return degrees * 0.01745329251994329576923690768489;
  }

  float dot(const glm::vec3& x, const glm::vec3& y)
  {
    glm::vec3 tmp(x * y);
    return tmp.x + tmp.y + tmp.z;
  }
	float dot(const glm::quat& a, const glm::quat& b)
	{
		glm::vec4 tmp(a.w * b.w, a.x * b.x, a.y * b.y, a.z * b.z);
		return (tmp.x + tmp.y) + (tmp.z + tmp.w);
	}
	glm::quat conjugate(const glm::quat& q)
	{
		return glm::quat(q.w, -q.x, -q.y, -q.z);
	}
	glm::vec3 cross(const glm::vec3& x, const glm::vec3& y)
	{
		return glm::vec3(
				x.y * y.z - y.y * x.z,
				x.z * y.x - y.z * x.x,
				x.x * y.y - y.x * x.y);
	}

  glm::vec3 normalize(const glm::vec3& v)
  {
    return v * (static_cast<float>(1) / sqrt(dot(v,v)));
  }

  glm::mat4 rotate(const glm::mat4& m, float radians, const glm::vec3& v)
  {
		const float a = radians;
		const float c = cos(a);
		const float s = sin(a);

		glm::vec3 axis(normalize(v));
		glm::vec3 temp((static_cast<float>(1) - c) * axis);

		glm::mat4 Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		glm::mat4 Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}
  
  glm::mat4 rotate(float radians, const glm::vec3& v)
  {
    return rotate(glm::mat4(1.0f), radians, v);
  }

  glm::quat catmullRom(const glm::quat& v1, const glm::quat& v2, const glm::quat& v3, const glm::quat& v4, const float& s)
  {
    float s2 = s * s;
    float s3 = s * s * s;

    float f1 = -s3 + static_cast<float>(2) * s2 - s;
		float f2 = static_cast<float>(3) * s3 - static_cast<float>(5) * s2 + static_cast<float>(2);
		float f3 = static_cast<float>(-3) * s3 + static_cast<float>(4) * s2 + s;
		float f4 = s3 - s2;

		return (f1 * v1 + f2 * v2 + f3 * v3 + f4 * v4) / static_cast<float>(2);
  }

	glm::vec3 catmullRom(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const float& s)
  {
    float s2 = s * s;
    float s3 = s * s * s;

    float f1 = -s3 + static_cast<float>(2) * s2 - s;
		float f2 = static_cast<float>(3) * s3 - static_cast<float>(5) * s2 + static_cast<float>(2);
		float f3 = static_cast<float>(-3) * s3 + static_cast<float>(4) * s2 + s;
		float f4 = s3 - s2;

		return (f1 * v1 + f2 * v2 + f3 * v3 + f4 * v4) / static_cast<float>(2);
  }
  glm::quat quatCast(const glm::mat3& m)
  {
    float fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
		float fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
		float fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
		float fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

		int biggestIndex = 0;
		float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		float biggestVal = sqrt(fourBiggestSquaredMinus1 + static_cast<float>(1)) * static_cast<float>(0.5);
		float mult = static_cast<float>(0.25) / biggestVal;

		switch(biggestIndex)
		{
		case 0:
			return glm::quat(biggestVal, (m[1][2] - m[2][1]) * mult, (m[2][0] - m[0][2]) * mult, (m[0][1] - m[1][0]) * mult);
		case 1:
			return glm::quat((m[1][2] - m[2][1]) * mult, biggestVal, (m[0][1] + m[1][0]) * mult, (m[2][0] + m[0][2]) * mult);
		case 2:
			return glm::quat((m[2][0] - m[0][2]) * mult, (m[0][1] + m[1][0]) * mult, biggestVal, (m[1][2] + m[2][1]) * mult);
		case 3:
			return glm::quat((m[0][1] - m[1][0]) * mult, (m[2][0] + m[0][2]) * mult, (m[1][2] + m[2][1]) * mult, biggestVal);
		default: //
			assert(false);
			return glm::quat(1, 0, 0, 0);
		}
  }

  glm::quat quatCast(const glm::mat4& m4)
  {
    return quatCast(glm::mat3(m4));
  }
  
  glm::mat3 toMat3(const glm::quat& q)
  {
    glm::mat3 result(float(1));
		float qxx(q.x * q.x);
		float qyy(q.y * q.y);
		float qzz(q.z * q.z);
		float qxz(q.x * q.z);
		float qxy(q.x * q.y);
		float qyz(q.y * q.z);
		float qwx(q.w * q.x);
		float qwy(q.w * q.y);
		float qwz(q.w * q.z);

		result[0][0] = float(1) - float(2) * (qyy +  qzz);
		result[0][1] = float(2) * (qxy + qwz);
		result[0][2] = float(2) * (qxz - qwy);

		result[1][0] = float(2) * (qxy - qwz);
		result[1][1] = float(1) - float(2) * (qxx +  qzz);
		result[1][2] = float(2) * (qyz + qwx);

		result[2][0] = float(2) * (qxz + qwy);
		result[2][1] = float(2) * (qyz - qwx);
		result[2][2] = float(1) - float(2) * (qxx +  qyy);
		return result;
  }

  glm::mat4 toMat4(const glm::quat& q)
  {
    return glm::mat4(toMat3(q));
  }

	glm::mat4 translate(const glm::mat4& m, const glm::vec3& v)
	{
		glm::mat4 result(m);
		result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return result;
	}

	glm::mat4 inverse(const glm::mat4& m)
	{
			float Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			float Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			float Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			float Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			float Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			float Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			float Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			float Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			float Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			float Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			float Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			float Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			float Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			float Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			float Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			float Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			float Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			float Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			glm::vec4 Fac0(Coef00, Coef00, Coef02, Coef03);
			glm::vec4 Fac1(Coef04, Coef04, Coef06, Coef07);
			glm::vec4 Fac2(Coef08, Coef08, Coef10, Coef11);
			glm::vec4 Fac3(Coef12, Coef12, Coef14, Coef15);
			glm::vec4 Fac4(Coef16, Coef16, Coef18, Coef19);
			glm::vec4 Fac5(Coef20, Coef20, Coef22, Coef23);

			glm::vec4 Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			glm::vec4 Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			glm::vec4 Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			glm::vec4 Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			glm::vec4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			glm::vec4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			glm::vec4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			glm::vec4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			glm::vec4 SignA(+1, -1, +1, -1);
			glm::vec4 SignB(-1, +1, -1, +1);
			glm::mat4 inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			glm::vec4 Row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

			glm::vec4 Dot0(m[0] * Row0);
			float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			float OneOverDeterminant = static_cast<float>(1) / Dot1;

			return inverse * OneOverDeterminant;
		}

  glm::mat3 inverse(const glm::mat3& m)
	{
			float OneOverDeterminant = static_cast<float>(1) / (
				+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

			glm::mat3 inverse;
			inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDeterminant;
			inverse[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDeterminant;
			inverse[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDeterminant;
			inverse[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDeterminant;
			inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDeterminant;
			inverse[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDeterminant;
			inverse[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDeterminant;
			inverse[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDeterminant;
			inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDeterminant;

			return inverse;
		}
	glm::quat inverse(const glm::quat& q)
	{
		return conjugate(q) / dot(q,q);
	}
	float angle(const glm::quat& x)
	{
		if (abs(x.w) > 0.877582561890372716130286068203503191)
		{
			return asin(sqrt(x.x * x.x + x.y * x.y + x.z * x.z)) * static_cast<float>(2);
		}
		return acos(x.w) * static_cast<float>(2);
	}

	glm::vec3 axis(const glm::quat& x)
	{
		const float tmp1 = static_cast<float>(1) - x.w * x.w;
		if(tmp1 <= static_cast<float>(0))
			return glm::vec3(0, 0, 1);
		const float tmp2 = static_cast<float>(1) / sqrt(tmp1);
		return glm::vec3(x.x * tmp2, x.y * tmp2, x.z * tmp2);
	}

	glm::quat angleAxis(const float& angle, const glm::vec3& v)
	{
		const float s = sin(angle * static_cast<float>(0.5));

		return glm::quat(cos(angle * static_cast<float>(0.5)), v * s);
	}

	glm::vec3 eulerAngles(const glm::quat& x)
	{
		return glm::vec3(pitch(x), yaw(x), roll(x));
	}

	float roll(const glm::quat& q)
	{
		return static_cast<float>(atan2(static_cast<float>(2) * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z));
	}

	float pitch(const glm::quat& q)
	{
		//return T(atan(T(2) * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
		const float y = static_cast<float>(2) * (q.y * q.z + q.w * q.x);
		const float x = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;

		if(x == 0.0 && y == 0.0) //avoid atan2(0,0) - handle singularity - Matiis
			return static_cast<float>(static_cast<float>(2) * atan2(q.x, q.w));

		return static_cast<float>(atan2(y, x));
	}

	float yaw(const glm::quat& q)
	{
		return asin(std::clamp(static_cast<float>(-2) * (q.x * q.z - q.w * q.y), static_cast<float>(-1), static_cast<float>(1)));
	}

	float length(const glm::vec3& v)
	{
		return sqrt(dot(v,v));
	}

	float length2(const glm::quat& q)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}

	glm::quat rotation(const glm::vec3& orig,const glm::vec3& dest)
	{
		float cosTheta = dot(orig, dest);
		glm::vec3 rotationAxis;

		if(cosTheta >= static_cast<float>(1) - std::numeric_limits<float>::epsilon()) {
			// orig and dest point in the same direction
			return glm::quat(1,0,0,0);
		}

		if(cosTheta < static_cast<float>(-1) + std::numeric_limits<float>::epsilon())
		{
			// special case when vectors in opposite directions :
			// there is no "ideal" rotation axis
			// So guess one; any will do as long as it's perpendicular to start
			// This implementation favors a rotation around the Up axis (Y),
			// since it's often what you want to do.
			rotationAxis = cross(glm::vec3(0, 0, 1), orig);
			if(length2(rotationAxis) < std::numeric_limits<float>::epsilon()) // bad luck, they were parallel, try again!
				rotationAxis = cross(glm::vec3(1, 0, 0), orig);

			rotationAxis = normalize(rotationAxis);
			return angleAxis(PI, rotationAxis);
		}

		// Implementation from Stan Melax's Game Programming Gems 1 article
		rotationAxis = cross(orig, dest);

		float s = sqrt((float(1) + cosTheta) * static_cast<float>(2));
		float invs = static_cast<float>(1) / s;

		return glm::quat(
			s * static_cast<float>(0.5f),
			rotationAxis.x * invs,
			rotationAxis.y * invs,
			rotationAxis.z * invs);
	}

	glm::vec3 mix(const glm::vec3& x, const glm::vec3& y, const float& a)
	{
		return glm::vec3(x * (static_cast<float>(1) - a) + y * a);
	}

	float mix(const float& x, const float& y, const float& a)
	{
		return static_cast<float>(x * (static_cast<float>(1) - a) + y * a);
	}

	glm::quat slerp(const glm::quat& x, const glm::quat& y, const float& a)
	{
		glm::quat z = y;

		float cosTheta = dot(x, y);

		// If cosTheta < 0, the interpolation will take the long way around the sphere.
		// To fix this, one quat must be negated.
		if(cosTheta < static_cast<float>(0))
		{
			z = -y;
			cosTheta = -cosTheta;
		}

		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if(cosTheta > static_cast<float>(1) - std::numeric_limits<float>::epsilon())
		{
			// Linear interpolation
			return glm::quat(
				mix(x.w, z.w, a),
				mix(x.x, z.x, a),
				mix(x.y, z.y, a),
				mix(x.z, z.z, a));
		}
		else
		{
			float angle = acos(cosTheta);
			return (sin((static_cast<float>(1) - a) * angle) * x + sin(a * angle) * z) / sin(angle);
		}
	}
}
