#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glut.h>
#include "Camera.h"
#include "GameTime.h"
#include "Control.h"

class Graphics{
	public:
		Graphics(){};
		~Graphics(){};

		virtual void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]) = 0;
		virtual void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)) = 0;
		virtual void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)) = 0;

		void SetCameraPtr(Camera* new_cam_ptr){
			cam = new_cam_ptr;
		};

		void SetGameTimePtr(GameTime* new_game_time_ptr){
			game_time = new_game_time_ptr;
		}

	protected:
		static int screen_width, screen_height;
		static Camera* cam;
		static GameTime* game_time;

	//virtual bool renderTriangleStrip(Vertices* v);
	//virtual bool renderModel(Model* m);
};



class OpenGL : public Graphics{
	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]);
	
	void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)){
		OpenGLKeyboardDownFunc = func;
	};

	void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)){
		OpenGLKeyboardUpFunc = func;
	};
	
	public: 
		

	private: 
		static void Initialize();
		static void Display();
		static void Reshape(int width, int height);
		static void CallLookAt();

		void(*OpenGLKeyboardDownFunc)(unsigned char, int, int);
		void(*OpenGLKeyboardUpFunc)(unsigned char, int, int);
};



class DirectX : public Graphics{
	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]){};
	void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)){};
	void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)){};
};

class GraphicsFactory{
	public:
		Graphics* Create(char* type);
};

#endif