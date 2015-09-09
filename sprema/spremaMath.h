#pragma once

#include <cmath>

namespace spremaMath
{
	class Vector3
	{
		public:
			Vector3() {}
			
			Vector3(float _x, float _y, float _z) :
				x(_x),
				y(_y),
				z(_z)
			{}

			~Vector3() {};

			inline float length()
			{
				return sqrt(x*x + y*y + z*z);
			}

			inline void normalize()
			{
				float l = length();
				x /= l;
				y /= l;
				z /= l;
			}

			inline float dotProduct(Vector3 &tar)
			{
				return x * tar.x + y * tar.y + z * tar.z;
			}

			inline Vector3 crossProduct(Vector3 &tar)
			{
				return Vector3(y*tar.z - z*tar.y, x*tar.z - z*tar.x, x*tar.y - y*tar.x);
			}

			inline Vector3 Vector3::operator +(const Vector3 &v)
			{
				return Vector3(x + v.x, y + v.y, z + v.z);
			}

			inline Vector3 Vector3::operator -(const Vector3 &v)
			{
				return Vector3(x - v.x, y - v.y, z - v.z);
			}

			inline Vector3 Vector3::operator *(const float a)
			{
				return Vector3(x * a, y * a, z * a);
			}

			inline Vector3 Vector3::operator /(const float a)
			{
				return Vector3(x / a, y / a, z / a);
			}

			float x;
			float y;
			float z;
		private:
			//todo
	};

	class Quaternion
	{
		public:
			Quaternion() {};
			Quaternion(float _w, float _x, float _y, float _z):
				w(_w),
				x(_x),
				y(_y),
				z(_z)
			{}

			Quaternion(Vector3 axis, float angle) :
				w(cos(angle / 2.00)),
				x(axis.x * sin(angle / 2.00)),
				y(axis.y * sin(angle / 2.00)),
				z(axis.z * sin(angle / 2.00))
			{}

			inline float length()
			{
				return sqrt(w*w + x*x + y*y + z*z);
			}

			inline void normalize()
			{
				float l = length();
				x /= l;
				y /= l;
				z /= l;
				w /= l;
			}

			inline Quaternion Inverted()
			{
				return Quaternion(w, -x, -y, -z);
			}

			inline Quaternion Quaternion::operator *(Quaternion &tar)
			{
				return Quaternion(
					w * tar.w - x * tar.x - y * tar.y - z * tar.z,
					x * tar.w + w * tar.x + y * tar.z - z * tar.y,
					y * tar.w + w * tar.y + z * tar.x - x * tar.z,
					z * tar.w + w * tar.z + x * tar.y - y * tar.x);
			}

			inline Vector3 Quaternion::operator *(Vector3 &tar)
			{
				return Vector3(
					w * tar.x + y * tar.z - z * tar.y,
					w * tar.y + z * tar.x - x * tar.z,
					w * tar.z + x * tar.y - y * tar.x);
			}

			float w;
			float x;
			float y;
			float z;
	};
}