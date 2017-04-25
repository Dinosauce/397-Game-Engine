#include "Control.h"

Camera* Control::cam;

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
}