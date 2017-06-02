#include "NPC.h"
#include "NPCStates.h"
void NPC::SetHealth(int HP)
{
	Health = HP;
	// state machine
	obj_fsm = new StateMachine<GameObject>(this);
	obj_fsm->SetCurrentState(&walk_state::Instance());
	obj_fsm->SetGlobalState(&global_state::Instance());
}

int NPC::GetHealth()
{
	return Health;
}

// state machine
void NPC::UpdateState(){
	obj_fsm->Update();
}