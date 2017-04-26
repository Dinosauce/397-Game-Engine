#include "Graphics.h"
#include <string>

int Graphics::screen_width;
int Graphics::screen_height;
clock_t OpenGL::last_clock = 0;
int OpenGL::frame_count = 0;
GameObject OpenGL::ObjectGrids;

void OpenGL::CreateGameWindow(int width, int height, char* window_name, int* argc, char* argv[]){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	screen_width = width;
	screen_height = height;
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow(window_name);

	Initialize();

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(OpenGLKeyboardDownFunc);
	glutKeyboardUpFunc(OpenGLKeyboardUpFunc);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

void OpenGL::Initialize(){
	// set background (sky colour)
	glClearColor(97.0 / 255.0, 140.0 / 255.0, 185.0 / 255.0, 1.0);
	glewInit();
	

	ObjectGrids.LoadGameObject("3Dmodels/grid.obj");

}

void OpenGL::Display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(-150, 100, 50,
		0, 40, -20,
		0, 1, 0);

	IncrementFrameCount();

	ObjectGrids.ShowGameObject();

	//glFlush();
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
	gluPerspective(90.0, ratio, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGL::IncrementFrameCount(){
	double t = ((GLdouble)(clock() - last_clock)) / (GLdouble)CLOCKS_PER_SEC;
	frame_count++;

	//reset after t
	if (t > 0.1){
		frame_count = 0;
		last_clock = clock();
	}
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