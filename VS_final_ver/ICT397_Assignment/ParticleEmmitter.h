#ifndef PARTICLEEMMITTER_H
#define PARTICLEEMMITTER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <iostream>

#include <GL/glut.h>

#define MAX_PARTICLES 6000

using namespace std;

typedef float fVector[3];

enum dimensions{X,Y,Z};
enum ParticleTypeEnum { explosion, fountain };

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

		/**
		* @brief  Draws the particles
		*
		* @param particleSystem, a pointer of type ParticleEmmitter *
		* @return void
		*/
	void DrawParticles(ParticleEmmitter* particleSystem);

		/**
		* @brief  Creates and initialises a single particle
		*
		* 
		*
		* @param Xpos, the initial X position of the particles
		* @param Ypos, the initial Y position of the particles
		* @param Zpos, the initial Z position of the particles
		* @param p, a pointer of type particle *
		* @return void
		*/
	void createParticle(Particle *p, float Xpos, float Ypos, float Zpos, ParticleTypeEnum type);
		
		/**
		* @brief  calls createParticle to initialise all particles in the system
		*
		* @param Xpos, the initial X position of the particles 
		* @param Ypos, the initial Y position of the particles 
		* @param Zpos, the initial Z position of the particles 
		* @return void
		*/
	void createParticles(float Xpos, float Ypos, float Zpos, ParticleTypeEnum type);

		/**
		* @brief  updates the particles positions based on their velocitys
		*
		* @return void
		*/
	void updateParticles();
		
		/**
		* @brief  Getter function for the variable MAX_PARTICLES
		*
		* @return MAX_PARTICLES an integer value
		*/
	int getNumofParticles();

		/**
		* @brief  Getter function for a particles x position
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].position[X] a float value
		*/
	float getXPos(int i); 

		/**
		* @brief  Getter function for a particles Y position
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].position[Y] a float value
		*/
	float getYPos(int i);

		/**
		* @brief  Getter function for a particles Z position
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].position[Z] a float value
		*/
	float getZPos(int i);

		/**
		* @brief  Getter function for a particles Red colour value
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].color[X] a float value
		*/
	float getR(int i);

		/**
		* @brief  Getter function for a particles Green colour value
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].color[Y] a float value
		*/
	float getG(int i); 

		/**
		* @brief  Getter function for a particles Blue colour value
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].color[Z] a float value
		*/
	float getB(int i); 

		/**
		* @brief  Getter function for a particles scale value
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].scale a float value
		*/
	float getScale(int i);
		
		/**
		* @brief  Getter function for the direction of the particle
		*
		* @param int i, a variable determining which particle to take value from
		* @return particles[i].direction a float value
		*/
	float getDirection(int i);
	
		/**
		* @brief  Getter function for how faded the particle should be based on its age and lifespan
		*
		* @param int i, a variable determining which particle to take value from
		* @return (1 - particles[i].age / particles[i].lifespan) a float value
		*/
	float getAlpha(int i); 

		/**
		* @brief  Adjusts the system pull
		*
		* @param float X,y,z used to modify the x,y,z pull magnitudes
		* @return void
		*/
	void modifySystemPull(float x, float y, float z); //used to modify x,y,z pull magnitudes

private:
	ParticleTypeEnum ParticleType;
	fVector systemPull;
	fVector initialPos;
	int randomness;
	Particle particles[MAX_PARTICLES];
};

#endif