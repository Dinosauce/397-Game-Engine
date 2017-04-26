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

		static void SetScreenSize(int const & width, int const & height){
			screen_width = width;
			screen_height = height;
		}

		static void OpenGLKeyboardDownFunc(unsigned char key, int x, int y);
		static void OpenGLKeyboardUpFunc(unsigned char key, int x, int y);
		static void OpenGLMouseMovementFunc(int x, int y);

	private:
		static Camera* cam;
		static int mouse_x_org, mouse_y_org;
		static int screen_width, screen_height;
};

#endif