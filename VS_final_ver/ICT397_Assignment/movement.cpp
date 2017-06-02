#include "movement.h"
#include "math/myMath.h"
#include <iomanip>
/*********************************************************************************************
* Moves an object located at curpos and travelling at curVelocity towards targetPos. This    *
* function changes the curPos and curVelocity to steer it towards targetPos over time. The   *
* time factor is specified by timeElasped which should be the current time in the game loop  *
* timer. 20ms is a reasonable update time.                                                   *
* Pre: all vars are assigned values.                                                         *
* Post: curPos and curVelocity are updated to incrementally move towards targetPos. curPos   *
*       will be equal to targetPos if the object has reached the target.                     *
* Variables: curPos is the position vector of the current agent.                             *
*            targetPos is the vector of the target position.                                 *
*            curVelocity is the current velocity of the agent.                               *
*            timeElaspsed is the time elaspsed since last logic update.                      *
*            offset is the distance to stop prior to reaching the target.                    *
*********************************************************************************************/
bool Movement::moveTo(vector2D &curPos, const vector2D& targetPos,vector2D& curVelocity, double timeElapsed,double offset)
{ 
 bool xdone=false, zdone=false;
 vector2D newPos;  

  vector2D toTarget = targetPos - curPos;  //vector between current position and target
  toTarget.normalise();                       //get heading
  vector2D pos=targetPos;
    if(!toTarget.isZero())
    {
     pos+=-(toTarget*offset);
    }
    if(curPos==pos)
	 {
	   return true;
	 }
  curVelocity=toTarget*curVelocity.length();  //new velocity
  newPos=curVelocity*timeElapsed;             //pos = vt
    //test if we have arrived at location.
    if(curPos.getX() == pos.getX())
     {
	  xdone=true;
     }
    else if(curPos.getX() < pos.getX())
	 {
		 if(curPos.getX()+newPos.getX()>=pos.getX())
			 xdone=true;
	 }
	 else if(curPos.getX()>pos.getX())
	 {
		 if(curPos.getX()+newPos.getX()<=pos.getX())
			 xdone=true;
	 }
    if(curPos.getY() == pos.getY())
	 {
		 zdone=true;
	 }
    else if(curPos.getY() < pos.getY())
	 {
		 if(curPos.getY()+newPos.getY()>=pos.getY())
			 zdone=true;
	 }
	 else if(curPos.getY()>pos.getY())
	 {
		 if(curPos.getY()+newPos.getY()<=pos.getY())
			 zdone=true;
	 }    
    if(xdone && zdone)
	{
		curPos=pos;
		return true;
	}
	else
		curPos+=newPos;
 return false;
}

bool Movement::flee(vector2D &curPos, const vector2D& pursuerPos,vector2D& curVelocity,  double fleeSpeed, double timeElapsed)
{ 
 vector2D fromPursuer;
 double panicDistSq=100.0*100.0;

   fromPursuer=curPos-pursuerPos;
     if(fromPursuer.lengthSqr()>panicDistSq)
		 return false;    //pursuer not in panic range

  fromPursuer.normalise();                       //get heading
  curVelocity=fromPursuer*fleeSpeed;  //new velocity
  curPos+=curVelocity*timeElapsed;             //pos = vt
  return true;
}

void Movement::pursue(const vector2D &evaderPos, vector2D& pursuerPos,const vector2D& evaderVelocity, vector2D& pursuerVelocity, double timeElapsed,double offset)
{
 double lookAheadTime;
 //distance between evader and pursuer
 vector2D toEvader=evaderPos-pursuerPos;	
 //compute agent headings
 vector2D pursuerHeading=pursuerVelocity;
 pursuerHeading.normalise();
 vector2D evaderHeading=evaderVelocity;
 evaderHeading.normalise();
 //compute angle between agents
 double relativeHeading=pursuerHeading.dotProduct(evaderHeading);
    //determine if evader is facing pursuer - note .95 radians =18 degrees
 if(((toEvader.dotProduct(pursuerHeading)>0) && relativeHeading <-0.95) || evaderVelocity.length()==1)
	{
		moveTo(pursuerPos,evaderPos,pursuerVelocity,timeElapsed,offset);
	}
	else
	{
	 lookAheadTime=(toEvader.length())/(evaderVelocity.length()+pursuerVelocity.length());
	 moveTo(pursuerPos,evaderPos+evaderVelocity*lookAheadTime,pursuerVelocity,timeElapsed,offset);
	}
}

bool Movement::evade(vector2D &evaderPos,const vector2D& pursuerPos,vector2D& evaderVelocity,const vector2D& pursuerVelocity, double timeElapsed)
{
 //distance between pursuer and evader
 vector2D toPursuer=pursuerPos-evaderPos;
 double lookaheadTime=toPursuer.length()/(evaderVelocity.length()+pursuerVelocity.length());
 return(flee(evaderPos,pursuerPos+pursuerVelocity*lookaheadTime,evaderVelocity,evaderVelocity.length(),timeElapsed));
}

//fov in degrees not radians
bool Movement::seeTarget(const vector2D &patroller,const vector2D& target, const vector2D &patrollerVel,float coneDistance, float fov)
{
	//vector between patroller and target
	vector2D toTarget = target-patroller;
	//distance between patroller and target
	float dist=toTarget.length();	  
	if(dist>coneDistance)
		  return false;
	//get heading to target
	toTarget.normalise();
	vector2D patrollerHeading=patrollerVel;
	//get patrollers current heading
	patrollerHeading.normalise();
	//compute angle between patroller and target
	double angle=(double)patrollerHeading.dotProduct(toTarget);
	  //getting some precision problem ensure cos angle is in -1.0 to 1.0
	  if(angle>1.0)
		  angle=1.0;
	  else if(angle<-1.0)
	      angle=-1.0;
    angle=radToDeg(acos(angle)); //get heading in degrees
	//determine if target is in fov
	if(angle <=(fov/2))
		return true;
 return false;
}


    inline double randFloat()      
	{
		return ((rand())/(RAND_MAX+1.0));
	}
    
	//returns a random double in the range -1 < n < 1
    inline double randomClamped()    
	{
		return randFloat() - randFloat();
	}


void Movement::setWander(double wanderRadius,double wanderDistance,double wanderJitter)
{
	this->wanderRadius=wanderRadius;
	this->wanderDistance=wanderDistance;
	this->wanderJitter=wanderJitter;
	double theta = ((rand())/(RAND_MAX+1.0)) * (2*PI);
	wanderTarget.set(wanderRadius * cos(theta),wanderRadius * sin(theta));
}

//--------------------------- Wander -------------------------------------
//
//  This behavior makes the agent wander about randomly
//   does not wander on the z axis
//------------------------------------------------------------------------
bool Movement::wander( vector2D &position, vector2D &velocity,double deltaT)
{ 
  //this behavior is dependent on the update rate, so this line must
  //be included when using time independent framerate.
  double jitterThisTimeSlice = wanderJitter * deltaT;
  //first, add a small random vector to the target's position
  wanderTarget += vector2D(randomClamped() * jitterThisTimeSlice,randomClamped() * jitterThisTimeSlice);
  //reproject this new vector back on to a unit circle
  wanderTarget.normalise();
  vector2D heading(velocity);
  heading.normalise();
  vector2D wanderCircleWorldCentre=position+(heading* wanderDistance);
  vector2D targetWorld=wanderCircleWorldCentre+( wanderTarget * wanderRadius);
  moveTo(position, targetWorld,velocity, deltaT,0);
return true;
}