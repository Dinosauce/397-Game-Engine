#ifndef GAMEMATHHELP_H
#define GAMEMATHHELP_H

#include <math.h>

#define _PI 3.14159265359f /// PI in float
#define _TWO_PI 6.28318530717f /// 2PI in float

/**
* MathHelp class - Plentoon Games
* Calculates the general maths for the game
*/
class MathHelp{
	public:
		/**
		* Converts degrees to radians
		* @param input degrees
		* @return output radians
		*/
		static float ToRadians(const float & degrees);

		/**
		* Restricts a value to be within a specified range
		* @param input value
		* @param min of the range
		* @param max of the range
		* @return either the input value or the range value
		*/
		static float Clamp(const float & value, const float & min, const float & max);

		/**
		* Float modulo function (remainder has same sign as the divisor)
		* @param dividend
		* @param divisor
		* @return remainder
		*/
		static float FloatMod(const float & var1, const float & var2);

		/**
		* Reduces a given angle to a value between pi and -pi
		* @param input angle
		* @return value after wrapped between pi and -pi
		*/
		static float WrapAngle(const float & angle);
};

/**
* Matrix class - Plentoon Games
* stores a matrix with size 4x4 in float
* reference from XNA
*/
class Matrix{
	public:
		/**
		* Ctor
		* default elements = 0.0
		*/
		Matrix();

		/**
		* Copy Ctor
		*/
		Matrix(const Matrix & new_matrix);

		/**
		* Ctor with set values
		* @param set values from [0,0] to [4,4], top down, left to right
		*/
		Matrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		/**
		* overrided plus operator - add two matrixes
		* @param adder matrix
		* @return result matrix
		*/
		Matrix operator +(const Matrix & var2);
	
		/**
		* overrided multiply operator - multiplies two matrixes
		* @param multipler matrix
		* @return result matrix
		*/
		Matrix operator *(const Matrix & var2);

		/**
		* create a rotation matrix in x-axis with object matrix and input radians
		* @param radians value
		* @return result matrix
		*/
		static Matrix CreateRotationX(const float & rad);
	
		/**
		* create a rotation matrix in y-axis with object matrix and input radians
		* @param radians value
		* @return result matrix
		*/
		static Matrix CreateRotationY(const float & rad);
	
		/**
		* create a rotation matrix in z-axis with object matrix and input radians
		* @param radians value
		* @return result matrix
		*/
		static Matrix CreateRotationZ(const float & rad);

		/// matrix
		float matrix[4][4];

		/// matrix size
		static const int SIZE = 4;

	private:
		/**
		* Get identity matrix
		* @return identity matrix 
		*/
		static Matrix Identity();
};

/**
* Vector3 class - Plentoon Games
* stores a vector with x, y, z in float
* reference from XNA
*/
class Vector3{
	public:
		/**
		* Ctor
		* default elements = 0.0
		*/
		Vector3(){ x = y = z = 0.0f; };

		/**
		* Copy Ctor
		*/
		Vector3(const Vector3 & new_vector3);

		/**
		* Ctor with set values
		* @param set values x, y, z
		*/
		Vector3(float var1, float var2, float var3);

		/**
		* overrided plus operator - add two vectors
		* @param adder vector
		* @return result vector
		*/
		Vector3 operator +(const Vector3 & var2);

		/**
		* overrided minus operator - minus two vectors
		* @param minus vector
		* @return result vector
		*/
		Vector3 operator -(const Vector3 & var2);
		
		/**
		* overrided multiply operator - multiplies two vectors
		* @param multiplier vector
		* @return result vector
		*/
		Vector3 operator *(const Vector3 & var2);

		/**
		* overrided multiply operator - multiplies vector with a scale
		* @param scale value
		* @return result vector
		*/
		Vector3 operator *(const float & scale);
		
		/**
		* overrided division operator - divide two vectors
		* @param divisor vector
		* @return result vector
		*/
		Vector3 operator /(const Vector3 & var2);

		/**
		* overrided equals operator - compare two vectors
		* @param compare vector
		* @return true if same, false otherwise
		*/
		bool operator ==(const Vector3 & var2);

		/**
		* overrided not equals operator - compare two vectors
		* @param compare vector
		* @return true if not same, false otherwise
		*/
		bool operator !=(const Vector3 & var2);

		/**
		* vector with [1,0,0]
		* @return [1,0,0]
		*/
		static Vector3 UnitX();
		
		/**
		* vector with [0,1,0]
		* @return [0,1,0]
		*/
		static Vector3 UnitY();
		
		/**
		* vector with [0,0,1]
		* @return [0,0,1]
		*/
		static Vector3 UnitZ();
		
		/**
		* vector with [0,0,0]
		* @return [0,0,0]
		*/
		static Vector3 Zero();

		/**
		* transform the vector with the input matrix
		* @param input vector
		* @param input matrix
		* @return result vector
		*/
		static Vector3 Transform(const Vector3 & vector3, const Matrix & matrix);

		/**
		* calculate the distance between two vectors
		* @return distance in float
		*/
		float Distance(const Vector3 & var1, const Vector3 & var2);

		/**
		* normalize the current vector object
		*/
		void Normalize(); 
		
		/// vector values
		float x, y, z;
};

#endif