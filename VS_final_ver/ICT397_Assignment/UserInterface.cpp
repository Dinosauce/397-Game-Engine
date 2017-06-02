#include "UserInterface.h"

int UserInterface::screen_width;
int UserInterface::screen_height;

void UserInterface::DisplayHealth()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glPushMatrix();  //Make sure our transformations don't affect any other transformations in other code
		//Put other transformations here
		glBegin(GL_QUADS);   //We want to draw a quad, i.e. shape with four sides
			glColor3f(1, 0, 0); //Set the colour to red 
			glVertex2f(10, 10);            //Draw the four corners of the rectangle
			glVertex2f(10, 50);
			glVertex2f(health, 50);
			glVertex2f(health, 10);
		glEnd();
	glPopMatrix();
	glPushMatrix();  //Make sure our transformations don't affect any other transformations in other code
		//Put other transformations here
	glLineWidth(5);
		glBegin(GL_LINES);   //We want to draw a quad, i.e. shape with four sides
			glColor3f(0, 0, 0); 
			glVertex2f(10, 10);            //Draw the four corners of the rectangle
			glVertex2f(10, 50);
			glVertex2f(health, 50);
			glVertex2f(health, 10);
			glVertex2f(health, 10);
			glVertex2f(10, 10);
			glVertex2f(health, 50);
			glVertex2f(10, 50);
		glEnd();
	glPopMatrix();


	glEnable(GL_DEPTH_TEST); 


		std::cout << "here" << std::endl;
	
}
/*
void UserInterface::DisplayHealth(const int & width, const int & height){
	// clear the color draw b4
	glColor4f(1.0, 1.0, 1.0, 0.0);

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screen_width, 0, screen_height);
	glScalef(1, -1, 1);

	// move to centre of screen
	glTranslatef(screen_width / 2 - 256.0, -screen_height / 2 - 256.0, 0);
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();  //Make sure our transformations don't affect any other transformations in other code
		//Put other transformations here
		glBegin(GL_QUADS);   //We want to draw a quad, i.e. shape with four sides
		glColor3f(1, 0, 0); //Set the colour to red 
			glVertex3f(0, 0,0);            //Draw the four corners of the rectangle
			glVertex3f(0, 10 +height,0);
			glVertex3f(10+width, 10+height,0);
			glVertex3f(10+width, 0,0);
		glEnd();
	glPopMatrix();
	// display exit screen or welcome screen
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// display image
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, 0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0, 0 + height, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0 + width, 0 + height, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0 + width, 0, 0.0);
	glEnd();

	// Reset Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}*/

void UserInterface::mainMenu(int width, int height, int pos_x, int pos_y)
{
	texture2d.Display2DTexture(width, height, pos_x, pos_y, 0);
}

int UserInterface::getHealth()
{
	return health;
}

void UserInterface::setHealth(int he)
{
	health = he;
}

int UserInterface::getScore()
{
	return score;
}

void UserInterface::setScore(int sc)
{
	score = sc;
}

UserInterface::UserInterface()
{
	health = 310;
}


UserInterface::~UserInterface()
{
}
