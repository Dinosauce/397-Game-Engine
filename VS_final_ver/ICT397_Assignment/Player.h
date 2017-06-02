#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player:public GameObject
{
public: 
	Player() :GameObject(){ Health = 100; }

	void SetHealth(int HP);
	int GetHealth();

private:
	int Health;

};

#endif