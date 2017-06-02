#ifndef __MUSHROOMSTATES_H
#define __MUSHROOMSTATES_H

#include "singleton.h"
#include "State.h"
#include "GameObject.h"

class GameObject;

class Global : public State <GameObject> {
public:
	void Enter(GameObject *thing);
	void Execute(GameObject *thing);
	void Exit(GameObject *thing);
};

class Walk : public State < GameObject > {
public:
	void Enter(GameObject *thing);
	void Execute(GameObject *thing);
	void Exit(GameObject *thing);
};

typedef singleton<Global> global_state;
typedef singleton<Walk> walk_state;

#endif