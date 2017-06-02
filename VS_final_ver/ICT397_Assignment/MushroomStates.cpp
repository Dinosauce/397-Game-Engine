#include "MushroomStates.h"
#include <iostream>

void Global::Enter(GameObject *thing){
	std::cout << "Enter global state" << std::endl;
}

void Global::Execute(GameObject *thing){
	std::cout << "Execute global state" << std::endl;
}

void Global::Exit(GameObject *thing){
	std::cout << "Exit global state" << std::endl;
}

void Walk::Enter(GameObject *thing){
	std::cout << "Enter walk state" << std::endl;
}

void Walk::Execute(GameObject *thing){
	std::cout << "Execute walk state" << std::endl;
}

void Walk::Exit(GameObject *thing){
	std::cout << "Exit walk state" << std::endl;
}