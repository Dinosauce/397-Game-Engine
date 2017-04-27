#ifndef CONTROL_H
#define CONTROL_H

#include <GL\glut.h>
#include <stdlib.h>
#include "Camera.h"

/**
* Control class - Plentoon Games
* Read user input and make changes in the game world
* Can be separated as different input devices by inheritance, in the future development
*/
class Control{
	public:
		/**
		* Ctor
		*/
		Control(){};

		/**
		* Set Method of private variables
		* @param new value
		*/

		static void SetCameraPtr(Camera* new_cam_ptr){
			cam = new_cam_ptr;
		};

		static void SetScreenSize(int const & width, int const & height){
			screen_width = width;
			screen_height = height;
		}

		static void SetQuitGameFunc(void(*func)()){
			QuitGame = func;
		}

		/**
		* Get Method of private variables
		* @return value of the variables
		*/

		static Camera* GetCameraPtr(){ return cam; };
		

		/// Keyboard Down function for openGL
		/// For activating the camera movement wasd
		static void OpenGLKeyboardDownFunc(unsigned char key, int x, int y);

		/// Keyboard Up function for openGL
		/// For deactivating the camera movement wasd
		static void OpenGLKeyboardUpFunc(unsigned char key, int x, int y);

		/// Mouse Passive Movement function for openGL
		/// For controlling the camera rotation
		static void OpenGLMouseMovementFunc(int x, int y);

	private:
		/// pointer to the camera object from World
		static Camera* cam;

		/// records previous mouse location on the game window
		static int mouse_x_org, mouse_y_org;

		/// screen width and height of the current game window
		static int screen_width, screen_height;

		/// Quit game function pointer from World class
		static void(*QuitGame)();
};

#endif