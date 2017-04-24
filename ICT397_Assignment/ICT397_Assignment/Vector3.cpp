#include "Vector3.h"

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