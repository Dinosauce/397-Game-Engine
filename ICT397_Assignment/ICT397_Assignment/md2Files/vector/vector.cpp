#include "vector.h"
#include "math/myMath.h"

vector3D::vector3D()
{
	x=0.0;
	y=0.0;
	z=0.0;
}

vector3D::vector3D(float xpos, float ypos, float zpos)
{
 set(xpos,ypos,zpos);
}

vector3D::vector3D(const vector3D &vec)
 {
	 set(vec);
 }

 void vector3D::set(const vector3D &v2)
 {
    x=v2.x;
	y=v2.y;
	z=v2.z;
 }

 void vector3D::set(float xpos, float ypos, float zpos)
 {
	x=xpos;
	y=ypos;
	z=zpos;
 }

 const vector3D &vector3D::operator=(const vector3D &vec)
 {
	x = vec.x;
    y = vec.y;
    z = vec.z;
  return *this;
 }

 vector3D vector3D::operator+(const vector3D &vec)const
 {
	 return vector3D(x+vec.x,y+vec.y,z+vec.z);
 }

 //vector inversion
 const vector3D vector3D::operator-() const
 {
	 return vector3D(-x, -y, -z);
 }



 vector3D vector3D::operator-(const vector3D &vec)const
 {
	 return vector3D(x-vec.x,y-vec.y,z-vec.z);
 }

 const vector3D& vector3D::operator+=(const vector3D &vec)
 {
	x += vec.x;
    y += vec.y;
    z += vec.z;
	return *this;
 }

  void vector3D::operator-=(const vector3D &vec)
 {
	x -= vec.x;
    y -= vec.y;
    z -= vec.z;
 }

 bool vector3D::operator==(const vector3D &vec)const
 {
	 return(x==vec.x && y==vec.y && z==vec.z);
 }
 void vector3D::setX(float xpos)
 {
	 x=xpos;
 }

  void vector3D::setY(float ypos)
 {
	 y=ypos;
 }

  void vector3D::setZ(float zpos)
 {
	 z=zpos;
 }

float vector3D::getX()
{
	return x;
}

float vector3D::getY()
{
	return y;
}

float vector3D::getZ()
{
	return z;
}

vector3D vector3D::crossProduct(const vector3D &vec)const
{
	return(vector3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x));
}

float vector3D::dotProduct(const vector3D &vec)const
{
	return(x*vec.x + y*vec.y + z*vec.z);
}
const vector3D &vector3D::operator/=(const float &val)
{
 const float recip = 1/val; // for speed, one division
   x *= recip;
   y *= recip;
   z *= recip;
 return (*this);
}

const vector3D vector3D::operator/(float val) const
{
  //more efficient than dividing 3 numbers
  val = 1/val;
  return vector3D(val*x, val*y, val*z);
}

const vector3D vector3D::operator*(const float &val) const
{
 return vector3D(x*val, y*val, z*val);
}

//magnitude of vector
float vector3D::length()
{
  return (sqrt((float)(x*x + y*y + z*z)));	
}

const double vector3D::squareLength() const
{
 return ((double)(x*x + y*y + z*z));
}

void vector3D::normalise()
{
 float f=length();
   if(f!=0)
   {
    x/=f;
    y/=f;
    z/=f; 
   }
}

//returns angle between 2 vectors. both vectors must
//be normalised prior to calling the function
const double inline vector3D::angle(const vector3D& normal)
{
  return acosf((*this).dotProduct(normal));
}

const vector3D inline vector3D::reflection(const vector3D& normal)
{    
  vector3D vec=*this;     
  vec.normalise();			// normalize this vector
  return ((vec - normal) * 2.0 * (vec.dotProduct(normal)) * length());
}

//gets the heading in degrees of a normalised
//vector usually representing the direction a velocity
//only returns a polar heading for x,z axes
double vector3D::getHeadingDegrees()
{
 float theta=0.0;

	 if(x==0.0)
	 {
	  theta=radToDeg((float)atan(z));
		 if(z>0)
		 {
		  theta+=45;
		 }
		 else
		 {
		  theta-=45;
		 }
	 }
	 else
	 {
	   theta=radToDeg((float)atan(z/x));
	 }
     if(z<0)
	 {
		 if(x>0)
			 theta=360+theta;
		 if(x<0)
			 theta=180+theta;
	 }
	 if(x<0 && z>=0)
		 theta=180+theta;
 return theta;
}

void vector3D::movePolarXZ(double moveDist, double& angle)
{
 point pos={x,z};

   movePolar2D(moveDist,pos,angle);
   x=pos.x;
   z=pos.y;
}

//converts a heading in degrees into a normalised
//heading vector
//use angle as y of polar coordinates and set x to 1
// as we are normalising.
void vector3D::degToNormalHeading(double& angle)
{
 point polar={1,degToRad(angle)};
 //convert polar to cartesian
 point cart=polarToCart(polar);
   x=cart.x;
   z=cart.y;
   //normalise to remove vector length
   normalise();
}