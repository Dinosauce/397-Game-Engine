#include "GameMathHelp.h"

// ==========================
// MathHelp
// ==========================
double MathHelp::ToRadians(const double & degrees){
	return (degrees * _PI / 180);
}

double MathHelp::Clamp(const double & value, const double & min, const double & max){
	if (value < min){
		return min;
	}
	if (value > max){
		return max;
	}
	return value;
}

double MathHelp::doubleMod(const double & var1, const double & var2){
	if (var2 == 0.0)
		return var1;

	double rem = var1 - var2 * floor(var1 / var2);

	// Handle boundary cases resulted from double cut off
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

double MathHelp::WrapAngle(const double & angle){
	return (doubleMod((angle + _PI), _TWO_PI) - _PI);
}

// ==========================
// Vector3
// ==========================
Vector3::Vector3(double var1, double var2, double var3){
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

Vector3 Vector3::operator *(const double &scale){
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
	Vector3 ret(1.0, 0.0, 0.0);
	return ret;
}

Vector3 Vector3::UnitY(){
	Vector3 ret(0.0, 1.0, 0.0);
	return ret;
}

Vector3 Vector3::UnitZ(){
	Vector3 ret(0.0, 0.0, 1.0);
	return ret;
}

Vector3 Vector3::Zero(){
	Vector3 ret(0.0, 0.0, 0.0);
	return ret;
}

Vector3 Vector3::Transform(const Vector3 &vector3, const Matrix &matrix){
	Vector3 ret;

	ret.x = vector3.x * matrix.matrix[0][0] + vector3.y * matrix.matrix[1][0] + vector3.z * matrix.matrix[2][0] + matrix.matrix[3][0];
	ret.y = vector3.x * matrix.matrix[0][1] + vector3.y * matrix.matrix[1][1] + vector3.z * matrix.matrix[2][1] + matrix.matrix[3][1];
	ret.z = vector3.x * matrix.matrix[0][2] + vector3.y * matrix.matrix[1][2] + vector3.z * matrix.matrix[2][2] + matrix.matrix[3][2];

	return ret;
}

double Vector3::Distance(const Vector3 &var1, const Vector3 &var2){
	return (double)sqrt(
		(var1.x - var2.x) * (var1.x - var2.x) +
		(var1.y - var2.y) * (var1.y - var2.y) +
		(var1.z - var2.z) * (var1.z - var2.z)
		);
}

void Vector3::Normalize(){
	Vector3 this_vector(this->x, this->y, this->z);

	double factor = Distance(this_vector, Vector3::Zero());
	factor = 1.0 / factor;

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
			matrix[i][j] = 0.0;
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

Matrix::Matrix(double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33){
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

Matrix Matrix::CreateRotationX(const double & rad){
	Matrix ret = Identity();

	ret.matrix[1][1] = cos(rad);
	ret.matrix[1][2] = sin(rad);
	ret.matrix[2][1] = -ret.matrix[1][2];
	ret.matrix[2][2] = ret.matrix[1][1];

	return ret;
}

Matrix Matrix::CreateRotationY(const double & rad){
	Matrix ret = Identity();

	ret.matrix[0][0] = cos(rad);
	ret.matrix[0][2] = sin(rad);
	ret.matrix[2][0] = -ret.matrix[0][2];
	ret.matrix[2][2] = ret.matrix[0][0];

	return ret;
}

Matrix Matrix::CreateRotationZ(const double & rad){
	Matrix ret;

	ret.matrix[0][0] = cos(rad);
	ret.matrix[0][1] = sin(rad);
	ret.matrix[1][0] = -ret.matrix[0][1];
	ret.matrix[1][1] = ret.matrix[0][0];

	return ret;
}

Matrix Matrix::Identity(){
	Matrix ret(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return ret;
}
