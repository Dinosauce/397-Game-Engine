#ifndef __VECTOR2D_H
#define __VECTOR2D_H

#if _MCS_VER >= 1020
  #pragma once
#endif

#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

class vector2D
{
private:
	double x;
	double y;

public:
	 vector2D();
     vector2D(double x, double y);
     vector2D(const vector2D &vec); 
	 void set(double x, double y);
	 bool isZero();
	// vector index
	double& operator[](unsigned short index);
     // vector assignment
     const vector2D& operator=(const vector2D &vec);
     // vector equality
     bool operator==(const vector2D &vec)const;
     // vector inequality
     const bool operator!=(const vector2D &vec) const;
     // vector add
     const vector2D operator+(const vector2D &vec) const;
     // vector2D increment
     const vector2D& operator+=(const vector2D& vec);
	 const vector2D& operator+=(double val);
     // vector2D subtraction
     const vector2D operator-(const vector2D& vec) const;     
	 const vector2D& operator-(double val); 
     // vector2D negation
     const vector2D operator-() const;
     // vector2D decrement
     const vector2D &operator-=(const vector2D& vec);
     // scalar self-multiply
     const vector2D &operator*=(double value);
     // scalar self-divide
     const vector2D &operator/=(double value);
     // multiply by scalar
     const vector2D operator*(double value) const;
 	 const vector2D operator*(const vector2D& vec) const;
     // divide by scalar
     const vector2D operator/(double value) const;
	 friend ostream& operator<<(ostream& os, const vector2D& vec);
     // dot product
	 double getX()const{return x;}
	 double getY()const{return y;}
     const double dotProduct(const vector2D &vec) const;
     // length of vector2D
      const double length() const;
	 void setLength(double length);
     // normalize this vector2D
     void normalise();
     // return angle between two vectors in radians
     const double angleInRadians(const vector2D& normalVec) const;
	 // return angle between two vectors in degrees
     const double angleInDegrees(const vector2D& normalVec) const;
	 //squared length
     const double lengthSqr() const;
   	//truncate a magnitude to maxValue
  	 void trunc(double maxValue);
	 double getHeadingDegrees();
};
#endif