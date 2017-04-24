#include "Matrix.h"

Matrix::Matrix(){
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			matrix[i][j] = 0.0f;
		}
	}
}

Matrix::Matrix(const Matrix &new_matrix){
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			this->matrix[i][j] = new_matrix.matrix[i][j];
		}
	}
}

Matrix::Matrix(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33){
	matrix[0][0] = m00;
	matrix[0][1] = m01;
	matrix[0][2] = m02;
	matrix[0][3] = m03;

	matrix[1][0] = m10;
	matrix[1][1] = m11;
	matrix[1][2] = m12;
	matrix[1][3] = m13;

	matrix[2][0] = m20;
	matrix[2][1] = m21;
	matrix[2][2] = m22;
	matrix[2][3] = m23;

	matrix[3][0] = m30;
	matrix[3][1] = m31;
	matrix[3][2] = m32;
	matrix[3][3] = m33;
}

Matrix Matrix::operator +(const Matrix &var2){
	Matrix ret;
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			ret.matrix[i][j] = this->matrix[i][j] + var2.matrix[i][j];
		}
	}
	return ret;
}

Matrix Matrix::operator *(const Matrix &var2){
	Matrix ret;
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			for (int k = 0; k < SIZE; k++){
				ret.matrix[i][j] += this->matrix[i][k] * var2.matrix[k][j];
			}
		}
	}
	return ret;
}

Matrix Matrix::CreateRotationX(float rad){
	Matrix ret = Identity();
	
	ret.matrix[1][1] = cos(rad);
	ret.matrix[1][2] = sin(rad);
	ret.matrix[2][1] = -ret.matrix[1][2];
	ret.matrix[2][2] = ret.matrix[1][1];

	return ret;
}

Matrix Matrix::CreateRotationY(float rad){
	Matrix ret = Identity();

	ret.matrix[0][0] = cos(rad);
	ret.matrix[0][2] = sin(rad);
	ret.matrix[2][0] = -ret.matrix[0][2];
	ret.matrix[2][2] = ret.matrix[0][0];

	return ret;
}

Matrix Matrix::CreateRotationZ(float rad){
	Matrix ret;

	ret.matrix[0][0] = cos(rad);
	ret.matrix[0][1] = sin(rad);
	ret.matrix[1][0] = -ret.matrix[0][1];
	ret.matrix[1][1] = ret.matrix[0][0];

	return ret;
}

Matrix Matrix::Identity(){
	Matrix ret(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	return ret;
}