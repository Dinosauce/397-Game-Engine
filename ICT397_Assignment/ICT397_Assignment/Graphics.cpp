#include "Graphics.h"
#include <string>

int Graphics::screen_width;
int Graphics::screen_height;
clock_t OpenGL::last_clock = 0;
int OpenGL::frame_count = 0;


//TODO: TESTING OBJECT REMOVE
GameObject OpenGL::ObjectGrids;
md2Loader model;

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
	

	//ObjectGrids.LoadGameObject("3Dmodels/terrain/grid.obj");
	model.loadModel("md2Files/testmodel/tris.MD2", "md2Files/testmodel/skin.pcx");

}

void OpenGL::Display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(-150, 100, 50,
		0, 40, -20,
		0, 1, 0);

	IncrementFrameCount();

	//ObjectGrids.ShowGameObject();
	model.render();

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

void OpenGL::DrawTerrain(Terrain terrain)
{
	unsigned char hcolor = 255;
	unsigned char hcolor2 = 255; //color of the height

	bool texturesEnabled = false;
	int size = terrain.getSize();
	float scaleX = terrain.getScaleX();
	float scaleY = terrain.getScaleY();
	float scaleZ = terrain.getScaleZ();

	float tLeft = 0.0f;
	float tBottom = 0.0f;
	float tTop = 0.0f;
	
	if (texturesEnabled)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (GLuint)terrain.getTexID());
		//cout << "Textures Enabled" << endl;
	}

	//loop through the z axis
	for (int z = 0; z<size - 2; z++) {
		//loop through the x axis
		glBegin(GL_TRIANGLE_STRIP);

		for (int x = 0; x<size - 1; x++) {
			if (texturesEnabled)
			{
				tLeft = (float)x / (float)size;
				tBottom = (float)z / (float)size;
				tTop = (float)(z + 1) / (float)size;
			}
			else
			{
				hcolor = terrain.getHeightColor(x, z);
				hcolor2 = terrain.getHeightColor(x, z + 1);
			}

			//create the the first point in the triangle strip
			glColor3ub(hcolor, hcolor, hcolor);
			glTexCoord2f(tLeft, tBottom);
			glVertex3f((float)x*scaleX, (float)terrain.getPointHeight(x, z)*scaleY, (float)z*scaleZ);

			//create the next point in the triangle strip
			glColor3ub(hcolor, hcolor, hcolor);
			glTexCoord2f(tLeft, tTop);
			glVertex3f((float)x*scaleX, (float)terrain.getPointHeight(x, z + 1)*scaleY, (z + 1)*scaleZ);
		}
		glEnd();
	}
}

Graphics* GraphicsFactory::Create(char* type){
	std::string type_str = type;
	if (type_str == "OpenGL"){
		return new OpenGL;
	}
	//else if(type_str == "DirectX"){
	//	return new DirectX;
	//}
	else{
		return NULL;
	}
}
