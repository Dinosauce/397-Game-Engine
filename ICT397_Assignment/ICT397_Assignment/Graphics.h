#include "GameObject.h"
#include <GL/glut.h>


class Graphics{
	public:
		Graphics(){};
		~Graphics(){};

		virtual void CreateNewWindow(int width, int height, char* window_name, int* argc, char* argv[]) = 0;
		virtual void DestroyWindow(int width, int height) = 0;

	protected:
		static int screen_width, screen_height;

	//virtual bool renderTriangleStrip(Vertices* v);
	//virtual bool renderModel(Model* m);
};



class OpenGL : public Graphics{
	void CreateNewWindow(int width, int height, char* window_name, int* argc, char* argv[]);
	void DestroyWindow(int width, int height);


	public: 


	private: 
		static GameObject DrawGrid;
		static void Initialize();
		static void Display();
		static void Reshape(int width, int height);
};



class DirectX : public Graphics{
	void CreateNewWindow(int width, int height, char* window_name, int* argc, char* argv[]){};
	void DestroyWindow(int width, int height){};
};

class GraphicsFactory{
	public:
		Graphics* Create(char* type);
};