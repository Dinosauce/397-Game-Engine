#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glut.h>

class Graphics{
	public:
		Graphics(){};
		~Graphics(){};

		virtual void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]) = 0;
		virtual void SetKeyboardFunc(void(*func)(unsigned char, int, int)) = 0;
		
	protected:
		static int screen_width, screen_height;
		void(*OpenGLKeyboardFunc)(unsigned char, int, int);

	//virtual bool renderTriangleStrip(Vertices* v);
	//virtual bool renderModel(Model* m);
};



class OpenGL : public Graphics{
	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]);
	
	void SetKeyboardFunc(void(*func)(unsigned char, int, int)){
		OpenGLKeyboardFunc = func;
	};
	
	public: 
		

	private: 
		static void Initialize();
		static void Display();
		static void Reshape(int width, int height);
};



class DirectX : public Graphics{
	void CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]){};
	void SetKeyboardFunc(void(*func)(unsigned char, int, int)){};
};

class GraphicsFactory{
	public:
		Graphics* Create(char* type);
};

#endif