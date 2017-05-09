#include <iostream>
#include "World.h"

/**
* main entry of the program
* create a World object and run the game
*/
int main(int argc, char* argv[]){
	World game_world;
	game_world.RunGame(&argc, argv);
	
	return 0;
}
