#ifndef PARTICLEEMMITTER_H
#define PARTICLEEMMITTER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <iostream>

#include <GL/glut.h>

#define MAX_PARTICLES 3000

using namespace std;

typedef float fVector[3];

enum dimensions{X,Y,Z};

struct Particle
{

	float lifespan, age, scale, direction;
	fVector position;
	fVector movement;
	fVector color;
	fVector pull;

};

class ParticleEmmitter
{
public:
	ParticleEmmitter();
	~ParticleEmmitter();
	
	void DrawParticles(ParticleEmmitter particleSystem);

		/**
		* @brief  Creates and initialises a single particle
		*
		* 
		*
		* @param p, a pointer of type particle *
		* @return void
		*/
	void createParticle(Particle *p);
		/**
		* @brief  calls createParticle to initialise all particles in the system
		*
		* @return void
		*/
	void createParticles();

	

	void updateParticles();
	int getNumofParticles();
	float getXPos(int i); //returns x position of particle i
	float getYPos(int i); //returns y position of particle i
	float getZPos(int i); //returns z position of particle i
	float getR(int i); //returns red component of particle i
	float getG(int i); //returns green component of particle i
	float getB(int i); //returns blue component of particle i
	float getScale(int i); //returns scale of particle
	float getDirection(int i); //returns direction of particle for texture rotation
	float getAlpha(int i); //returns how faded (according to age) the particle should be

	void modifySystemPull(float x, float y, float z); //used to modify x,y,z pull magnitudes

private:
	fVector systemPull;
	Particle particles[MAX_PARTICLES];
};

#endif