#include "World.h"

World::World(){
	game_done = false;
	screen_width = 800;
	screen_height = 600;

	if (! SetOpenGLGraphics())
		std::cout << "error set openGL graphics. " << std::endl;
	
}

void World::RunGame(int* argc, char* argv[]){
	graphic_handler->SetKeyboardFunc(Control::OpenGLKeyboardFunc);
	graphic_handler->CreateGameWindow(screen_width, screen_height, "Grid Grunt", argc, argv);
}

bool World::SetOpenGLGraphics(){
	graphic_handler = graphics_factory.Create("OpenGL");
	if (graphic_handler == 0){
		return false;
	}
	return true;
}