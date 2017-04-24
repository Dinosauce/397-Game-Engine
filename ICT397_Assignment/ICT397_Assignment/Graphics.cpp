#include "Graphics.h"
#include <string>

int Graphics::screen_width;
int Graphics::screen_height;
GameObject OpenGL::DrawGrid;

void OpenGL::CreateNewWindow(int width, int height, char* window_name, int* argc, char* argv[]){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	screen_width = width;
	screen_height = height;
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow(window_name);

	Initialize();

	glutDisplayFunc(Display);

	glutReshapeFunc(Reshape);

	glutMainLoop();
}

void OpenGL::DestroyWindow(int width, int height){

}

void OpenGL::Initialize(){
	// set background (sky colour)
	glClearColor(97.0 / 255.0, 140.0 / 255.0, 185.0 / 255.0, 1.0);
	DrawGrid.LoadGameObject("3Dmodels/grid.obj");
}

void OpenGL::Display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawGrid.ShowGameObject();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OpenGL::Reshape(int width, int height){
	float ratio;

	screen_width = width;
	screen_height = height;

	// prevent divide by zero
	if (screen_height == 0) screen_height = 1;
	ratio = 1.0f * screen_width / screen_height;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, screen_width, screen_height);
	gluPerspective(45.0, ratio, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}



Graphics* GraphicsFactory::Create(char* type){
	std::string type_str = type;
	if (type_str == "OpenGL"){
		return new OpenGL;
	}
	else if(type_str == "DirectX"){
		return new DirectX;
	}
	else{
		return NULL;
	}
}