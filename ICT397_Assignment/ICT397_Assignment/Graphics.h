#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GameObject.h"
#include "md2Files\md2Loader.h"
#include "Terrain.h"
#include <GL/glut.h>
#include <time.h>

class Graphics{
	public:
		Graphics(){};
		~Graphics(){};

		virtual void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]) = 0;
		virtual void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)) = 0;
		virtual void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)) = 0;

		//virtual void DrawModel(ObjectLoader model) = 0;
		//virtual void DrawTerrain(Terrain terrain) = 0;
		
	protected:
		static int screen_width, screen_height;

	//virtual bool renderTriangleStrip(Vertices* v);
	//virtual bool renderModel(Model* m);
};



class OpenGL : public Graphics{
	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]);
	
	//void DrawModel(ObjectLoader model);

	void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)){
		OpenGLKeyboardDownFunc = func;
	};

	void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)){
		OpenGLKeyboardUpFunc = func;
	};
	
	public: 
		static void DrawTerrain(Terrain terrain);

	private: 
		static void Initialize();
		//TODO: Make static again?
		static void Display();
		static void Reshape(int width, int height);
		static void IncrementFrameCount();


		static clock_t last_clock;
		static int frame_count;
		void(*OpenGLKeyboardDownFunc)(unsigned char, int, int);
		void(*OpenGLKeyboardUpFunc)(unsigned char, int, int);

		static GameObject ObjectGrids;
};



//class DirectX : public Graphics{
//	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]){};
//	void SetKeyboardDownFunc(void(*func)(unsigned char, int, int)){};
//	void SetKeyboardUpFunc(void(*func)(unsigned char, int, int)){};
//};

class GraphicsFactory{
	public:
		Graphics* Create(char* type);
};

#endif