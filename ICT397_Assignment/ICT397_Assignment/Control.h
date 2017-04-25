#ifndef CONTROL_H
#define CONTROL_H

#include <GL\glut.h>
#include <stdlib.h>
#include "Camera.h"

class Control{
	public:
		Control(){};
		~Control(){};

		static void SetCameraPtr(Camera* new_cam_ptr){
			cam = new_cam_ptr;
		};


		static void OpenGLKeyboardDownFunc(unsigned char key, int x, int y);
		static void OpenGLKeyboardUpFunc(unsigned char key, int x, int y);

	private:
		static Camera* cam;
};

#endif