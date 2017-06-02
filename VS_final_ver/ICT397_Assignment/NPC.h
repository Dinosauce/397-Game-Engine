#ifndef NPC_H
#define NPC_H

#include "GameObject.h"
#include "State.h"
#include "StateMachine.h"
class NPC:public GameObject
{
public:
	NPC() :GameObject(){}
	void SetHealth(int HP);
	int GetHealth();

	StateMachine<GameObject>* GetFSM() const { return obj_fsm; };

	// state machine
	void UpdateState();
private:
	int Health;
	// state machine
	StateMachine<GameObject>* obj_fsm;
};
#endif