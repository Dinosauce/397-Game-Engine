#ifndef USERINTERFACE_H
#define USERINTERFACE_H


#include "Texture.h"
#include "TextureMap.h"
#include <cstdio>
#include <iostream>

#include <GL/glut.h>

class UserInterface
{
public:
	void DisplayHealth();

	void mainMenu(int width, int height, int pos_x, int pos_y);
	
	/**
	* @brief  getter for health
	*
	* @return health
	*/
	int getHealth();

	/**
	* @brief  Setter for health
	*
	* @param int he
	* @return void
	*/
	void setHealth(int he);

	/**
	* @brief  getter for score
	*
	* @return score
	*/
	int getScore();

	/**
	* @brief  Setter for score
	*
	* @param int sc
	* @return void
	*/
	void setScore(int sc);
public:
	UserInterface();
	~UserInterface();

private:
	int health, score;

	static Texture2D texture2d;

	static int screen_width, screen_height;
};
#endif

