#ifndef GAMEMATHHELP_H
#define GAMEMATHHELP_H

#include <math.h>

#define _PI 3.14159265359 /// PI in double
#define _TWO_PI 6.28318530717 /// 2PI in double

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
		static double ToRadians(const double & degrees);

		/**
		* Converts radians to degrees
		* @param input radians
		* @return output degrees
		*/
		static double ToDegrees(const double & radians);

		/**
		* Restricts a value to be within a specified range
		* @param input value
		* @param min of the range
		* @param max of the range
		* @return either the input value or the range value
		*/
		static double Clamp(const double & value, const double & min, const double & max);

		/**
		* double modulo function (remainder has same sign as the divisor)
		* @param dividend
		* @param divisor
		* @return remainder
		*/
		static double doubleMod(const double & var1, const double & var2);

		/**
		* Reduces a given angle to a value between pi and -pi
		* @param input angle
		* @return value after wrapped between pi and -pi
		*/
		static double WrapAngle(const double & angle);
};

/**
* Matrix class - Plentoon Games
* stores a matrix with size 4x4 in double
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
		Matrix(double m00, double m01, double m02, double m03,
			double m10, double m11, double m12, double m13,
			double m20, double m21, double m22, double m23,
			double m30, double m31, double m32, double m33);

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
		static Matrix CreateRotationX(const double & rad);
	
		/**
		* create a rotation matrix in y-axis with object matrix and input radians
		* @param radians value
		* @return result matrix
		*/
		static Matrix CreateRotationY(const double & rad);
	
		/**
		* create a rotation matrix in z-axis with object matrix and input radians
		* @param radians value
		* @return result matrix
		*/
		static Matrix CreateRotationZ(const double & rad);

		/// matrix
		double matrix[4][4];

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
* stores a vector with x, y, z in double
* reference from XNA
*/
class Vector3{
	public:
		/**
		* Ctor
		* default elements = 0.0
		*/
		Vector3(){ x = y = z = 0.0; };

		/**
		* Copy Ctor
		*/
		Vector3(const Vector3 & new_vector3);

		/**
		* Ctor with set values
		* @param set values x, y, z
		*/
		Vector3(double var1, double var2, double var3);

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
		Vector3 operator *(const double & scale);
		
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
		* @return distance in double
		*/
		double Distance(const Vector3 & var1, const Vector3 & var2);

		/**
		* normalize the current vector object
		*/
		void Normalize(); 

		void set(double var1, double var2, double var3);
		
		/// vector values
		double x, y, z;
};

#endif