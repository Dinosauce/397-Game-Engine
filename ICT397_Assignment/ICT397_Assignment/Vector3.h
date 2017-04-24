#ifndef VECTOR3_H
#define VECTOR3_H

#include "Matrix.h"

class Vector3{
	public:
		float x, y, z;

		Vector3(){ x = y = z = 0.0f; };
		Vector3(const Vector3 &new_vector3);
		~Vector3(){};
		Vector3(float var1, float var2, float var3);

		Vector3 operator +(const Vector3 &var2);
		Vector3 operator -(const Vector3 &var2);
		Vector3 operator *(const Vector3 &var2);
		Vector3 operator *(const float &scale);
		Vector3 operator /(const Vector3 &var2);
		bool operator ==(const Vector3 &var2);
		bool operator !=(const Vector3 &var2);

		static Vector3 UnitX();
		static Vector3 UnitY();
		static Vector3 UnitZ();
		static Vector3 Zero();

		static Vector3 Transform(const Vector3 &vector3, const Matrix &matrix);
		float Distance(const Vector3 &var1, const Vector3 &var2);
		void Normalize();
};

#endif