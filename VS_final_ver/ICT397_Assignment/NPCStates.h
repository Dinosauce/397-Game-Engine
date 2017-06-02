#ifndef __NPCSTATES_H
#define __NPCSTATES_H

#include "singleton.h"
#include "State.h"
#include "vector/vector2D.h"
#include "movement.h"
#include <math.h>
#include <stdio.h> 
#define PI 3.14159265
class NPC;


class Flee : public State <NPC> {
public:
	void Enter(NPC *npc);
	void Execute(NPC *npc);
	void Exit(NPC *npc);
	Movement *NPCs = new Movement();
};

class Default : public State < NPC > {
public:
	void Enter(NPC *npc);
	void Execute(NPC *npc);
	void Exit(NPC *npc);
	Movement *NPCs = new Movement();
};

typedef singleton<Flee> flee_state;
typedef singleton<Default> Default_state;

#endif