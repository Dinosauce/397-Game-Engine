#include "NPCStates.h"

#include <iostream>
#include "NPC.h"

using namespace std;

void Flee::Enter(NPC *npc){
	cout << "Enter global state" << endl;
}

void Flee::Execute(NPC *npc){
	distance = 0.0f;
	vector2D patroller(npc->getPosition().x, npc->getPosition().z);
	vector2D target(npc->GetTarget().getPosition().x, npc->GetTarget().getPosition().z);
	vector2D patrollerVel(0, 80);
	vector2D targetVel(10,10);


	npc->ShowAnimation(40, 46, 15);
	NPCs->flee(patroller, target, targetVel, 1,1);

	double z = patroller.getY() - target.getY();
	double x = patroller.getX() - target.getX();
	double angle = atan2(x, z) * 180 / PI;

	npc->setX(patroller.getX());
	npc->setZ(patroller.getY());
	npc->setRotation(angle-90);

	// lua
	lua_State *L;
	L = lua_open();
	luaL_openlibs(L);

	luaL_dofile(L, "AI_Lua.lua");
	lua_getglobal(L, "FleeExecuteUpdate");
	lua_call(L, 0, 2);
	distance = (float)lua_tonumber(L, 1);
	new_state_str = lua_tostring(L, 2);
	lua_pop(L, 2);
	lua_close(L);

	if (!NPCs->seeTarget(patroller, target, patrollerVel, distance, 360))
	{
		if (new_state_str == "Default_state")
			npc->changeState(&Default_state::Instance());
	}


	cout << "Execute global state" << endl;
}

void Flee::Exit(NPC *npc){
	cout << "Exit global state" << endl;
}

void Default::Enter(NPC *npc){
	cout << "Enter walk state" << endl;
}

void Default::Execute(NPC *npc){
	distance = 0.0f;

	 vector2D patroller(npc->getPosition().x, npc->getPosition().z);
	 vector2D target(npc->GetTarget().getPosition().x, npc->GetTarget().getPosition().z);
	vector2D patrollerVel(0, 80);

	npc->ShowAnimation(0, 30, 5);

	// lua
	lua_State *L;
	L = lua_open();
	luaL_openlibs(L);

	luaL_dofile(L, "AI_Lua.lua");
	lua_getglobal(L, "DefaultExecuteUpdate");
	lua_call(L, 0, 2);
	distance = (float)lua_tonumber(L, 1);
	new_state_str = lua_tostring(L, 2);
	lua_pop(L, 2);
	lua_close(L);

	if (NPCs->seeTarget(patroller, target, patrollerVel,distance,360))
	{
		if (new_state_str == "flee_state")
			npc->changeState(&flee_state::Instance());
	}

	//cout << "Execute walk state" << endl;
}

void Default::Exit(NPC *npc){
	cout << "Exit walk state" << endl;
}