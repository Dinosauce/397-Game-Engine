#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <iostream>
#include "State.h"

template <class entity_type>
class StateMachine{
public:
	StateMachine(entity_type *fsm_owner){
		owner = fsm_owner;
		pre_state = NULL;
		current_state = NULL;
		global_state = NULL;
	}

	virtual ~StateMachine(){};

	void Update() const{
		if (global_state)
			global_state->Execute(owner);
		if (current_state)
			current_state->Execute(owner);
	}

	void ChangeState(State<entity_type> *new_state){
		pre_state = current_state;
		current_state->Exit(owner);
		current_state = new_state;
		current_state->Enter(owner);
	}

	void RevertToPreState(){
		current_state = pre_state;
	}

	bool IsInState(const State<entity_type>& state) const{
		return (typeid(*current_state) == typeid(state));
	}

	// Setters
	// use the following methods to initialize the FSM
	void SetPreState(State<entity_type> *state){ pre_state = state; };
	void SetCurrentState(State<entity_type> *state){ current_state = state; };
	void SetGlobalState(State<entity_type> *state){ global_state = state; };

	// Getters
	State<entity_type>* GetPreState(){ return pre_state; };
	State<entity_type>* GetCurrentState(){ return current_state; };
	State<entity_type>* GetGlobalState(){ return global_state; };

private:
	entity_type* owner; //owner of the FSM
	State<entity_type> *pre_state;
	State<entity_type> *current_state;
	State<entity_type> *global_state;
};

#endif