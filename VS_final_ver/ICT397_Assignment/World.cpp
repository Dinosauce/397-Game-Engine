#include "World.h"

int World::screen_width;
int World::screen_height;
int World::game_status;
GraphicsFactory World::graphics_factory;
Graphics* World::graphic_handler;
Camera World::cam;
Control World::control;
GameTime World::game_time;
ParticleEmmitter World::particleSystem;
LuaData World::LD;
//terrain World::Terrain;
map<string,terrain> World::Terrains;
double World::elapsed_time_second;
int World::fps;

//Draw Terrain Model

bool World::RandomGrids[10][10];

//Draw NPCs Model
GameObject World::NPCs;
bool World::RandomNPCs[10][10];

//Draw Trees Model
GameObject World::Trees;
bool World::RandomTrees[10][10];

void World::LoadLuaFiles()
{
	lua_State *gameFile = lua_open();

	luaL_openlibs(gameFile);
	luaL_loadfile(gameFile, "GameFiles.lua");
	lua_pcall(gameFile, 0, 0, 0);
	lua_getglobal(gameFile, "terrainFile");
	lua_getglobal(gameFile, "objectFile");
	lua_getglobal(gameFile, "npcFile");

	LD.TerrainFile = lua_tostring(gameFile, -3);
	LD.NPCsFile = lua_tostring(gameFile, -2);
	LD.ObjectsFile = lua_tostring(gameFile, -1);

	cout << LD.TerrainFile << endl;
	cout << LD.ObjectsFile << endl;
	cout << LD.NPCsFile << endl;
	lua_close(gameFile);

}

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
	//Load extra lua files
	LoadLuaFiles();

	//Initial Terrian Model
	InitialTerrain();


	texture2d.SetTextureCount(3);
	texture2d.LoadRawTexture2D("pictures/GameMenu.raw", 512, 512, GAME_MAIN_MENU_TEXTURE);
	texture2d.LoadRawTexture2D("pictures/HelpMenu.raw", 512, 512, GAME_HELP_MENU_TEXTURE);
	texture2d.LoadRawTexture2D("pictures/Credit.raw", 512, 512, CREDIT_TEXTURE);

	// init the special effects
	InitSpecialEffects();


	//Initial NPCs Model
	//InitialNPCs();

	//Initial NPCs Model
	//InitialTrees();

}

void World::InitSpecialEffects(){
	particleSystem.createParticles(0, 200, 0);
}

void World::Update(){

	elapsed_time_second = game_time.GetElapsedTimeSecond();
	fps = game_time.GetFps();
	cam.SetCameraSpdWithDT(elapsed_time_second);
	cam.CheckCamera();
	graphic_handler->SetCameraPos(cam.GetCameraPos());
	graphic_handler->SetCameraLookAt(cam.GetCameraLookAt());


	//Draw Terrain Model
	DrawTerrain();
	DrawSpecialEffects();

	//Draw NPCs Models
	//DrawNPCs();
	
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

void World::DrawSpecialEffects(){
	particleSystem.updateParticles();
	particleSystem.DrawParticles(&particleSystem);
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

void World::InitialTerrain()
{
	terrain *Terrain=new terrain();

	Terrain->loadHeightfield(LD.TerrainFile.c_str(), 128);
	Terrain->setScalingFactor(7, 1, 7);
	Terrain->generateHeightfield(128, 0.3, 150);
	Terrain->addProceduralTexture("pictures/lowestTile.tga");
	Terrain->addProceduralTexture("pictures/lowTile.tga");
	Terrain->addProceduralTexture("pictures/highTile.tga");
	Terrain->addProceduralTexture("pictures/highestTile.tga");
	Terrain->createProceduralTexture();
	Terrain->setNumTerrainTexRepeat(1);
	Terrain->DoTextureMapping(true);
	Terrain->loadDetailMap("pictures/detailMap.tga");
	Terrain->setNumDetailMapRepeat(8);
	Terrain->DoDetailMapping(true);
	Terrain->LoadLightMap("pictures/lightmap.raw", 128);
	Terrain->DoLightMapping(true);

	Terrains["T1"] = *Terrain;



	terrain *Terrain2 = new terrain();

	Terrain2->loadHeightfield(LD.TerrainFile.c_str(), 128);
	Terrain2->setScalingFactor(3, 0.5, 3);
	Terrain2->generateHeightfield(128, 0.3, 150);
	Terrain2->addProceduralTexture("pictures/lowestTile.tga");
	Terrain2->addProceduralTexture("pictures/lowTile.tga");
	Terrain2->addProceduralTexture("pictures/highTile.tga");
	Terrain2->addProceduralTexture("pictures/highestTile.tga");
	Terrain2->createProceduralTexture();
	Terrain2->setNumTerrainTexRepeat(1);
	Terrain2->DoTextureMapping(true);
	Terrain2->loadDetailMap("pictures/detailMap.tga");
	Terrain2->setNumDetailMapRepeat(8);
	Terrain2->DoDetailMapping(true);
	Terrain2->LoadLightMap("pictures/lightmap.raw", 128);
	Terrain2->DoLightMapping(true);

	Terrains["T2"] = *Terrain2;

}

void World::DrawTerrain()
{
	Terrains["T1"].render();
	Terrains["T2"].render();
	//terrain t1 = Terrains["T1"];
	int CamX = cam.GetCameraPos().x;

	int CamZ = cam.GetCameraPos().z;
	int CamY=Terrains["T1"].getAverageHight(CamX, CamZ);
	cam.isTerrainCollision(CamY+10);
}

void World::InitialNPCs()
{
	NPCs.LoadGameObject(LD.NPCsFile.c_str(), "NPC");

	for (int i = 0; i < 10; i++)
	{
		int randNum1 = (rand() % 10) + 0;
		int randNum2 = (rand() % 10) + 0;

		for (int j = 0; j < 10; j++)
		{
			std::vector<bool> colVector;

			if ((j == randNum1) || (j == randNum2))
			{
				RandomNPCs[i][j] = false;
			}
			else
			{
				RandomNPCs[i][j] = true;
			}
		}
	}
}

void World::DrawNPCs()
{
	NPCs.ShowGameObject();
}

void World::InitialTrees()
{
	Trees.LoadGameObject(LD.ObjectsFile.c_str(), "Objects");

	for (int i = 0; i < 10; i++)
	{
		int randNum1 = (rand() % 10) + 0;
		int randNum2 = (rand() % 10) + 0;

		for (int j = 0; j < 10; j++)
		{
			std::vector<bool> colVector;

			if ((j == randNum1) || (j == randNum2))
			{
				RandomTrees[i][j] = false;
			}
			else
			{
				RandomTrees[i][j] = true;
			}
		}
	}
}

void World::DrawTrees()
{
	Trees.ShowGameObject();
}