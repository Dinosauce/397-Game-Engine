#ifndef WORLD_H
#define WORLD_H

#include "Graphics.h"
#include "Camera.h"
#include "Control.h"
#include "GameTime.h"
#include "Texture.h"
#include "GameStatus.h"
#include "TextureMap.h"
#include <iostream>
#include "GameObject.h"
#include "ParticleEmmitter.h"
#include <cstdlib>
#include <vector>
#include <map>
#include "lua/lua.hpp"
#include "Terrain.h"
#include "LuaScript.h"
#include "SkyBox.h"
#include "water.h"
#include "UserInterface.h"
#include "Player.h"
#include "NPC.h"

/**
* World class - Plentoon Games
* Stores all the game components and helps object communication
*/
struct  LuaData
{
	string TerrainFile;
	string ObjectsFile;
	string NPCsFile;
};
struct terrainData
{
	string TerrainFile;
	int ImageSize, scalex, scaley, scalez;
	int iterations, hSize, minHeight, maxHeight;
	float weight;
	bool random;
	string ProceduralTexture1, ProceduralTexture2, ProceduralTexture3, ProceduralTexture4;
	int repeat;
	bool textureMapping;
	string DetailMap;
	int mapRepeat;
	bool DetailMapping;
	string LightMap;
	int LightMapSize;
	bool LightMapping;
};

class World{
	public:
		//Terrain *terrain;
		//Player *player;
		//Audio *worldSound;
		//GUI *gui;
		//Levels *levels;
		//Enemy *enemy;

		/**
		* Ctor
		* default screen size 800x600
		* setup the graphics API
		* setup the object communication and function pointers
		*/
		World();

		/**
		* Destructor
		* but in glut, it will exit through QuitGame
		*/
		~World(){
			delete graphic_handler;
			texture2d.Clear();
		};

		/**
		* create the game window and start running the game
		* @param argument from main()
		*/
		static void RunGame(int* argc, char* argv[]);

		/**
		* return the game status
		* @return game status
		*/
		static int GetGameStatus(){ return game_status; };

		/**
		* Set game status
		*/
		static void SetGameStatus(const int & new_status){ game_status = new_status; };

		/**
		* delete the game objects and class objects before exit the program
		*/
		static void GameDestruction();

		/**
		* initialize the components and game object rendering
		*/
		static void Initialize();

		/**
		* initialize all the special effects - particle etc.
		*/
		static void InitSpecialEffects();

		/**
		* components update and game object animation
		*/
		static void Update();

		/**
		* draw the special effects in update
		*/
		static void DrawSpecialEffects();
		

		/**
		* set the graphics API to OpenGL
		* @return true if setup success, false otherwise
		*/
		static bool SetOpenGLGraphics();

		/**
		* Initial Terrain Model
		*/
		static void InitialTerrain();
		/**
		* Draw Terrain Model
		*/
		static void DrawTerrain();

		/**
		* Initial Terrain Model
		*/
		static void InitialNPCs();
		/**
		* Draw Terrain Model
		*/
		static void DrawNPCs();

		/**
		* Initial Terrain Model
		*/
		static void InitialTrees();

		/**
		* Draw Terrain Model
		*/
		static void DrawTrees();

		/**
		* Load lua files
		*/
		static void LoadLuaFiles();

		static void InitialSkyBox();

		static void DrawSkyBox();

		static void InitialWater();

		static void DrawWater();

		static void DrawUI();

		static void InitCamera(double x, double z);

		static void SetTerrainBoundray();

		static void Initplayer();

		static void DrawPlayer();

	private:
		/// game status
		static int game_status;

		/// size of game window
		static int screen_width, screen_height; 

		/// update rate for the game loop
		static double elapsed_time_second;

		/// frame per second
		static int fps;

		/// graphic factory sends the graphic API out to handler
		static GraphicsFactory graphics_factory;

		/// graphic API handler
		static Graphics* graphic_handler;

		/// camera object
		static Camera cam;

		/// control object
		static Control control;

		/// game time object
		static GameTime game_time;

		/// particles
		static ParticleEmmitter particleSystem;

		/// texture object
		static Texture2D texture2d;

		static bool RandomGrids[10][10];

		static bool RandomNPCs[10][10];

		static bool RandomTrees[10][10];

		static LuaData LD;

		static terrainData terrainInfo;

		//static terrain Terrain;

		static map<string,terrain> Terrains;

		static map<string, GameObject> Trees;

		static map<string, Player> Players;

		static map<string, NPC> NPCs;

		static double CurrentX;

		static double CurrentZ;

		static SkyBox Sky;

		static water WaterObj;

		static UserInterface ui;

		static double t;

		static bool IsDead;

};

#endif