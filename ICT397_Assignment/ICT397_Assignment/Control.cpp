#include "Control.h"

Camera* Control::cam;
int Control::mouse_x_org = 0;
int Control::mouse_y_org = 1;
int Control::screen_width = 0;
int Control::screen_height = 0;

void Control::OpenGLKeyboardDownFunc(unsigned char key, int x, int y){
	

	switch (key){
		case 'w':
		case 'W':
			cam->MoveForward();
			break;

		case 's':
		case 'S':
			cam->MoveBackward();
			break;

		case 'a':
		case 'A':
			cam->MoveLeft();
			break;

		case 'd':
		case 'D':
			cam->MoveRight();
			break;

		case 27:
			exit(0);

		default:
			break;
	}

	glutPostRedisplay();
}

void Control::OpenGLKeyboardUpFunc(unsigned char key, int x, int y){
	switch (key){
	case 'w':
	case 'W':
	case 's':
	case 'S':
		cam->SetIsMovingFB(false);
		break;
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		cam->SetIsMovingLR(false);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void Control::OpenGLMouseMovementFunc(int x, int y){
	if (x != mouse_x_org || y != mouse_y_org){
		cam->SetCameraRotation(
			((float)x - ((float)screen_width/2)),
			((float)y - ((float)screen_height/2))
			);
		cam->SetIsRotating(true);
		glutWarpPointer(screen_width / 2, screen_height / 2);
	}
	else{
		cam->SetIsRotating(false);
	}

	mouse_x_org = x;
	mouse_y_org = y;

	glutPostRedisplay();
}