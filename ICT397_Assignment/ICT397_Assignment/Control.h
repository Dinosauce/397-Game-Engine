#ifndef CONTROL_H
#define CONTROL_H

#include <GL\glut.h>
#include <stdlib.h>
#include "Camera.h"

class Control{
	public:
		Control(){};
		~Control(){};

		static void OpenGLKeyboardFunc(unsigned char key, int x, int y);

	private:
		Camera* cam;
};

#endif