#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

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

#endif