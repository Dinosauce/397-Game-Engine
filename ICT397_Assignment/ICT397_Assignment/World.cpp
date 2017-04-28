#include "World.h"

int World::screen_width;
int World::screen_height;
bool World::game_done;
GraphicsFactory World::graphics_factory;
Graphics* World::graphic_handler;
Camera World::cam;
Control World::control;
GameTime World::game_time;

double World::elapsed_time_second;
int World::fps;

World::World(){
	game_done = false;
	screen_width = 800;
	screen_height = 600;

	if (! SetOpenGLGraphics())
		std::cout << "error set openGL graphics. " << std::endl;
	
	control.SetCameraPtr(&cam);
	control.SetScreenSize(screen_width, screen_height);
	control.SetQuitGameFunc(QuitGame);
	graphic_handler->SetWorldInitializeFunc(Initialize);
	graphic_handler->SetWorldUpdateFunc(Update);
	texture2d.SetScreenSize(screen_width, screen_height);

	std::cout << GAME_DONE << std::endl;
}

void World::Initialize(){
	/*
	texture2d.SetTextureCount(2);
	texture2d.LoadRawTexture2D("src", 10, 10, GAME_MAIN_MENU_TEXTURE);
	texture2d.LoadRawTexture2D("src", 10, 10, GAME_HELP_MENU_TEXTURE);
	texture2d.LoadRawTexture2D("src", 10, 10, CREDIT_TEXTURE);
	*/
}

void World::Update(){
	elapsed_time_second = game_time.GetElapsedTimeSecond();
	fps = game_time.GetFps();
	cam.SetCameraSpdWithDT(elapsed_time_second);
	cam.CheckCamera();
	graphic_handler->SetCameraPos(cam.GetCameraPos());
	graphic_handler->SetCameraLookAt(cam.GetCameraLookAt());

	if (IsGameDone()){
		GameDestruction();
		exit(0);
	}
}

void World::RunGame(int* argc, char* argv[]){
	graphic_handler->SetKeyboardDownFunc(Control::OpenGLKeyboardDownFunc);
	graphic_handler->SetKeyboardUpFunc(Control::OpenGLKeyboardUpFunc);
	graphic_handler->SetPassiveMouseFunc(Control::OpenGLMouseMovementFunc);
	graphic_handler->CreateGameWindow(screen_width, screen_height, "Grid Grunt", argc, argv);
}

void World::GameDestruction(){
	delete graphic_handler;
}

bool World::SetOpenGLGraphics(){
	graphic_handler = graphics_factory.Create("OpenGL");
	if (graphic_handler == 0){
		return false;
	}
	return true;
}