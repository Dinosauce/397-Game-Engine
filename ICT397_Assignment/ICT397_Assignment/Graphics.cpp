#include "Graphics.h"
#include <string>

int Graphics::screen_width;
int Graphics::screen_height;
void(*Graphics::WorldInitialize)();
void(*Graphics::WorldUpdate)();
Vector3 Graphics::camera_pos;
Vector3 Graphics::camera_look_at;

void(*OpenGL::OpenGLKeyboardDownFunc)(unsigned char, int, int);
void(*OpenGL::OpenGLKeyboardUpFunc)(unsigned char, int, int);
void(*OpenGL::OpenGLPassiveMouseFunc)(int, int);

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
	glutWarpPointer(width / 2, height / 2);
	glutPassiveMotionFunc(OpenGLPassiveMouseFunc);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

void OpenGL::Initialize(){
	// set background (sky colour)
	glClearColor(97.0 / 255.0, 140.0 / 255.0, 185.0 / 255.0, 1.0);

	WorldInitialize();
}

void OpenGL::Display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	elapsed_time_second = game_time->GetElapsedTimeSecond();
	fps = game_time->GetFps();
	cam->SetCameraSpdWithDT(elapsed_time_second);
	cam->CheckCamera();
	*/

	WorldUpdate();
	CallLookAt();
	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3i(0, 0, 10);
		glVertex3i(10, 0, 10);
		glVertex3i(10, 10, 10);
		glVertex3i(0, 10, 10);
	glEnd();

	//glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OpenGL::Reshape(int width, int height){
	double ratio;

	screen_width = width;
	screen_height = height;

	// prevent divide by zero
	if (screen_height == 0) screen_height = 1;
	ratio = 1.0 * screen_width / screen_height;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, screen_width, screen_height);
	gluPerspective(45.0, ratio, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGL::CallLookAt(){
	glLoadIdentity();
	gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z,
		camera_look_at.x, camera_look_at.y, camera_look_at.z,
		0, 1, 0);
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