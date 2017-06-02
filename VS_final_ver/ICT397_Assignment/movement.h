#ifndef __MOVEMENT_H
#define __MOVEMENT_H

#include "vector/vector2D.h"
#include "vector/vector.h"

class Movement
{
private:
vector2D wanderTarget;
double wanderRadius;
double wanderDistance;
double wanderJitter;

public:
/*********************************************************************************************
* Moves an object located at curpos and travelling at curVelocity towards targetPos. This    *
* function changes the curPos and curVelocity to steer it towards targetPos over time. The   *
* time factor is specified by timeElasped which should be the current time in the game loop  *
* timer. 20ms is a reasonable update time.                                                   *
* Pre: all vars are assigned values.                                                         *
* Post: curPos and curVelocity are updated to incrementally move towards targetPos. curPos   *
*       will be equal to targetPos if the object has reached the target.                     *
* Returns: true if target has reached targetPos, otherwise false.                            *
*********************************************************************************************/
bool moveTo(vector2D &curPos, const vector2D& targetPos,vector2D& curVelocity, double timeElapsed,double offset=0);
bool flee(vector2D &curPos, const vector2D& pursuerPos,vector2D& curVelocity, double fleeSpeed, double timeElapsed);
void pursue(const vector2D &evaderPos, vector2D& pursuerPos,const vector2D& evaderVelocity, vector2D& pursuerVelocity, double timeElapsed,double offset);
bool evade(vector2D &evaderPos,const vector2D& pursuerPos,vector2D& evaderVelocity,const vector2D& pursuerVelocity, double timeElapsed);
bool seeTarget(const vector2D &patroller,const vector2D& target, const vector2D &patrollerVel,float coneDistance, float coneRadius);
void setWander(double wanderRadius,double wanderDistance,double wanderJitter);
bool wander( vector2D &position, vector2D &velocity, double deltaT);
};
#endif