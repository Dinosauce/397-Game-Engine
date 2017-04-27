#include "GameMathHelp.h"

// ==========================
// MathHelp
// ==========================
float MathHelp::ToRadians(const float & degrees){
	return (degrees * _PI / 180);
}

float MathHelp::Clamp(const float & value, const float & min, const float & max){
	if (value < min){
		return min;
	}
	if (value > max){
		return max;
	}
	return value;
}

float MathHelp::FloatMod(const float & var1, const float & var2){
	if (var2 == 0.0)
		return var1;

	float rem = var1 - var2 * floor(var1 / var2);

	// Handle boundary cases resulted from float cut off
	if (var2 > 0){
		if (rem >= var2)
			return 0;

		if (rem < 0){
			if ((var2 + rem) == var2)
				return 0;
			else
				return (var2 + rem);
		}
	}

	else{
		if (rem <= var2)
			return 0;

		if (rem > 0){
			if ((var2 + rem) == var2)
				return 0;
			else
				return (var2 + rem);
		}
	}

	return rem;
}

float MathHelp::WrapAngle(const float & angle){
	return (FloatMod((angle + _PI), _TWO_PI) - _PI);
}

// ==========================
// Vector3
// ==========================
Vector3::Vector3(float var1, float var2, float var3){
	x = var1;
	y = var2;
	z = var3;
}

Vector3::Vector3(const Vector3 &new_vector3){
	this->x = new_vector3.x;
	this->y = new_vector3.y;
	this->z = new_vector3.z;
}

Vector3 Vector3::operator +(const Vector3 &var2){
	Vector3 ret;
	ret.x = this->x + var2.x;
	ret.y = this->y + var2.y;
	ret.z = this->z + var2.z;
	return ret;
}

Vector3 Vector3::operator -(const Vector3 &var2){
	Vector3 ret;
	ret.x = this->x - var2.x;
	ret.y = this->y - var2.y;
	ret.z = this->z - var2.z;
	return ret;
}

Vector3 Vector3::operator *(const Vector3 &var2){
	Vector3 ret;
	ret.x = this->x * var2.x;
	ret.y = this->y * var2.y;
	ret.z = this->z * var2.z;
	return ret;
}

Vector3 Vector3::operator *(const float &scale){
	Vector3 ret;
	ret.x = this->x * scale;
	ret.y = this->y * scale;
	ret.z = this->z * scale;
	return ret;
}

Vector3 Vector3::operator /(const Vector3 &var2){
	Vector3 ret;
	ret.x = this->x / var2.x;
	ret.y = this->y / var2.y;
	ret.z = this->z / var2.z;
	return ret;
}

bool Vector3::operator ==(const Vector3 &var2){
	if ((this->x == var2.x) && (this->y == var2.y) && (this->z == var2.z)){
		return true;
	}
	else{
		return false;
	}
}

bool Vector3::operator !=(const Vector3 &var2){
	if ((this->x == var2.x) && (this->y == var2.y) && (this->z == var2.z)){
		return false;
	}
	else{
		return true;
	}
}

Vector3 Vector3::UnitX(){
	Vector3 ret(1.0f, 0.0f, 0.0f);
	return ret;
}

Vector3 Vector3::UnitY(){
	Vector3 ret(0.0f, 1.0f, 0.0f);
	return ret;
}

Vector3 Vector3::UnitZ(){
	Vector3 ret(0.0f, 0.0f, 1.0f);
	return ret;
}

Vector3 Vector3::Zero(){
	Vector3 ret(0.0f, 0.0f, 0.0f);
	return ret;
}

Vector3 Vector3::Transform(const Vector3 &vector3, const Matrix &matrix){
	Vector3 ret;

	ret.x = vector3.x * matrix.matrix[0][0] + vector3.y * matrix.matrix[1][0] + vector3.z * matrix.matrix[2][0] + matrix.matrix[3][0];
	ret.y = vector3.x * matrix.matrix[0][1] + vector3.y * matrix.matrix[1][1] + vector3.z * matrix.matrix[2][1] + matrix.matrix[3][1];
	ret.z = vector3.x * matrix.matrix[0][2] + vector3.y * matrix.matrix[1][2] + vector3.z * matrix.matrix[2][2] + matrix.matrix[3][2];

	return ret;
}

float Vector3::Distance(const Vector3 &var1, const Vector3 &var2){
	return (float)sqrt(
		(var1.x - var2.x) * (var1.x - var2.x) +
		(var1.y - var2.y) * (var1.y - var2.y) +
		(var1.z - var2.z) * (var1.z - var2.z)
		);
}

void Vector3::Normalize(){
	Vector3 this_vector(this->x, this->y, this->z);

	float factor = Distance(this_vector, Vector3::Zero());
	factor = 1.0f / factor;

	this->x *= factor;
	this->y *= factor;
	this->z *= factor;
}

// ==========================
// Matrix
// ==========================
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

Matrix Matrix::CreateRotationX(const float & rad){
	Matrix ret = Identity();

	ret.matrix[1][1] = cos(rad);
	ret.matrix[1][2] = sin(rad);
	ret.matrix[2][1] = -ret.matrix[1][2];
	ret.matrix[2][2] = ret.matrix[1][1];

	return ret;
}

Matrix Matrix::CreateRotationY(const float & rad){
	Matrix ret = Identity();

	ret.matrix[0][0] = cos(rad);
	ret.matrix[0][2] = sin(rad);
	ret.matrix[2][0] = -ret.matrix[0][2];
	ret.matrix[2][2] = ret.matrix[0][0];

	return ret;
}

Matrix Matrix::CreateRotationZ(const float & rad){
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
