#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glut.h>
#include "GameMathHelp.h"

/**
* Graphic class - Plentoon Games
* Base class for graphics API
*/
class Graphics{
	public:
		/**
		* Ctor
		*/
		Graphics(){};

		/**
		* virtual method - to create a game window and loop the components
		* @param width and height of the screen
		* @param name of the window shown in the window bar
		* @param arguments from main()
		*/
		virtual void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]) = 0;
		
		/**
		* virtual method - to set the openGL keyboard down function
		* @param keyboard down function
		*/
		virtual void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)) = 0;
		
		/**
		* virtual method - to set the openGL keyboard up function
		* @param keyboard up function
		*/
		virtual void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)) = 0;
		
		/**
		* virtual method - to set the openGL mouse passive function
		* @param mouse passive function
		*/
		virtual void SetPassiveMouseFunc(void(*func)(int, int)) = 0;

		/**
		* Set methods for the private variables
		* @param new value
		*/

		void SetCameraPos(const Vector3 & new_pos){
			camera_pos = new_pos;
		}

		void SetCameraLookAt(const Vector3 & new_look_at){
			camera_look_at = new_look_at;
		}

		void SetWorldInitializeFunc(void(*func)()){
			WorldInitialize = func;
		}

		void SetWorldUpdateFunc(void(*func)()){
			WorldUpdate = func;
		}

	protected:
		/// size of the game window
		static int screen_width, screen_height;

		/// camera position for glutlookat function
		static Vector3 camera_pos;

		/// position that the camera is looking at for glutlookat function
		static Vector3 camera_look_at;

		/// function pointer for initializing the world
		static void(*WorldInitialize)();

		/// function pointer for world updates
		static void(*WorldUpdate)();
};


/**
* OpenGL class - Plentoon Games
* Graphics API OpenGL using glut - inheritance from Graphics
*/
class OpenGL : public Graphics{
	/**
	* virtual method - to create a game window and loop the components
	* @param width and height of the screen
	* @param name of the window shown in the window bar
	* @param arguments from main()
	*/
	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]);
	
	/**
	* Set methods for private variables and function pointers
	* @param new value
	*/
	void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)){
		OpenGLKeyboardDownFunc = func;
	};

	void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)){
		OpenGLKeyboardUpFunc = func;
	};

	void SetPassiveMouseFunc(void(*func)(int, int)){
		OpenGLPassiveMouseFunc = func;
	};
	
	public: 
		

	private: 
		/**
		* the main initialize function - setup the glut settings
		*/
		static void Initialize();

		/**
		* the main display function - draw all the things and display them
		*/
		static void Display();

		/**
		* reshape function that keeps the components work same in resizing the screen
		*/
		static void Reshape(int width, int height);

		/**
		* call the glut look at function to update the camera
		*/
		static void CallLookAt();

		/// function pointer for keyboard down function
		static void(*OpenGLKeyboardDownFunc)(unsigned char, int, int);
		
		/// function pointer for keyboard up function
		static void(*OpenGLKeyboardUpFunc)(unsigned char, int, int);

		/// function pointer for mouse passive function
		static void(*OpenGLPassiveMouseFunc)(int, int);
};


/**
* DirectX class - Plentoon Games
* Graphics API DirectX - inheritance from Graphics
* Not yet developed
*/
class DirectX : public Graphics{
	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]){};
	void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)){};
	void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)){};
	void SetPassiveMouseFunc(void(*func)(int, int)){};
};


/**
* GraphicsFactory class - Plentoon Games
* Mainly for outputting the child graphic API
*/
class GraphicsFactory{
	public:
		/**
		* return the graphic API
		* @param the name of the graphic API
		* @return the child graphic API object
		*/
		Graphics* Create(char* type);
};

#endif