#ifndef NPC_H
#define NPC_H

#include "GameObject.h"
#include "State.h"
#include "Player.h"

class NPC:public GameObject
{
public:
	NPC() :GameObject(){ }
	void InitialState();
	void SetHealth(int HP);
	int GetHealth();

	Player GetTarget(){ return PL; };
	void changeState(State<NPC>* newState);
	// state machine
	void UpdateState(Player P);
private:
	int Health;
	//Vector3 TargetPos;
	Player PL;
	// state machine
	State<NPC> *currentState;
};
#endif