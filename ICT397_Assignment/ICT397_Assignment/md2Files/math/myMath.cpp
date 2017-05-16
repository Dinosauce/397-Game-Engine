#include "myMath.h"

inline double degToRad(double radians)
{
	return (piOver180 * radians); 
}

//convert from radians to degrees
inline double radToDeg(double radians)
{
 radians*= (180.0 / PI);
 return radians;
}


//converts from cartesian to polar coords
point cartToPolar(double x, double y)
{
 point2D polar;

   polar.x=sqrt((x*x) + (y*y));
   polar.y= radToDeg((double)atan(y/x));
 return polar;
}

point polarToCart(point2D polar)
{
 point2D cart;
   cart.x=polar.x*cos(polar.x);
   cart.y=polar.x*sin(polar.y);
 return cart;
}


void movePolar2D(double moveDist,point2D& cartCoords, double& angle)
{
       if(angle>359)
         angle-=360;
       else if(angle<0)
         angle=360-angle;
       if(moveDist>=0)
        {
            cartCoords.x+=moveDist*cos(degToRad(angle));
            cartCoords.y += moveDist*sin(degToRad(angle));
        }
}


