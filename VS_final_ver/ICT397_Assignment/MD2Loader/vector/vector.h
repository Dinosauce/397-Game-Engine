#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

class vector3D
{
public:
	float x;
	float y;
	float z;    // x,y,z coordinates
public:
	 vector3D();
     vector3D(float xpos, float ypos, float zpos);
     vector3D(const vector3D &vec);
     void set(const vector3D &v2);
	 void set(float xpos, float ypos, float zpos);
	 void setX(float xpos);
	 void setY(float ypos);
	 void setZ(float zpos);
	 float getX();
	 float getY();
	 float getZ();
     // vector assignment
     const vector3D &operator=(const vector3D &vec);
	 const vector3D&  operator+=(const vector3D &vec);
	 vector3D operator+(const vector3D &vec)const;
	      
	 vector3D operator-(const vector3D &vec)const;
	  //vector inversion
 const vector3D operator-() const;
     void operator-=(const vector3D &vec);
	 bool operator==(const vector3D &vec)const;
     vector3D crossProduct(const vector3D &vec)const; 
     float dotProduct(const vector3D &vec)const;
	 const vector3D &operator/=(const float &val);
	 const vector3D operator/(float val) const;
     // post multiply by float
     const vector3D operator*(const float &val) const;
	 //magnitude of vector
	 float length(); 
	 //squared length
     const double squareLength() const;
	 //returns angle between 2 vectors. both vectors must
	 //be normalised prior to calling the function
	 void normalise();
	 const double inline angle(const vector3D& normal);
	 // reflect this vector off surface with normal vector
	      // reflect this vector off surface with normal vector
     const vector3D inline reflection(const vector3D& normal);
	 double vector3D::getHeadingDegrees();
	 void movePolarXZ(double moveDist, double& angle);

//converts a heading in degrees into a normalised
//heading vector
//use angle as y of polar coordinates and set x to 1
// as we are normalising.
void degToNormalHeading(double& angle);
};
#endif