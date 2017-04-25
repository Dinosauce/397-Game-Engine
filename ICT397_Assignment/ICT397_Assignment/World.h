#ifndef WORLD_H
#define WORLD_H

#include "Graphics.h"
#include "Camera.h"
#include "Control.h"
#include "GameTime.h"
#include <iostream>

class World{
	public:
		//Terrain *terrain;
		//Camera *camera
		//Player *player;
		//Audio *worldSound;
		//GUI *gui;
		//Levels *levels;
		//Enemy *enemy;


		World();
		//World(Camera *c);
		~World(){
			delete graphic_handler;
		};

		// game
		void RunGame(int* argc, char* argv[]);
		bool IsGameDone(){ return game_done; };
		void QuitGame(){ game_done = true; };

		// graphics
		bool SetOpenGLGraphics();

		// initialize terrai, load objects and put in container
		void LoadWorld();
		void UnloadWorld();



	private:
		bool game_done;
		int screen_width, screen_height;

		// graphics
		GraphicsFactory graphics_factory;
		Graphics* graphic_handler;

		// camera
		Camera cam;

		// control
		Control control;

		// game time
		GameTime game_time;
};

#endif