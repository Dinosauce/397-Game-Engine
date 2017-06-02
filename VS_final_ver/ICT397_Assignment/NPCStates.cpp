#include "NPCStates.h"

#include <iostream>
#include "NPC.h"

using namespace std;

void Flee::Enter(NPC *npc){
	cout << "Enter global state" << endl;
}

void Flee::Execute(NPC *npc){
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

	if (!NPCs->seeTarget(patroller, target, patrollerVel, 50, 360))
	{
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
	 vector2D patroller(npc->getPosition().x, npc->getPosition().z);
	 vector2D target(npc->GetTarget().getPosition().x, npc->GetTarget().getPosition().z);
	vector2D patrollerVel(0, 80);

	npc->ShowAnimation(0, 30, 5);

	if (NPCs->seeTarget(patroller, target, patrollerVel,50,360))
	{
		npc->changeState(&flee_state::Instance());
	}

	//cout << "Execute walk state" << endl;
}

void Default::Exit(NPC *npc){
	cout << "Exit walk state" << endl;
}