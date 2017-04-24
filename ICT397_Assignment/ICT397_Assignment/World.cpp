#include "World.h"

World::World(){
	game_done = false;
	screen_width = 800;
	screen_height = 600;

	SetOpenGLGraphics();
}

void World::RunGame(int* argc, char* argv[]){
	graphic_handler->CreateNewWindow(screen_width, screen_height, "Grid Grunt", argc, argv);
}

bool World::SetOpenGLGraphics(){
	graphic_handler = graphics_factory.Create("OpenGL");
	if (graphic_handler == 0){
		return false;
	}

	return true;
}
