#include "vector2D.h"
#include <fstream>
using namespace std;
#include "../math/myMath.h"

vector2D::vector2D()
{
	this->x=this->y=0.0;
}

vector2D::vector2D(double x, double y)
{
	this->x=x;
	this->y=y;
}

vector2D::vector2D(const vector2D &vec)
{
	x=vec.x;
	y=vec.y;
}

void vector2D::set(double x, double y)
{
 this->x=x;
 this->y=y;
}

bool vector2D::isZero()
{
	return (this->x==0 && this->y==0);
}
double& vector2D::operator[](unsigned short index)
{
     if(index >=0 && index <=1)
	   return *((&x)+index);
  return *(&x);
}

const vector2D& vector2D::operator=(const vector2D &vec)
{
  x = vec.x;
  y = vec.y;
  return *this;
}

bool vector2D::operator==(const vector2D &vec)const
{
 return ((x == vec.x) && (y == vec.y));
}

const bool vector2D::operator!=(const vector2D &vec) const
{
 return !(*this == vec);
}

const vector2D vector2D::operator+(const vector2D &vec) const
{
 return vector2D(x + vec.x, y + vec.y);
}

const vector2D& vector2D::operator+=(const vector2D& vec)
{    x += vec.x;
     y += vec.y;
 return *this;
}

const vector2D& vector2D::operator+=(double val)
{
	x+=val;
	y+=val;
 return *this;
}

const vector2D vector2D::operator-(const vector2D& vec) const
{    
 return vector2D(x - vec.x, y - vec.y);
}

const vector2D& vector2D::operator-(double val)
{
	x-=val;
	y-=val;
 return *this;
}

const vector2D vector2D::operator-() const
{    
 return vector2D(-x, -y);
}

const vector2D& vector2D::operator-=(const vector2D& vec)
{
   x -= vec.x;
   y -= vec.y;
 return *this;
}

const vector2D& vector2D::operator*=(double value)
{
    x*=value;
    y*=value;
  return *this;
 }

const vector2D& vector2D::operator/=(double value)
{
	  if(value!=0)
	  {
		x /= value;
		y /=value;
	  }
   
 return *this;
}

 const vector2D vector2D::operator*(double value) const
 {
  return vector2D(x*value, y*value);
 }

 const vector2D vector2D::operator*(const vector2D& vec) const
{
 return vector2D(x*vec.x, y*vec.y);
}

const vector2D vector2D::operator/(double value) const
{
	if(value==0)
		value=1;
	else
        value = 1/value;
 return vector2D(x*value, y*value);
}

const double vector2D::dotProduct(const vector2D &vec) const
{
 return x*vec.x + y*vec.y;
}

const double vector2D::length() const
{
 return (double)sqrt((double)(x*x + y*y));
}

void vector2D::setLength(double length)
{
	if(length>=1)
	{
		this->normalise();
		*this=*this*length;
	}
}

void vector2D::normalise()
{
 double len=length();
   if(len!=0)
      (*this) /=len;
}

// return angle between two vectors in radians
const double vector2D::angleInRadians(const vector2D& normalVec) const
{
 vector2D angle=*this;
 angle.normalise();
 return (double)acosf(angle.dotProduct(normalVec));
}

// return angle between two vectors in radians
const double vector2D::angleInDegrees(const vector2D& normalVec) const
{
 return(radToDeg(angleInRadians(normalVec))); 
}

const double vector2D::lengthSqr() const
{
 return (double)(x*x + y*y);
}

//truncate a magnitude to maxValue
void vector2D::trunc(double maxValue)
{ 
   if (this->length() > maxValue)
   {
	this->normalise();
	*this *= maxValue;
   } 
}

//determines theta in degrees from a vector heading
//assumes vector stores a normalised vector
double vector2D::getHeadingDegrees()
{
 vector2D heading=*this;
 heading.normalise();
 double x=heading[0];
 double y=heading[1];
 double theta=radToDeg((double)atan(y/x));
     if(y<0)
	 {
		 if(x>=0)
			 theta=360+theta;
		 if(x<0)
			 theta=180+theta;
	 }
	 if(x<0 && y>=0)
		 theta=180+theta;
 return theta;
}

ostream& operator<<(ostream& os, const vector2D& vec)
{
  os << " " << vec.x << " " << vec.y;

  return os;
}

