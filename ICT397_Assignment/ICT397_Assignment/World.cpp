#include "World.h"

int World::screen_width;
int World::screen_height;
int World::game_status;
GraphicsFactory World::graphics_factory;
Graphics* World::graphic_handler;
Camera World::cam;
Control World::control;
GameTime World::game_time;

double World::elapsed_time_second;
int World::fps;

World::World(){
	game_status = GAME_PLAYING;
	screen_width = 800;
	screen_height = 600;

	if (! SetOpenGLGraphics())	
		std::cout << "error set openGL graphics. " << std::endl;
	
	control.SetCameraPtr(&cam);
	control.SetScreenSize(screen_width, screen_height);
	control.SetGameStatusFunc(SetGameStatus, GetGameStatus);
	graphic_handler->SetWorldInitializeFunc(Initialize);
	graphic_handler->SetWorldUpdateFunc(Update);
	texture2d.SetScreenSize(screen_width, screen_height);
}

void World::Initialize(){
	
	texture2d.SetTextureCount(3);
	texture2d.LoadRawTexture2D("pictures/GameMenu.raw", 512, 512, GAME_MAIN_MENU_TEXTURE);
	//texture2d.LoadRawTexture2D("src", 10, 10, GAME_HELP_MENU_TEXTURE);
	texture2d.LoadRawTexture2D("pictures/Credit.raw", 512, 512, CREDIT_TEXTURE);
	
}

void World::Update(){
	elapsed_time_second = game_time.GetElapsedTimeSecond();
	fps = game_time.GetFps();
	cam.SetCameraSpdWithDT(elapsed_time_second);
	cam.CheckCamera();
	graphic_handler->SetCameraPos(cam.GetCameraPos());
	graphic_handler->SetCameraLookAt(cam.GetCameraLookAt());

	if (GetGameStatus() != GAME_PLAYING){
		if (GetGameStatus() == GAME_DONE){
			GameDestruction();
			exit(0);
		}

		if (GetGameStatus() == GAME_MAIN_MENU){
			texture2d.Display2DTexture(512, 512, 0, 0, GAME_MAIN_MENU_TEXTURE);
		}

		if (GetGameStatus() == GAME_HELP_MENU){
			texture2d.Display2DTexture(512, 512, 0, 0, GAME_HELP_MENU_TEXTURE);
		}

		if (GetGameStatus() == GAME_CREDIT_PAGE){
			texture2d.Display2DTexture(512, 512, 0, 0, CREDIT_TEXTURE);
		}
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
	texture2d.Clear();
}

bool World::SetOpenGLGraphics(){
	graphic_handler = graphics_factory.Create("OpenGL");
	if (graphic_handler == 0){
		return false;
	}
	return true;
}