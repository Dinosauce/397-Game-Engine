#ifndef GAMEMATHHELP_H
#define GAMEMATHHELP_H

#include <math.h>

#define _PI 3.14159265359f
#define _TWO_PI 6.28318530717f

class MathHelp{
	public:

		// Converts degrees to radians
		static float ToRadians(float degrees);

		// Restricts a value to be within a specified range
		static float Clamp(float value, float min, float max);

		// Float modulo function (remainder has same sign as the divisor)
		static float FloatMod(float var1, float var2);

		// Reduces a given angle to a value between pi and -pi
		static float WrapAngle(float angle);
};

// stores a matrix with size 4x4 in float
class Matrix{
public:
	float matrix[4][4];
	static const int SIZE = 4;

	Matrix();
	Matrix(const Matrix &new_matrix);
	Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	Matrix operator +(const Matrix &var2);
	Matrix operator *(const Matrix &var2);

	static Matrix CreateRotationX(float rad);
	static Matrix CreateRotationY(float rad);
	static Matrix CreateRotationZ(float rad);

private:
	static Matrix Identity();
};

// stores a vector with x, y, z in float
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