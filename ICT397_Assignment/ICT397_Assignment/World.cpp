#include "World.h"

World::World(){
	game_done = false;
	screen_width = 800;
	screen_height = 600;

	if (! SetOpenGLGraphics())
		std::cout << "error set openGL graphics. " << std::endl;
	
	control.SetCameraPtr(&cam);
	control.SetScreenSize(screen_width, screen_height);
	graphic_handler->SetCameraPtr(&cam);
	graphic_handler->SetGameTimePtr(&game_time);
	
}

void World::RunGame(int* argc, char* argv[]){
	graphic_handler->SetKeyboardDownFunc(Control::OpenGLKeyboardDownFunc);
	graphic_handler->SetKeyboardUpFunc(Control::OpenGLKeyboardUpFunc);
	graphic_handler->SetPassiveMouseFunc(Control::OpenGLMouseMovementFunc);
	graphic_handler->CreateGameWindow(screen_width, screen_height, "Grid Grunt", argc, argv);
}

bool World::SetOpenGLGraphics(){
	graphic_handler = graphics_factory.Create("OpenGL");
	if (graphic_handler == 0){
		return false;
	}
	return true;
}