#include "Control.h"

Camera* Control::cam;
int Control::mouse_x_org = 0;
int Control::mouse_y_org = 1;
int Control::screen_width = 0;
int Control::screen_height = 0;
int(*Control::GetGameStatus)();
void(*Control::SetGameStatus)(const int &);
char Control::key_pressed;

void Control::OpenGLKeyboardDownFunc(unsigned char key, int x, int y){
	if (GetGameStatus() == GAME_PLAYING){
		switch (key){
			case 'w':
			case 'W':
				cam->MoveForward();
				key_pressed = 'w';
				break;

			case 's':
			case 'S':
				cam->MoveBackward();
				key_pressed = 's';
				break;

			case 'a':
			case 'A':
				cam->MoveLeft();
				key_pressed = 'a';
				break;

			case 'd':
			case 'D':
				cam->MoveRight();
				key_pressed = 'd';
				break;

			case 'k':
			case 'K':
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				key_pressed = 'k';
				break;

			case 'm':
			case 'M':
				SetGameStatus(GAME_HELP_MENU);
				key_pressed = 'm';
				break;

			case 27:
				SetGameStatus(GAME_MAIN_MENU);
				break;

			case 'x':
			case 'X':
				SetGameStatus(GAME_CREDIT_PAGE);
				key_pressed = 'x';
				break;

			default:
				break;
		}
	}

	else if (GetGameStatus() == GAME_MAIN_MENU){
		switch (key){
			case 27:
				SetGameStatus(GAME_PLAYING);
				break;

			default:
				break;
		}
	}

	else if (GetGameStatus() == GAME_HELP_MENU){
		switch (key){
			case 27:
			case 'm':
			case 'M':
				SetGameStatus(GAME_PLAYING);
				key_pressed = 'm';
				break;

			default:
				break;
		}
	}

	else if (GetGameStatus() == GAME_CREDIT_PAGE){
		switch (key){
			case 27:
				SetGameStatus(GAME_PLAYING);
				break;

			case 'x':
			case 'X':
				SetGameStatus(GAME_DONE);
				key_pressed = 'x';
				break;

			default:
				break;
		}
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
		key_pressed = 0;
		break;
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		cam->SetIsMovingLR(false);
		key_pressed = 0;
		break;

	case 'k':
	case 'K':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		key_pressed = 0;

	default:
		break;
	}

	glutPostRedisplay();
}

void Control::OpenGLMouseMovementFunc(int x, int y){
	if (x != mouse_x_org || y != mouse_y_org){
		cam->SetCameraRotation(
			((double)x - ((double)screen_width/2)),
			((double)y - ((double)screen_height/2))
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