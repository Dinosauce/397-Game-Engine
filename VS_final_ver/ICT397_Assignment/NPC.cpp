#include "NPC.h"
#include "NPCStates.h"

void NPC::SetHealth(int HP)
{
	Health = HP;
	
}

void NPC::InitialState()
{
	currentState = &Default_state::Instance();
}

int NPC::GetHealth()
{
	return Health;
}

void NPC::changeState(State<NPC> *newState)
{
	//call the exit method of the existing state
	currentState->Exit(this);
	//change state to the new state
	currentState = newState;
	//call the entry method of the new state
	currentState->Enter(this);
}

// state machine
void NPC::UpdateState(Player p){

	this->PL = p;
	if (currentState)
	{
		currentState->Execute(this);
	}
}