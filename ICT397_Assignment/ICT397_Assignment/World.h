#ifndef WORLD_H
#define WORLD_H

#include "Graphics.h"
#include "Camera.h"
#include "Control.h"
#include "GameTime.h"
#include <iostream>

/**
* World class - Plentoon Games
* Stores all the game components and helps object communication
*/
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
		* but in glut, it will exit directly without deleting
		*/
		~World(){
			delete graphic_handler;
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
		static bool IsGameDone(){ return game_done; };

		/**
		* quit the game
		*/
		static void QuitGame(){ game_done = true; };

		/**
		* delete the game objects and class objects before exit the program
		*/
		static void GameDestruction();

		/**
		* initialize the components and game object rendering
		*/
		static void Initialize();

		/**
		* components update and game object animation
		*/
		static void Update();

		/**
		* set the graphics API to OpenGL
		* @return true if setup success, false otherwise
		*/
		static bool SetOpenGLGraphics();


	private:
		/// game status
		static bool game_done;

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
};

#endif